#include "inspect_event.hh"
#include "state.hh"
#include "event_buffer.hh"
#include "scheduler_setting.hh"
#include "scheduler.hh"
#include "inspect_exception.hh"
#include "thread_info.hh"
#include "next_state.hh"

using namespace std;


#ifdef NLZ_COMM
void handle_symmetry_event(State *state, std::vector<InspectEvent> &event_vec, EventBuffer &event_buffer)
{
  assert(state != NULL);
  if (event_vec.front().type != SYMM_POINT) {return;}
  
  assert(event_vec.size()==1);
  InspectEvent& ev = event_vec.front(); 
  event_buffer.approve(ev);
  state->symmetry.insert(ev);
 
  InspectEvent new_event;
  event_vec = event_buffer.get_events(ev.thread_id);
}
#endif

void handle_symmetry_event(State *state, InspectEvent &event, EventBuffer &event_buffer)
{
  assert(state != NULL);
  if (event.type != SYMM_POINT) return;
  
  event_buffer.approve(event);
  state->symmetry.insert(event);
 
  InspectEvent new_event;
  new_event = event_buffer.get_event(event.thread_id);
  event = new_event;  
}


/**  Given a state, compute the next state 
 * 
 *  Here we need to take care of thread creation specially.
 *  
 *  A state is composed of:
 *  (1) enabled set  -- the set of transitions that are enabled at the state                 
 *  (2) disabled set -- the set of transitions that are currently disabled, but              
 *  (3) the state of global objects                                                        
 *        -- the state of mutexes
 *        -- the state of reader/writer locks
 *        -- the snapshot of global objects
 *  (4) the local states of threads
 *  (5) 
 *  (6)  
 * 
 */
