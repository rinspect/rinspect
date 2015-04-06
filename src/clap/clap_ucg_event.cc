#include "clap_ucg_event.hh"


map<int, event_t> event_list;
map<int *, int> obj_list;
map<int *, int> atomic_obj_list;
map<unsigned, int> tid_list;
map<pthread_mutex_t *, int> mutex_list;
map<pthread_cond_t *, int> cond_list;

map<pthread_t, locks_held_t> locks;
//map<int *, vars_written_t> vars;

map<unsigned, vector<event_t> > thread_routine;

map<unsigned, map<int, map<action_t, map<int, int, less<int> > >, less<int> > > locks_log;

map<unsigned, vector<event_t> > wait_notify_pair;
vector<event_t> fork_join_list;

vector<unsigned> thread_id;

ofstream fout;

int step_id = 0;

event_t event_create()
{
  event_t new_event;
  new_event.eid = event_list.size();
  new_event.tid = (unsigned)pthread_self();
  new_event.action = START;
  new_event.obj_id = -1;
  new_event.mutex_id = -1;
  new_event.cond_id = -1;
  new_event.child_id = -1;
  new_event.mem_odr = memory_order_relaxed;
  return new_event;
}

int map_tid(unsigned tid)
{
  int res = -1;
  int size_1 = tid_list.size();
  res = tid_list[tid];
  int size_2 = tid_list.size();
  if (size_2 != size_1) {
    tid_list[tid] = size_1;
    res = size_1;
  }
  return res;
}

int map_mutex(pthread_mutex_t *mutex)
{
  int res = -1;
  int size_1 = mutex_list.size();
  res = mutex_list[mutex];
  int size_2 = mutex_list.size();
  if (size_2 != size_1) {
    mutex_list[mutex] = size_1;
    res = size_1;
    printf("[tid = %d] _ucg_mutex_init(%u)\n", map_tid((unsigned)pthread_self()), (unsigned)mutex);
    fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)pthread_self()) << " </threadId> <eventType> mutex_init </eventType> <mutexId> " << (unsigned)mutex << " </mutexId>\n\t</ExecutionStep>\n";
  }
  return res;
}

int map_obj(int *addr)
{
  int res = -1;
  int size_1 = obj_list.size();
  res = obj_list[addr];
  int size_2 = obj_list.size();
  if (size_2 != size_1) {
    obj_list[addr] = size_1;
    res = size_1;
  }
  return res;
}

int map_atomic_obj(int *addr)
{
  int res = -1;
  int size_1 = atomic_obj_list.size();
  res = atomic_obj_list[addr];
  int size_2 = atomic_obj_list.size();
  if (size_2 != size_1) {
    atomic_obj_list[addr] = size_1;
    res = size_1;
  }
  return res;
}

int map_cond(pthread_cond_t *cond)
{
  int res = -1;
  int size_1 = cond_list.size();
  res = cond_list[cond];
  int size_2 = cond_list.size();
  if (size_2 != size_1) {
    cond_list[cond] = size_1;
    res = size_1;
  }
  return res;
}

locks_held_t get_locks_held(pthread_t thread)
{
  map<pthread_t, locks_held_t>::iterator it;
  it = locks.find(thread);
  if (it != locks.end()) {
    //    printf("%d\n", locks[thread].size());
    return it->second;
  }
  else {
    locks_held_t tmp;
    return tmp;
  }
}

