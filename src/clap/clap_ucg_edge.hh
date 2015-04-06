#ifndef CLAP_UCG_EDGE_HH
#define CLAP_UCG_EDGE_HH

#include "clap_ucg_event.hh"
#include <list>

using namespace std;




typedef enum{
  WAIT_NOTIFY,
  FORK_JOIN
}sync_prop_t;

typedef enum{
  DATA_RACE,
  ATOMICITY_VIOLATION,
  ORDER_VIOLATION,
  DEADLOCK
}property_t;

typedef enum{
  SQTL_SEED,
  PROP_SEED,
  SYNC_SEED,
  ATOMIC,
  INDUCED
}ucg_edge_t;

typedef struct {
  unsigned edge_id;
  event_t source;
  event_t target;
  ucg_edge_t type;
} edge_t;


void add_ucg_edge(map<unsigned, vector<event_t> > thread_routine,
                  property_t prop = DATA_RACE);
void add_sequential_edge(map<unsigned, vector<event_t> > thread_routine,
                         bool mem_rlx = true);
/*
void ucg_seed_edge(property_t prop,
                   map<unsigned, vector<event_t> > thread_routine,
                   unsigned thread_A,
                   unsigned thread_B,
                   map<int *, int> *obj_list,
                   map<pthread_cond_t *, int> cond_list);

void add_property_seed_edge(property_t prop,
                            map<unsigned, vector<event_t> > thread_routine,
                            unsigned thread_A,
                            unsigned thread_B,
                            int obj_id);
*/
void add_sync_seed_edge(sync_prop_t sync,
                        map<unsigned, vector<event_t> > wait_notify_pair,
                        vector<event_t> fork_join_list,
                        unsigned thread_A,
                        unsigned thread_B,
                        map<pthread_cond_t *, int> cond_list);
void add_poly_edge(map<unsigned, map<int, map<action_t, map<int, int, less<int> > >, less<int> > > locks_log,
                   unsigned thread_A,
                   unsigned thread_B);
void add_atomic_edge(map<int, event_t> event_list, map<int *, int> atomic_obj_list);
void add_induced_edge(map<unsigned, vector<event_t> > thread_routine,
                      map<pthread_mutex_t *, int> mutex_list);
void create_edge(event_t source, event_t target, ucg_edge_t type);
void remove_edge(event_t source, event_t target, ucg_edge_t type);
bool find_edge(event_t source, event_t target);
void restore_event_containers(vector<vector<event_t> > &event_containers);
bool lock_held(event_t event, int mutex_id);
//bool lock_not_released(event_t event, int mutex_id);
event_t find_last(action_t action, event_t event, int mutex_id);
event_t find_first(action_t action, event_t event, int mutex_id);
event_t find_matching(event_t event, int mutex_id);

//void ucg_print_edges();
//void ucg_print_events();

bool ucg_edge_found(vector<edge_t> edges, edge_t edge);

#endif // CLAP_UCG_EDGE_HH
