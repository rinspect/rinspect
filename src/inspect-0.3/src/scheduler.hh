#ifndef __THREAD_SCHEDULER_H__
#define __THREAD_SCHEDULER_H__

#include "naling.def"
#include <vector>
#include <set>
#include <ext/hash_set>
#include <utility>

#include "inspect_util.hh"
#include "inspect_event.hh"
#include "scheduler_object_table.hh"
#include "inspect_exception.hh"

#include "state.hh"
#include "state_stack.hh"
#include "event_buffer.hh"
#include "thread_info.hh"
#include "scheduler_setting.hh"
#include "event_relation_graph.hh"


using std::vector;
using std::set;
using std::map;
using std::pair;
using __gnu_cxx::hash_map;
using __gnu_cxx::hash;


class Scheduler : public Thread
{
public:
  Scheduler();
  ~Scheduler();

  bool init();
  void read_replay_file();

  InspectEvent receive_event( Socket * socket ); 
  InspectEvent receive_main_start();
  void approve_event(InspectEvent &event);

  void run(); 
  void stop();
  
  inline bool is_listening_socket(int fd); 
  void print_out_trace();
  pair<int, int> set_read_fds();

  void exec_test_target(const char * path);

  void update_backtrack_info(State * state);

  void DPOR_update_backtrack_info(State * state);
  void PCB_update_backtrack_info(State * state);
  void PSET_update_backtrack_info(State * state);

  void DPOR_update_backtrack_info(State * state, InspectEvent &event);
  void PCB_update_backtrack_info(State * state, InspectEvent &event);
  void PSET_update_backtrack_info(State * state, InspectEvent &event);
#ifdef NLZ_COMM
    void NLZ_DPOR_update_backtrack_info(State * state,InspectEvent &event);
#endif

  void lazy_update_backtrack_info(State * state, InspectEvent &event, bool allow_communicative=true);

  void lazy_update_locks(State*, InspectEvent&);
  void lazy_update_internal(State*, State*, InspectEvent&, InspectEvent&, InspectEvent&);

  State* last_conflicting_state(State *s, InspectEvent &e);

  bool dependent(InspectEvent &e1, InspectEvent &e2);
  bool is_mutex_exclusive_locksets(Lockset *, Lockset*);
  void report();

  bool examine_state(State*, State*);
public:
  InspectEvent & get_event_from_buffer(int tid);
  void exec_transition(InspectEvent &event);

  void free_run();
  void monitor_first_run();
  void yices_run();
  void backtrack_checking();
//   void monitor();
  State * execute_one_thread_until(State * state, int tid, InspectEvent);
  //State * next_state(State *state, InspectEvent &event, LocalStateTable * ls_table);

public:
  void get_mutex_protected_events(State * state1, State * state2, int tid, vector<InspectEvent>& events);

  State * get_initial_state();

  InspectEvent get_latest_executed_event_of_thread(State * state, int thread_id);

  void check_property(State * state);

  bool found_enough_error() { return (num_of_errors_detected >= max_errors); }


    
public:
  EventBuffer event_buffer;
  EventGraph  event_graph;
  
public:
  int max_errors;
  int num_of_errors_detected;
  int num_of_transitions;
  int num_of_states;
  int num_of_truncated_branches;
  int num_killed;
  int sut_pid;  
  int run_counter;
  bool found_bug; 
  StateStack state_stack;

  vector<InspectEvent> error_trace;  //RSS
  int exit_status;                   //RSS
  long start_cpu_time;               //RSS

#ifdef NLZ_FLAG
public:
    typedef std::vector<State*> Chain;
    typedef std::vector<int> PtnCycle;
    std::vector<PtnCycle> ptn_cycles;
    PtnCycle* p_current_replaying_ptn_cycle;
    
    void detect_ptn_cycle();
    void save_ptn_cycle(const Chain& chain, InspectEvent& event);
    void confirm_cycle();
    int ptn_delay_model(InspectEvent& event);
    int rand_delay_model(InspectEvent& event);
    int get_distance_between_states(State* state1, State* state2);
#endif


    
};




#endif



