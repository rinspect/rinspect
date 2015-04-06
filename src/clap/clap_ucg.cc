#include "clap_ucg.hh"

static int thread_cnt = 0;

unsigned parent_thread = 0;

bool main_thread = false;

void _ucg_thread_start()
{
  UCG_PRINT();
  //  printf("[tid = %d] %s()\n", map_tid((unsigned)pthread_self()), __FUNCTION__);

  // record each thread id
  pthread_t cur_thread = pthread_self();
  thread_id.push_back((unsigned)cur_thread);

  event_t new_event = event_create();
  //  new_event.action = START;
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);
}

void _ucg_thread_end()
{
  UCG_PRINT();
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)pthread_self()) << " </threadId> <eventType> thread_end </eventType>\n\t</ExecutionStep>\n";

  event_t new_event = event_create();
  new_event.action = END;
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);

  if(/*thread_cnt-- == 0 && */map_tid((unsigned)pthread_self()) == 0) {
    add_ucg_edge(thread_routine, DATA_RACE);

    fout.close();
    return;
  }
}

void _ucg_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg)
{
  if (!main_thread) {
    fout.open("trace.log.xml");
    parent_thread = (unsigned)pthread_self();
    thread_id.push_back(parent_thread);
    printf("[tid = %d] _ucg_thread_start()\n", map_tid(parent_thread));
    fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid(parent_thread) << " </threadId> <eventType> thread_start </eventType>\n\t</ExecutionStep>\n";
    main_thread = true;
  }
  printf("[tid = %d] _ucg_thread_precreate()\n", map_tid((unsigned)pthread_self()));
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid(parent_thread) << " </threadId> <eventType> thread_precreate </eventType>\n\t</ExecutionStep>\n";
  printf("[tid = %d] _ucg_thread_postcreate(%d)\n", map_tid((unsigned)pthread_self()), map_tid((unsigned)(*thread)));
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid(parent_thread) << " </threadId> <eventType> thread_postcreate </eventType> <childThreadId> " << map_tid((unsigned)(*thread)) << " </childThreadId>\n\t</ExecutionStep>\n";
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)*thread) << " </threadId> <eventType> thread_start </eventType>\n\t</ExecutionStep>\n";

  //  UCG_PRINT1(*thread);
  event_t new_event = event_create();
  pthread_t cur_thread = pthread_self();
  new_event.action = FORK;
  new_event.child_id = (unsigned)*thread;
  new_event.locks_held = get_locks_held(cur_thread);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);
  fork_join_list.push_back(new_event);
  ++thread_cnt;
}

void _ucg_thread_join(pthread_t thread, void **value_ptr)
{
  //  UCG_PRINT1(thread);
  printf("[tid = %d] %s(%d)\n", map_tid((unsigned)pthread_self()), __FUNCTION__, map_tid((unsigned)thread));
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)pthread_self()) << " </threadId> <eventType> thread_join </eventType> <childThreadId> " << map_tid((unsigned)thread) << " </childThreadId>\n\t</ExecutionStep>\n";

  event_t new_event = event_create();
  pthread_t cur_thread = pthread_self();

  new_event.action = JOIN;
  new_event.child_id = (unsigned)thread;
  new_event.locks_held = get_locks_held(cur_thread);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);
  fork_join_list.push_back(new_event);
  /*
  unsigned p, q, res = 0;
  unsigned thread_A, thread_B;
  if(--thread_cnt == 0) {
    for (p = 0; p < thread_id.size() - 1; ++p) {
      for (q = p + 1; q < thread_id.size(); ++q) {
        thread_A = thread_id[p];
        thread_B = thread_id[q];
        res = ucg_edge(thread_routine, thread_A, thread_B, DATA_RACE);
        if (res == 1) {
          printf("[tid = %d] _ucg_thread_end()\n", map_tid(parent_thread));
          fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid(parent_thread) << " </threadId> <eventType> thread_end </eventType>\n\t</ExecutionStep>\n";
          fout.close();
          return;
        }
      }
    }
    printf("[tid = %d] _ucg_thread_end()\n", map_tid(parent_thread));
    fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid(parent_thread) << " </threadId> <eventType> thread_end </eventType>\n\t</ExecutionStep>\n";
    fout.close();
  }*/
}

void _ucg_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr)
{
  //  UCG_PRINT1(mutex);
  map_mutex(mutex);
}

void _ucg_mutex_destroy(pthread_mutex_t *mutex)
{
  UCG_PRINT1(mutex);
  fout << "ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)pthread_self()) << " </threadId> <eventType> mutex_destroy </eventType> <mutexId> " << (unsigned)mutex << " </mutexId>\n\t</ExecutionStep>\n";
}

