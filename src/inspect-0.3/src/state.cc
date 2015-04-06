
#include "state.hh"
#include <sstream>
#include <iomanip>
#include <cassert>
#include <functional>
#include <vector>
#include "scheduler_setting.hh"

using namespace std;


////////////////////////////////////////////////////////////////////////////
//
//   the implementation of State
//
////////////////////////////////////////////////////////////////////////////

State::State()
    : prev(NULL), next(NULL), pcb_count(0)
{ 
  prog_state = new ProgramState();
}


State::State(State &another)
{
  prog_state = new ProgramState();
  *prog_state = *another.prog_state;

  symmetry = another.symmetry;
  backtrack = another.backtrack;
  done = another.done;
  sleepset = another.sleepset;
#ifdef NLZ_EVEC
  enabled_due = another.enabled_due;
  sel_event = another.sel_event;
#else
  sel_event = prog_state->enabled.get_transition(another.sel_event.thread_id);
#endif
  clock_vectors = another.clock_vectors;
  
  prev = next = NULL;

  pcb_count = another.pcb_count;
}


State::~State()
{ 
    delete prog_state;
}


State & State::operator = (State& another)
{
  prog_state = new ProgramState();
  *prog_state = *another.prog_state;

  backtrack = another.backtrack;
  done = another.done;
  sleepset = another.sleepset;

  if (another.sel_event.valid())
#ifdef NLZ_EVEC
      enabled_due = another.enabled_due;
      sel_event = another.sel_event;
#else
      sel_event = prog_state->enabled.get_transition(another.sel_event.thread_id);
#endif

  clock_vectors = another.clock_vectors;

  prev = next = NULL;

  pcb_count = another.pcb_count;

  return *this;
}


State * State::duplicate()
{
  State * state;
  state = new State(); 
  *state = *this;
  return state;
}


void State::add_transition(InspectEvent &event)
{
  prog_state->add_transition(event);
}



/**
 *  move all events that are disabled in enabled set into disabled set
 * 
 */
void State::update_enabled_set(InspectEvent &event)
{
  prog_state->update_enabled_set(event);
}


/** either release a disabled RWLOCK_WRLOCK or all disabled RWLOCK_RDLOCK;
 *
 */

void State::update_disabled_set(InspectEvent &event)
{
  prog_state->update_disabled_set(event);
}


void State::update_sleepset(InspectEvent &event)
{
  TransitionSet::iterator it;
  vector<InspectEvent> tobe_removed;
  vector<InspectEvent>::iterator vit;
  InspectEvent tmpev;

  assert( !prog_state->enabled.has_member(event));
#ifdef NLZ_EVEC
  for (it = sleepset.begin(); it != sleepset.end(); it++){
      for (vit = it->second.begin(); vit != it->second.end(); vit++){
	  tmpev = *vit;
	  if (event.dependent(tmpev))
	      tobe_removed.push_back(tmpev);
      }
  }
#else
  for (it = sleepset.begin(); it != sleepset.end(); it++){
    tmpev = it->second;
    if (event.dependent(tmpev))
      tobe_removed.push_back(tmpev);
  }
#endif
  for (vit = tobe_removed.begin(); vit != tobe_removed.end(); vit++){
    tmpev = *vit;
    //cout<<"sleepset remove dependent event "<<tmpev.toString()<<endl;
    sleepset.remove(tmpev);
  }  
}

void State::update_pcb_count(InspectEvent &event)
{
  if (prev != NULL) {
    pcb_count = prev->pcb_count;
    if (prev->sel_event.thread_id != event.thread_id) {
      if (alive(prev->sel_event.thread_id)) {
        pcb_count ++;
      }
    }
  }
}



bool State::is_in_backtrack(InspectEvent event)
{
  return backtrack.has_member(event);
}


bool  State::is_in_the_backtrack_set_of_previous_state(InspectEvent &event)
{
  State * prev_state = prev;

  while (prev_state != NULL){
    if (prev_state->is_in_backtrack(event)) return true;
    prev_state = prev_state->prev;
  }
  
  return false;
}



bool State::is_executed_before_bound(State * bound, InspectEvent &event)
{
  State * ptr;

  ptr = this;
  while (ptr != NULL && ptr != bound){
    if (ptr->sel_event == event) return true;
    ptr = ptr->next;
  }
  
  return false;  
}


