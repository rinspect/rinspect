#ifndef __INSPECT_STATE_H__
#define __INSPECT_STATE_H__

#include <vector>
#include <map>
#include <set>

#include "inspect_event.hh"
#include "scheduler_object_table.hh"
#include "clock_vector.hh"
#include "transition_set.hh"
#include "lockset.hh"
#include "program_state.hh"
#include "event_buffer.hh"


using std::vector;
using std::set;
using std::map;



class State
{
public:
  State();
  State(State& another);
  ~State();

  State& operator = (State& another);
  State * duplicate();
  //State * apply(InspectEvent &event);

  bool is_in_backtrack(InspectEvent event);
  
  //void clear_backtrack_info();

  bool mutual_exclusive(InspectEvent * e1, InspectEvent * e2);
  bool must_happen_before(InspectEvent * e1, InspectEvent * e2);
  bool is_concurrent(InspectEvent * e1, InspectEvent * e2);
  
  string toString();
  string toSimpleString();

  void add_transition(InspectEvent & event);

  void update_enabled_set(InspectEvent & event);
  void update_disabled_set(InspectEvent &event);
  void update_sleepset(InspectEvent &event);
  void update_pcb_count(InspectEvent &event);
  void update_backtrack_set(State * bound);
  
  void update_clock_vector(int tid);
  void update_clock_vector(InspectEvent &event);
  void join_clock_vector(int tid, int child_tid);

  bool operator == (State& st);

  bool alive(int tid);
  
  InspectEvent get_transition();
  InspectEvent get_transition_random();
  InspectEvent get_transition_pcb();
  InspectEvent get_transition_no_spin();

  void execute(InspectEvent &event);
  //void execute(InspectEvent &event, EventBuffer &event_buffer);

  State * get_next(InspectEvent &event, EventBuffer &event_buffer);

  bool has_executable_transition();
  bool has_been_end();

  bool is_enabled_empty();

  Lockset * get_lockset(int tid); 
  ClockVector * get_clock_vector(int tid);

  bool check_race();

  ProgramState * get_program_state(EventBuffer & event_buffer);

  void add_to_enabled(InspectEvent &event);
  void remove_from_enabled(InspectEvent &event);
  
  bool is_enabled(InspectEvent &event);
  bool is_disabled(InspectEvent &event);

  bool is_executed_before_bound(State * bound, InspectEvent &event);
  bool is_in_the_backtrack_set_of_previous_state(InspectEvent &event);
  bool is_in_some_backtrack_set_before_bound(State * bound, InspectEvent &event);
  bool is_disabled_before_bound(State * bound, InspectEvent &event);

  bool is_accessed_by_the_same_thread_again_before_bound(State * bound, InspectEvent &event);

  
  int get_local_state_id(int tid);

public:
  ProgramState * prog_state;

  TransitionSet symmetry;

  int pcb_count;
						
  TransitionSet backtrack;
  TransitionSet done;
  TransitionSet sleepset;
  
  Locksets  locksets;
  //Rwlocksets  rwlocksets;

  ClockVectorList  clock_vectors;
  
  InspectEvent sel_event;
  bool bkinfo_computed_flag;  // the backtrack info has been computed

#ifdef NLZ_COMM
    std::map<int, bool> enabled_due;  // empty==false
#endif
    
  State * prev;
  State * next;  
};


//   TransitionSet enabled;
//   TransitionSet disabled;

//   SchedulerMutexIndex  mutexes;
//   SchedulerCondIndex   conds;
//   SchedulerRwlockIndex rwlocks;
  



/* 
 You are given an array of integer of size N (A[0],A[1],A[2],...A,[N-1])
containing both negative and non-negative integers. Design an efficient
algorithm to find the sub sequence A[i],A[i+1],A[i+2]...,A[j] having the
maximum summation (A[i]+A[i+1]+A[i+2] + ...+A[j] have the highest sum). What
is the complexity of your algorithm?
*/

#endif