void _ucg_mutex_lock(pthread_mutex_t *mutex)
{
  event_t new_event = event_create();
  pthread_t cur_thread = pthread_self();

  new_event.action = LOCK;
  new_event.mutex_id = map_mutex(mutex);
  new_event.locks_held = get_locks_held(cur_thread);
  locks[cur_thread].insert(new_event.mutex_id);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);

  map<int, int, less<int> > tmp_acq_map, tmp_rel_map;
  map<action_t, map<int, int> > tmp_lock_acq_rel;
  if (locks_log[(unsigned)cur_thread].find(new_event.mutex_id) == locks_log[(unsigned)cur_thread].end()) {
    //    tmp_acq_map[new_event.eid] = -1;
    tmp_lock_acq_rel[LOCK] = tmp_acq_map;
    tmp_lock_acq_rel[UNLOCK] = tmp_rel_map;
    locks_log[(unsigned)cur_thread][new_event.mutex_id] = tmp_lock_acq_rel;
  }
  locks_log[(unsigned)cur_thread][new_event.mutex_id][LOCK][new_event.eid] = -1;

  UCG_PRINT1(mutex);
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)cur_thread) << " </threadId> <eventType> mutex_lock </eventType> <mutexId> " << (unsigned)mutex << " </mutexId>\n\t</ExecutionStep>\n";
}

void _ucg_mutex_trylock(pthread_mutex_t *mutex)
{
  UCG_PRINT1(mutex);
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)pthread_self()) << " </threadId> <eventType> mutex_trylock </eventType> <mutexId> " << (unsigned)mutex << " </mutexId>\n\t</ExecutionStep>\n";
}

void _ucg_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime)  
{
  UCG_PRINT1(mutex);
}

void _ucg_mutex_unlock(pthread_mutex_t *mutex)  
{
  UCG_PRINT1(mutex);
  event_t new_event = event_create();
  pthread_t cur_thread = pthread_self();
  new_event.action = UNLOCK;
  new_event.mutex_id = map_mutex(mutex);
  new_event.locks_held = get_locks_held(cur_thread);
  //  get_locks_held(cur_thread, new_event.locks_held);
  locks[cur_thread].erase(new_event.mutex_id);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);

  locks_log[(unsigned)cur_thread][new_event.mutex_id][LOCK].rbegin()->second = new_event.eid;
  locks_log[(unsigned)cur_thread][new_event.mutex_id][UNLOCK][new_event.eid] = locks_log[(unsigned)cur_thread][new_event.mutex_id][LOCK].rbegin()->first;

  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)cur_thread) << " </threadId> <eventType> mutex_unlock </eventType> <mutexId> " << (unsigned)mutex << " </mutexId>\n\t</ExecutionStep>\n";
}

void _ucg_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr)
{
  UCG_PRINT1(cond);
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)pthread_self()) << " </threadId> <eventType> cond_init </eventType> <condId> " << (unsigned)cond << " </condId>\n\t</ExecutionStep>\n";
}

void _ucg_cond_destroy(pthread_cond_t *cond)
{
  UCG_PRINT1(cond);
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)pthread_self()) << " </threadId> <eventType> cond_destroy </eventType> <condId> " << (unsigned)cond << " </condId>\n\t</ExecutionStep>\n";
}

void _ucg_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex)
{
  UCG_PRINT2(cond, mutex);
  pthread_t cur_thread = pthread_self();
  event_t new_event = event_create();
  new_event.action = WAIT_PRE;
  new_event.cond_id = map_cond(cond);
  new_event.locks_held = get_locks_held(cur_thread);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);
  wait_notify_pair[new_event.tid].push_back(new_event);

  new_event = event_create();
  new_event.action = UNLOCK;
  new_event.mutex_id = map_mutex(mutex);
  new_event.locks_held = get_locks_held(cur_thread);
  locks[cur_thread].erase(new_event.mutex_id);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);

  locks_log[(unsigned)cur_thread][new_event.mutex_id][LOCK].rbegin()->second = new_event.eid;
  locks_log[(unsigned)cur_thread][new_event.mutex_id][UNLOCK][new_event.eid] = locks_log[(unsigned)cur_thread][new_event.mutex_id][LOCK].rbegin()->first;

  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)cur_thread) << " </threadId> <eventType> cond_wait </eventType> <condId> " << (unsigned)cond << " </condId> <mutexId> " << (unsigned)mutex << " </mutexId>\n\t</ExecutionStep>\n";

  new_event = event_create();
  new_event.action = LOCK;
  new_event.mutex_id = map_mutex(mutex);
  new_event.locks_held = get_locks_held(cur_thread);
  locks[cur_thread].erase(new_event.mutex_id);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);

  locks_log[(unsigned)cur_thread][new_event.mutex_id][LOCK][new_event.eid] = -1;

  new_event = event_create();
  new_event.action = WAIT_POST;
  new_event.cond_id = map_cond(cond);
  new_event.locks_held = get_locks_held(cur_thread);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);
  wait_notify_pair[new_event.tid].push_back(new_event);
}