bool State::is_in_some_backtrack_set_before_bound(State * bound, InspectEvent &event)
{
  State * ptr;
  ptr = this;

  while (ptr != NULL && ptr != bound){
    if (ptr->backtrack.has_member(event)) return true;
    ptr = ptr->next;
  }

  return false;
}


bool State::is_disabled_before_bound(State * bound, InspectEvent &event)
{
  State * ptr;
  ptr = this;
  while (ptr != NULL && ptr != bound){
    if (ptr->prog_state->disabled.has_member(event)) return true;	
    ptr = ptr->next;
  }

  return false;
}


bool State::is_accessed_by_the_same_thread_again_before_bound(State * bound, 
							      InspectEvent &event)
{
  State *ptr;
  InspectEvent event2;

  ptr = this->next;
  
  while (ptr != NULL && ptr != bound){
    event2 = ptr->sel_event;
    if (event2.thread_id == event.thread_id && event2.type == event.type){
      switch(event.type){
      case MUTEX_LOCK:  
	if (event.mutex_id == event2.mutex_id) return true; break;

      case OBJ_READ: 
      case OBJ_WRITE:
	if (event.obj_id == event2.obj_id) return true; break;

      default:  break;
      }
    }
    
    ptr = ptr->next;
  }
  return false;
}


void State::update_backtrack_set(State * bound)
{
  TransitionSet::iterator it;
  InspectEvent event;

  assert( bound != NULL);
  //cout << this->toString() << endl;
  assert(prog_state != NULL);
  if (sel_event.type == MUTEX_UNLOCK) return;
  if (sel_event.type == THREAD_CREATE) return;
  if (is_accessed_by_the_same_thread_again_before_bound(bound, sel_event)) return;
#ifdef NLZ_EVEC
  for (it = prog_state->enabled.begin(); 
       it != prog_state->enabled.end(); it++){
      for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++){
	  event = *vit;
	  if (event.type == MUTEX_UNLOCK)  continue;
	  if (backtrack.has_member(event)) continue;
	  if (done.has_member(event)) continue;
	  if (sleepset.has_member(event)) continue;
	  //if (is_in_the_backtrack_set_of_previous_state(event)) continue;
	  if (event.dependent(sel_event) && is_executed_before_bound(bound, event)) continue;
	  // if (is_in_some_backtrack_set_before_bound(bound, event)) continue;
	  // if (is_disabled_before_bound(bound, event)) continue;
    
	  backtrack.insert(event);
	  cout << endl << "DBG chao3: adding to backtrack: " << event.toString() << endl;
      }
  }  
#else
  for (it = prog_state->enabled.begin(); 
       it != prog_state->enabled.end(); it++){
    event = it->second;    
    if (event.type == MUTEX_UNLOCK)  continue;
    if (backtrack.has_member(event)) continue;
    if (done.has_member(event)) continue;
    if (sleepset.has_member(event)) continue;
    //if (is_in_the_backtrack_set_of_previous_state(event)) continue;
    if (event.dependent(sel_event) && is_executed_before_bound(bound, event)) continue;
    // if (is_in_some_backtrack_set_before_bound(bound, event)) continue;
    // if (is_disabled_before_bound(bound, event)) continue;
    
    backtrack.insert(event);
    cout << endl << "DBG chao3: adding to backtrack: " << event.toString() << endl;
  }
#endif
}

void State::execute(InspectEvent &event)
{
  switch(event.type){
  case MUTEX_INIT:   
  case MUTEX_DESTROY: 
  case MUTEX_LOCK:
  case MUTEX_UNLOCK:
  case RWLOCK_INIT:   
  case RWLOCK_DESTROY: 
  case RWLOCK_RDLOCK:
  case RWLOCK_WRLOCK:
  case RWLOCK_UNLOCK:    prog_state->execute_transition(event);    
  default:  break;
  }

  switch(event.type){
  case THREAD_START:  locksets.add_thread(event.thread_id);  break;
  case THREAD_END:    locksets.remove_thread(event.thread_id); break;
  case MISC_EXIT:     locksets.remove_thread(event.thread_id); break;
  case THREAD_CANCEL: locksets.remove_thread(event.child_id); break;
  case MUTEX_LOCK:    locksets.acquire(event.thread_id, event.mutex_id); break;
  case MUTEX_UNLOCK:  locksets.release(event.thread_id, event.mutex_id); break;    
  default:  break;
  }
}



