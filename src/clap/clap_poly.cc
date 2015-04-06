#include "clap_poly.hh"
#include "clap_poly_trace.hh"

// @variable   trace
// @brief      Storing the input execution trace.
static PolyTrace trace;


void _poly_thread_start() {
  POLY_PRINT();
  trace.add_event(THREAD_START, UTID_self(), 0);
}

void _poly_thread_end() {
  POLY_PRINT();
  trace.add_event(THREAD_END, UTID_self(), 0);

  if (UTID_self() == 1) {

    //after the main thread ends, start predictive analysis
    char *flag_str = getenv("CLAP_POLY_CHECKER");
    if (flag_str && !strcmp(flag_str,"atomicity")) {
      trace.check_atomicity();
    }
    else {
      trace.check_race();
    }

  }
}

void _poly_thread_create(pthread_t * thread, const pthread_attr_t * attr,
                         void *(*start_routine)(void*), void * arg) {
  POLY_PRINTt(*thread);
  trace.add_event(THREAD_CREATE, UTID_self(), UTID(*thread));
}

void _poly_thread_join(pthread_t thread, void **value_ptr) {
  POLY_PRINTt(thread);
  trace.add_event(THREAD_JOIN, UTID_self(), UTID(thread));
}

void _poly_mutex_init(pthread_mutex_t * mutex,
                      const pthread_mutexattr_t * attr) {
  POLY_PRINT1(mutex);
  trace.add_event(MUTEX_INIT, UTID_self(), UOID(mutex));
}

void _poly_mutex_destroy(pthread_mutex_t *mutex) {
  POLY_PRINT1(mutex);
  trace.add_event(MUTEX_DESTROY, UTID_self(), UOID(mutex));
}

void _poly_mutex_lock(pthread_mutex_t *mutex) {
  POLY_PRINT1(mutex);
  trace.add_event(MUTEX_LOCK, UTID_self(), UOID(mutex));
}

void _poly_mutex_trylock(pthread_mutex_t *mutex) {
  POLY_PRINT1(mutex);
  assert(0);
}

void _poly_mutex_timedlock(pthread_mutex_t *mutex,
                           const struct timespec *abstime) {
  POLY_PRINT1(mutex);
  assert(0);
}

void _poly_mutex_unlock(pthread_mutex_t *mutex) {
  POLY_PRINT1(mutex);
  trace.add_event(MUTEX_UNLOCK, UTID_self(), UOID(mutex));
}

void _poly_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr) {
  POLY_PRINT1(cond);
  trace.add_event(COND_INIT, UTID_self(), UOID(cond));
}

void _poly_cond_destroy(pthread_cond_t *cond) {
  POLY_PRINT1(cond);
  trace.add_event(COND_DESTROY, UTID_self(), UOID(cond));
}

void _poly_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex) {
  POLY_PRINT2(cond, mutex);
  trace.add_event(COND_WAIT, UTID_self(), UOID(cond));
}

void _poly_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex,
                          const struct timespec * abstime) {
  POLY_PRINT2(cond, mutex);
  assert(0);
}

void _poly_cond_broadcast(pthread_cond_t *cond) {
  POLY_PRINT1(cond);
  trace.add_event(COND_SIGNAL, UTID_self(), UOID(cond));
}

void _poly_cond_signal(pthread_cond_t *cond) {
  POLY_PRINT1(cond);
  trace.add_event(COND_SIGNAL, UTID_self(), UOID(cond));
}

void _poly_obj_read(int* addr) {
  POLY_PRINT1(addr);
  trace.add_event(OBJ_READ, UTID_self(), UOID(addr));
}

void _poly_obj_write(int* addr) {
  POLY_PRINT1(addr);
  trace.add_event(OBJ_WRITE, UTID_self(), UOID(addr));
}

void _poly_call_begin(char* fname, char* ptr) {
  POLY_PRINTs(fname, ptr);
  assert(0);
}

void _poly_call_end(char* fname, char* ptr) {
  POLY_PRINTs(fname, ptr);
  assert(0);
}

void _poly_inst_begin(int inst, int stat) {
  POLY_PRINTi(inst, stat);
  assert(0);
}

void _poly_inst_end(int inst, int stat, int retval) {
  POLY_PRINTi(inst, stat);
  assert(0);
}

