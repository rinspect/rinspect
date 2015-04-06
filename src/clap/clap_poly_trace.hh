#ifndef __CLAP_POLY_TRACE_HH__
#define __CLAP_POLY_TRACE_HH__

#include <map>
#include <stdlib.h>

#include "clap_event.hh"
#include "clap_poly_object.hh"
#include "clap_poly_graph.hh"


using namespace std;

typedef EventType PolyEventType;
typedef Event     PolyEvent;


class PolyTrace
{
public: 
  PolyTrace();
  ~PolyTrace();

  void add_event(PolyEventType typ, int tid, int var);

  void handle_thread(PolyEvent* ev);
  void handle_mutex(PolyEvent* ev);
  void handle_object(PolyEvent* ev);
  void handle_condvar(PolyEvent* ev);

  void add_thread_edges();        //thread-local, fork/join
  void add_acq_rel_edges();  
  void add_signal_wait_edges();
  void add_write_read_edges();
  void add_causally_precedes_edges();

  void find_potential_races(vector<PolyEventPair>& races);
  void filter_races_by_lockset(vector<PolyEventPair>& races);

  void filter_races(const char* str, vector<PolyEventPair>& races, bool);
  void filter_races_by_hb(vector<PolyEventPair>& races, bool);
  void filter_races_by_cp(vector<PolyEventPair>& races, bool);
  void filter_races_by_ucg(vector<PolyEventPair>& races, bool);
  void filter_races_by_vt(vector<PolyEventPair>& races, bool);

  bool simultaneously_reachable(PolyEvent* ev1, PolyEvent* ev2);
  void check_race();

  void slicing();

  void check_atomicity();

  void dump();
  void print_statistics();

public:
  vector<PolyEvent*>    events;

  PolyEvent*            main_start_ev;
  PolyEvent*            main_end_ev;
  PolyEvent*            main_first_thread_create_ev;
  PolyEvent*            main_last_thread_join_ev;

  vector<PolyThread*>   threads;
  vector<PolyMutex*>    mutexes;
  vector<PolyCondVar*>  condvars;
  vector<PolyObject*>   objects;

  map<int, PolyThread*>  id_to_thread;
  map<int, PolyMutex*>   id_to_mutex;
  map<int, PolyObject*>  id_to_object;
  map<int, PolyCondVar*> id_to_condvar;

  PolyGraphSMT   graph;


private:
  map<int, LockSet>     curr_locksets;
  map<int, PolyEvent*>  mutex_to_acq;
  VarSet                curr_varset;
  map<int, PolyEvent*>  obj_to_write;
  CondSet               curr_condset;
  map<int, PolyEvent*>  cond_to_signal;
  map<int, PolyEvent*>  thread_to_start;
  map<int, PolyEvent*>  thread_to_last_event;

};


#endif