bool State::is_enabled_empty()
{
  assert( prog_state != NULL);
  return  prog_state->enabled.empty();
}

/**
 *  get the new state by executing the event 
 */

/*
State * State::apply(InspectEvent &event)
{
  State * new_state = NULL;
  TransitionSet::iterator it;
  InspectEvent  tmpev;
  ClockVector * clock_vector = NULL;

  assert( prog_state->is_enabled(event) );  

  this->sel_event = event;
  
  new_state = new State();
  new_state->sleepset = sleepset;
  new_state->locksets = locksets;  
  new_state->clock_vectors = clock_vectors;
  clock_vector = new_state->clock_vectors.get_clock_vector(event.thread_id);  
  assert(clock_vector != NULL);
  clock_vector->timestamps[event.thread_id]++;

  new_state->execute(event);

  // to be added
  if (! this->symmetry.has_member(event.thread_id)){
    new_state->symmetry = symmetry;
  }

  // move some enabled transitions to disable transitions 
  new_state->update_enabled_set(event);
  new_state->update_disabled_set(event);
  new_state->update_sleepset(event);

  if (! this->sleepset.has_member(event) )
    this->sleepset.insert(event);

  if( !this->done.has_member(event))
    this->done.insert(event);  

  return new_state;
}
*/

/**
 *  testing whether an thread is alive
 */
bool State::alive(int tid)
{
  return prog_state->alive(tid);
}


bool  State::has_executable_transition()
{
  TransitionSet::iterator it;
  InspectEvent event;

#ifdef NLZ_EVEC
  for (it = prog_state->enabled.begin(); it != prog_state->enabled.end(); it++){
      for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++){
	  event = *vit;
	  if (!sleepset.has_member(event)) return true;
      }
  }
#else
  for (it = prog_state->enabled.begin(); it != prog_state->enabled.end(); it++){
      event = it->second;
      if (!sleepset.has_member(event)) return true;
  }
#endif
  return false;
}


bool State::has_been_end()
{
  return (prog_state->enabled.size() == 0 && prog_state->disabled.size() == 0);
}


InspectEvent State::get_transition()
{
  TransitionSet::iterator it;
  InspectEvent event;
#ifdef NLZ_EVEC
  for (it = prog_state->enabled.begin(); it != prog_state->enabled.end(); it++){
      for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++){
	  event = *vit;
	  if (!sleepset.has_member(event)) return event;
      }
  }
#else
  for (it = prog_state->enabled.begin(); it != prog_state->enabled.end(); it++){
    event = it->second;
    if (!sleepset.has_member(event)) return event;
  }
#endif
  return InspectEvent::dummyEvent;
}


InspectEvent State::get_transition_random()
{
  TransitionSet::iterator it;

  vector<InspectEvent*> trans;
#ifdef NLZ_EVEC
  for (it = prog_state->enabled.begin(); it != prog_state->enabled.end(); it++){
      for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++){
	  InspectEvent& event = *vit;
	  if (!sleepset.has_member(event)) {
	      trans.push_back(&event);
	  }
      }
  }
#else
  for (it = prog_state->enabled.begin(); it != prog_state->enabled.end(); it++){
    InspectEvent& event = it->second;
    if (!sleepset.has_member(event)) {
      trans.push_back(&event);
    }
  }
#endif  
  if (trans.size() == 0) 
    return InspectEvent::dummyEvent;

  int idx = rand() % trans.size();
  return *(trans[idx]);
}

#ifdef NLZ_EVEC
#else
InspectEvent State::get_transition_pcb()
{
  TransitionSet::iterator it;

  int prev_idx = -1;
  
  vector<InspectEvent*> trans;
  for (it = prog_state->enabled.begin(); it != prog_state->enabled.end(); it++){
    InspectEvent& event = it->second;
    if (!sleepset.has_member(event)) {
      if (prev != NULL && prev->sel_event.thread_id == it->first) {
        //this event has the same thread_id as the previous event
        prev_idx = trans.size();
      }
      trans.push_back(&event);
    }
  }

  if (trans.size() == 0) 
    return InspectEvent::dummyEvent;
  
  if (prev_idx != -1) {
    return *(trans[prev_idx]);
  }

  return *(trans[0]);
}
#endif