State * next_state(State* state, 
		   InspectEvent &event, 
		   EventBuffer &event_buffer)
{
  State * new_state = NULL;
  InspectEvent  symmetry_event;
  InspectEvent pre_create, post_create, after_post, thread_start, first_ev;
  int prev_sid = -1;    
  bool exception_flag = false;

  assert( state != NULL );
  assert( event.valid() );  
  assert( state->is_enabled(event) );
  
  // state->check_race();

  new_state = new State();

  //*new_state = *state;
#ifdef NLZ_COMM
  new_state->enabled_due = state->enabled_due;
  new_state->enabled_due[event.thread_id] = false;
#endif
  *(new_state->prog_state) = *(state->prog_state);
  new_state->remove_from_enabled(event);

  new_state->sleepset = state->sleepset;
  new_state->locksets = state->locksets;  
  new_state->clock_vectors = state->clock_vectors;

  // increase the clock counter of the correspondent thread by 1
  new_state->update_clock_vector(event);  

  new_state->execute(event);

  if (! state->symmetry.has_member(event.thread_id)){
    new_state->symmetry = state->symmetry;
  }

  new_state->update_enabled_set(event);
  new_state->update_disabled_set(event);
  new_state->update_sleepset(event);//new state update sleepset

  //#define RSS_DISABLE_SLEEPSET
#ifndef RSS_DISABLE_SLEEPSET
  //RSS: if you want to disable sleepset, remove the following 
  if (! state->sleepset.has_member(event) ) { 
  #ifdef NLZ_NO_SLEEPSET // if no sleep ==true, add,here it is opposite
      if(!setting.disable_sleepset_flag) {state->sleepset.insert(event);}
  #else 
      state->sleepset.insert(event);
  #endif
  }
#endif

  if( !state->done.has_member(event))
    state->done.insert(event);  


  state->sel_event = event;
  try{
      
      event_buffer.approve(event);
      
  }
  catch(SocketException &e){
    exception_flag = true;
  }


#ifdef NLZ_EVEC //don't care right now
#else
  update_pcb_count(state);
#endif

  if (exception_flag) return new_state;
    
  if (event.type == THREAD_END ||
      event.type == MISC_EXIT ||
      event.type == PROPERTY_ASSERT)  return new_state;
  
  // here we need to handle multiple situtation here
  // need a better style 
  
  bool found_next_event = false;
  bool received_delta = false;
  InspectEvent new_event;

#ifdef NLZ_COMM
  std::vector<InspectEvent> new_ev_vec;
  while (! found_next_event){
    new_ev_vec = event_buffer.get_events(event.thread_id);    
    handle_symmetry_event(new_state, new_ev_vec, event_buffer);
    new_event = new_ev_vec.front();
    if(new_event.i_mult==1) { State * em_state = NULL; em_state = new State();return em_state; }//for bounding
  
    switch(new_event.type){
    case THREAD_POST_CREATE:
      {
	  assert(new_ev_vec.size() ==1 );
#else
  while (! found_next_event){
      new_event = event_buffer.get_event(event.thread_id);
      handle_symmetry_event(new_state, new_event, event_buffer);
      switch(new_event.type){
      case THREAD_POST_CREATE:
      {	  
#endif
        assert(event.type == THREAD_PRE_CREATE);
	post_create = new_event;

	event_buffer.approve(post_create);
	
	after_post = event_buffer.get_event(post_create.thread_id);
	thread_start = event_buffer.get_event(post_create.child_id);
	assert(thread_start.type == THREAD_START);

	event_buffer.approve(thread_start);
	first_ev = event_buffer.get_event(post_create.child_id);
	
	//ls_tables.add_thread(post_create.child_id);
	
	handle_symmetry_event(new_state, first_ev, event_buffer);

	InspectEvent  thrd_ev;
	thrd_ev.init_thread_create(post_create.thread_id, post_create.child_id);
	
	new_state->execute(post_create);
	new_state->execute(thread_start);      
	state->sel_event = thrd_ev;
	
#ifdef NLZ_EVEC
#else
	update_pcb_count(state);
#endif
	
	new_state->remove_from_enabled(post_create);
#ifdef NLZ_COMM
	if (first_ev.type == OBJ_WRITE){ new_state->enabled_due[first_ev.thread_id]=true; }
#endif
	new_state->add_transition(first_ev);

	new_event = after_post;
	new_state->clock_vectors.add_thread(post_create.child_id, post_create.thread_id);	

	thread_table.add_thread(post_create.child_id, ""// thread_start.thread_nm
				, post_create.thread_arg);

	found_next_event = true;
#ifdef NLZ_COMM
	new_ev_vec.front() = new_event;
#endif
	break;
      }
      default:  found_next_event = true; 
    }
    
  }

#ifdef NLZ_COMM
  /// fix a bug of two read
  // if there is an event (future) is inside of enabled set, do i need to update it?
  for (std::vector<InspectEvent>::iterator it = new_ev_vec.begin(); it != new_ev_vec.end(); it++){
      assert(it->thread_id == event.thread_id);
      new_state->add_transition(*it);
  }
 
  if (new_state->prog_state->enabled.has_write_but_read(event.thread_id) && new_event.future != -1){
     	  new_state->enabled_due[event.thread_id] = true;
      }
  
#else
  assert(new_event.thread_id == event.thread_id);
  new_state->add_transition(new_event);
#endif
  
 
  return new_state;
}
	

#ifdef RSS_EXTENSION

#ifdef NLZ_EVEC
#else
void update_pcb_count(State *state)
{
  State *prev_state = state->prev;
  if (prev_state == NULL) {
    state->pcb_count = 0;
  }
  else {
    state->pcb_count = prev_state->pcb_count;
    
    InspectEvent &prev_event = prev_state->sel_event;
    InspectEvent &event = state->sel_event;
    if (prev_event.valid() && event.valid() && 
	prev_event.thread_id != event.thread_id) { //context switched

      if (get_event_category(prev_event.type) != EC_THREAD &&
	  get_event_category(event.type) != EC_THREAD ) {

	InspectEvent alt_event;
	alt_event = state->prog_state->enabled.get_transition(prev_event.thread_id);
	if (alt_event.valid()) { // pre-emption
	  state->pcb_count++;
	}
      }
    }
  }

}
#endif

void update_pset(State *state)
{
  InspectEvent &event = state->sel_event;

  assert(0 && "not yet implemented!\n");
}
#endif
