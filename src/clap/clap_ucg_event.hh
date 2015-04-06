#ifndef CLAP_UCG_EVENT_HH
#define CLAP_UCG_EVENT_HH

#include <pthread.h>
#include <stdio.h>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

//#include "clap_ucg_lockset.h"
typedef set<int, less<int> > locks_held_t;



typedef enum {
  START,
  END,
  FORK,
  JOIN,
  WAIT_PRE,
  WAIT_POST,
  NOTIFY,
  NOTIFYALL,
  LOCK,
  UNLOCK,
  READ,
  WRITE,
  ATOMIC_LOAD,
  ATOMIC_STORE
} action_t;

typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} mem_odr_t;

typedef struct{
  int eid;
  unsigned tid;
  action_t action;
  union{
    int obj_id;
    int mutex_id;
    int cond_id;
    int child_id; // unsigned may be faulty
  };
  mem_odr_t mem_odr;
  locks_held_t locks_held;
} event_t;


extern map<int, event_t> event_list;
extern map<int *, int> obj_list;
extern map<int *, int> atomic_obj_list;
extern map<unsigned, int> tid_list;
extern map<pthread_mutex_t *, int> mutex_list;
extern map<pthread_cond_t *, int> cond_list;

extern map<pthread_t, locks_held_t> locks;

extern map<unsigned, vector<event_t> > thread_routine;

extern map<unsigned, map<int, map<action_t, map<int, int, less<int> > >, less<int> > > locks_log;

extern map<unsigned, vector<event_t> > wait_notify_pair;
extern vector<event_t> fork_join_list;

extern vector<unsigned> thread_id;

extern ofstream fout;

extern int step_id;

event_t event_create();
int map_tid(unsigned tid);
int map_mutex(pthread_mutex_t *mutex);
int map_obj(int *addr);
int map_atomic_obj(int *addr);
int map_cond(pthread_cond_t *cond);
locks_held_t get_locks_held(pthread_t thread);


#endif //CLAP_UCG_EVENT_HH