InspectEvent State::get_transition_no_spin()
{
  TransitionSet::iterator it;

  cout << __FUNCTION__ << " : sizeof(enabled) = " << prog_state->enabled.size() << endl;
  
#ifdef NLZ_EVEC   // TODO: IMPORTANT, need to understand the following code, ie no_spin
  for (it = prog_state->enabled.begin(); it != prog_state->enabled.end(); it++){
      for (std::vector<InspectEvent>::iterator vit= it->second.begin(); vit != it->second.end(); vit++){
	  InspectEvent event = *vit;
	  cout << __FUNCTION__ << "                   " << event.toString() << endl;
	  if (sleepset.has_member(event)) 
	      continue;
	  if (prev!=NULL && event.inst_id==prev->sel_event.inst_id && event.type==OBJ_READ)  {      
	      continue; // the two events are not from the same OBJ_READ
	  }
	  return event;
      }
  }
#else
for (it = prog_state->enabled.begin(); it != prog_state->enabled.end(); it++){
    InspectEvent event = it->second;
    cout << __FUNCTION__ << "                   " << event.toString() << endl;
    if (sleepset.has_member(event)) 
      continue;
    if (prev!=NULL && event.inst_id==prev->sel_event.inst_id && event.type==OBJ_READ)  {      
      continue; // the two events are not from the same OBJ_READ
    }
    return event;
  }
#endif
  return get_transition();
}



bool State::operator == (State &st)
{
//   return (enabled == st.enabled  &&
// 	  disable == st.disable  &&
// 	  sel_event == st.sel_event);	  
  assert(false);
  return false;
}


bool State::is_enabled(InspectEvent &event)
{
  return  prog_state->is_enabled(event);
}

bool State::is_disabled(InspectEvent &event)
{
  return prog_state->is_disabled(event);
}


bool State::check_race()
{
  return  prog_state->check_race();
}



Lockset * State::get_lockset(int tid)
{
  Lockset * lockset = NULL;
  lockset = locksets.get_lockset(tid);
  return lockset;
}


ClockVector * State::get_clock_vector(int tid)
{
  ClockVector * clock_vec = NULL;
  clock_vec = clock_vectors.get_clock_vector(tid);
  return clock_vec;
}


ProgramState * State::get_program_state(EventBuffer & event_buffer)
{
  return prog_state;
}


void State::update_clock_vector(InspectEvent &event)
{
  // RSS: fix on 4/7/2012
  if (event.type == THREAD_JOIN) {
    join_clock_vector(event.thread_id, event.child_id);
  }
  update_clock_vector(event.thread_id);
}


void State::update_clock_vector(int tid)
{
  ClockVector * clock_vector;

  clock_vector = clock_vectors.get_clock_vector(tid);
  assert(clock_vector != NULL);
  clock_vector->timestamps[tid]++;
}

#ifdef RSS_EXTENSION
 
void State::join_clock_vector(int tid, int child_tid)
{
  ClockVector * cv;
  ClockVector * cv_child;

  cv = clock_vectors.get_clock_vector(tid);
  assert(cv != NULL);

  cv_child = clock_vectors.get_clock_vector(child_tid);
  assert(cv_child != NULL);

  for(int pos = 0; pos < cv_child->size(); pos++) {
    if (cv->timestamps[pos] < cv_child->timestamps[pos]) {
      cv->timestamps[pos] = cv_child->timestamps[pos];
    }
  }
  cv->timestamps[child_tid] ++;

  assert(  cv_child->must_happen_before(*cv) );
  assert( !cv_child->is_concurrent_with(*cv) );
}
 
#endif//RSS_EXTENSION


string State::toString()
{
  stringstream  ss;
  TransitionSet::iterator it;

  ss << "state: ---------------------------\n";
  ss << "       sel:   : " << sel_event.toString() << "\n";

#ifdef NLZ_EVEC
  ss << "       enabled: \n";
  for (it = prog_state->enabled.begin(); it != prog_state->enabled.end(); it++)
      for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++)
	  ss << "            " << vit->toString() << "\n";
    
  ss << "       disabled: \n";
  for (it = prog_state->disabled.begin(); it != prog_state->disabled.end(); it++)
      for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++)
	  ss << "            " << vit->toString() << "\n";

  ss << "       backtrack: \n";
  for (it = backtrack.begin(); it != backtrack.end(); it++)
      for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++)
	  ss << "            " << vit->toString() << "\n";

  ss << "       done: \n";
  for (it = done.begin(); it != done.end(); it++)
      for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++)
	  ss << "            " << vit->toString() << "\n";


  ss << "       sleepset: \n";
  for (it = sleepset.begin(); it != sleepset.end(); it++)
      for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++)
	  ss << "            " << vit->toString() << "\n";