void _ucg_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime)
{
  UCG_PRINT2(cond, mutex);
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)pthread_self()) << " </threadId> <eventType> cond_timedwait </eventType> <condId> " << (unsigned)cond << " </condId>\n\t</ExecutionStep>\n";
}

void _ucg_cond_broadcast(pthread_cond_t *cond)
{
  UCG_PRINT1(cond);
  pthread_t cur_thread = pthread_self();
  event_t new_event = event_create();
  new_event.action = NOTIFYALL;
  new_event.cond_id = map_cond(cond);
  new_event.locks_held = get_locks_held(cur_thread);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);
  wait_notify_pair[new_event.tid].push_back(new_event);
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)cur_thread) << " </threadId> <eventType> cond_broadcast </eventType> <condId> " << (unsigned)cond << " </condId>\n\t</ExecutionStep>\n";
}

void _ucg_cond_signal(pthread_cond_t *cond)
{ 
  UCG_PRINT1(cond);
  pthread_t cur_thread = pthread_self();
  event_t new_event = event_create();
  new_event.action = NOTIFY;
  new_event.cond_id = map_cond(cond);
  new_event.locks_held = get_locks_held(cur_thread);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);
  wait_notify_pair[new_event.tid].push_back(new_event);
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)cur_thread) << " </threadId> <eventType> cond_signal </eventType> <condId> " << (unsigned)cond << " </condId>\n\t</ExecutionStep>\n";
}

void _ucg_atomic_load(int* addr, const int mem_odr)
{
  UCG_PRINT1(addr);
  event_t new_event = event_create();
  pthread_t cur_thread = pthread_self();
  new_event.action = ATOMIC_LOAD;
  new_event.obj_id = map_atomic_obj(addr);
  new_event.mem_odr = (mem_odr_t)mem_odr;
  new_event.locks_held = get_locks_held(cur_thread);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);
}

void _ucg_atomic_store(int* addr, const int mem_odr)
{
  UCG_PRINT1(addr);
  event_t new_event = event_create();
  pthread_t cur_thread = pthread_self();
  new_event.action = ATOMIC_STORE;
  new_event.obj_id = map_atomic_obj(addr);
  new_event.mem_odr = (mem_odr_t)mem_odr;
  new_event.locks_held = get_locks_held(cur_thread);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);
}

void _ucg_obj_read(int* addr)
{
  UCG_PRINT1(addr);
  pthread_t cur_thread = pthread_self();
  event_t new_event = event_create();
  new_event.action = READ;
  new_event.obj_id = map_obj(addr);
  new_event.locks_held = get_locks_held(cur_thread);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)cur_thread) << " </threadId> <eventType> obj_read </eventType> <objId> " << (unsigned)addr << " </objId> <objVal> " << *addr << " </objVal>\n\t</ExecutionStep>\n";
}

void _ucg_obj_write(int* addr)
{
  UCG_PRINT1(addr);
  pthread_t cur_thread = pthread_self();
  event_t new_event = event_create();
  new_event.action = WRITE;
  new_event.obj_id = map_obj(addr);
  new_event.locks_held = get_locks_held(cur_thread);
  event_list[new_event.eid] = new_event;
  thread_routine[new_event.tid].push_back(new_event);
  fout << "<ExecutionStep id = \"" << step_id++ << "\">\n\t<threadId> " << map_tid((unsigned)cur_thread) << " </threadId> <eventType> obj_write </eventType> <objId> " << (unsigned)addr << " </objId> <objVal> " << *addr << " </objVal>\n\t</ExecutionStep>\n";
}

void _ucg_call_begin(char* fname, char* ptr)
{
  UCG_PRINT1(fname);  
}

void _ucg_call_end(char* fname, char* ptr)
{
  UCG_PRINT1(fname);  
}

void _ucg_inst_begin(int inst, int stat)
{
  UCG_PRINT2(inst, stat);
}

void _ucg_inst_end(int inst, int stat, int retval)
{
  UCG_PRINT2(inst, stat);
}