///no-dpor
  ss << "       clock vector size: \n";
  // for (it = sleepset.begin(); it != sleepset.end(); it++)
  // for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++)
  ss << "            " << clock_vectors.vecs.size() << "\n";

  ss << "       enabled_due:\n";
  for (std::map<int, bool>::iterator it=enabled_due.begin(); it!=enabled_due.end(); it++){
      ss<<"         "<<it->first<<": "<<it->second<<"    ";
  }
  ss<<"\n";
#else
  ss << "       enabled: \n";
  for (it = prog_state->enabled.begin(); it != prog_state->enabled.end(); it++)
    ss << "            " << it->second.toString() << "\n";
    
  ss << "       disabled: \n";
  for (it = prog_state->disabled.begin(); it != prog_state->disabled.end(); it++)
    ss << "            " << it->second.toString() << "\n";

  ss << "       backtrack: \n";
  for (it = backtrack.begin(); it != backtrack.end(); it++)
    ss << "            " << it->second.toString() << "\n";

  ss << "       done: \n";
  for (it = done.begin(); it != done.end(); it++)
    ss << "            " << it->second.toString() << "\n";


  ss << "       sleepset: \n";
  for (it = sleepset.begin(); it != sleepset.end(); it++)
    ss << "            " << it->second.toString() << "\n";
//no-dpor 
#ifdef NLZ_NO_DPOR
  ss << "       clock vector size: \n";
  ss << "            " << clock_vectors.vecs.size() << "\n";
#endif

#endif
  ss << "-----------------------------------\n";

  return ss.str();
}



string State::toSimpleString()
{
  stringstream  ss;
  TransitionSet::iterator it;

  ss << " [" << setw(3) << pcb_count;
  ss <<  "] ";

  ss << setw(30) << left << sel_event.toString() << ";";

#ifdef NLZ_EVEC
  if (backtrack.size() == 0) {
    ss << "     ";
  }
  else {
    ss << " bt={ ";  
    for (it = backtrack.begin(); it != backtrack.end(); it++) {
	for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); ++vit){
	    ss << "e" << vit->eid << " ";
	    ss<<"t= "<<vit->thread_id<<" , oid= "<< vit->obj_id<<" ";
	}
    }
    ss <<"}  ";
    ss << endl << setw(53) << " ";
  }

  ss << " done={ ";
  for (it = done.begin(); it != done.end(); it++) {
	for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); ++vit){
	    ss << "e" << vit->eid << " ";
	}
  }
  ss <<"}  ";

  if (sleepset.size() > 0) {
    ss << " sleep={ ";
    for (it = sleepset.begin(); it != sleepset.end(); it++){
	for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); ++vit){
	    ss << "e" << vit->eid << " ";
	}
    }
    ss <<"} ";
  }
#else
  if (backtrack.size() == 0) {
    ss << "     ";
  }
  else {
    ss << " bt={ ";  
    for (it = backtrack.begin(); it != backtrack.end(); it++) {
      ss << "e" << it->second.eid << " ";
    }
    ss <<"}  ";
    ss << endl << setw(53) << " ";
  }

  ss << " done={ ";
  for (it = done.begin(); it != done.end(); it++) {
    ss << "e" << it->second.eid << " ";
  }
  ss <<"}  ";

  if (sleepset.size() > 0) {
    ss << " sleep={ ";
    for (it = sleepset.begin(); it != sleepset.end(); it++)
      ss << "e" << it->second.eid << " ";
    ss <<"} ";
  }
#endif
  return ss.str();
}


void State::add_to_enabled(InspectEvent &event)
{
  assert(prog_state != NULL);
  prog_state->enabled.insert(event);
}


void State::remove_from_enabled(InspectEvent &event)
{
  assert(prog_state != NULL);
  prog_state->enabled.remove(event);
}





