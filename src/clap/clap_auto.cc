#include "clap_auto.hh"

//defined by test (client) program for each Class under investigation
extern "C" void* clap_extract_state(void *obj);

__attribute__((weak)) void* clap_extract_state(void *obj) {
  assert( 0 && "Please re-define void* clap_extract_state(void* obj) in client program!\n" );
}


void _auto_thread_start() {
  AUTO_PRINT();
}

void _auto_thread_end() {
  AUTO_PRINT();
}

void _auto_thread_create(pthread_t * thread, const pthread_attr_t * attr,
                           void *(*start_routine)(void*), void * arg) {
  AUTO_PRINTt(*thread);
}

void _auto_thread_join(pthread_t thread, void **value_ptr) {
  AUTO_PRINTt(thread);
}

void _auto_mutex_init(pthread_mutex_t * mutex, 
                        const pthread_mutexattr_t * attr) {
  AUTO_PRINT1(mutex);
}

void _auto_mutex_destroy(pthread_mutex_t *mutex) {
  AUTO_PRINT1(mutex);
}

void _auto_mutex_lock(pthread_mutex_t *mutex) {
  AUTO_PRINT1(mutex);
}

void _auto_mutex_trylock(pthread_mutex_t *mutex) {
  AUTO_PRINT1(mutex);
}

void _auto_mutex_timedlock(pthread_mutex_t *mutex,
                             const struct timespec *abstime) {
  AUTO_PRINT1(mutex);
}

void _auto_mutex_unlock(pthread_mutex_t *mutex) {
  AUTO_PRINT1(mutex);
}

void _auto_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr) {
  AUTO_PRINT1(cond);
}

void _auto_cond_destroy(pthread_cond_t *cond) {
  AUTO_PRINT1(cond);
}

void _auto_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex) {
  AUTO_PRINT2(cond, mutex);
}

void _auto_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex,
                            const struct timespec * abstime) {
  AUTO_PRINT2(cond, mutex);
}

void _auto_cond_broadcast(pthread_cond_t *cond) {
  AUTO_PRINT1(cond);
}

void _auto_cond_signal(pthread_cond_t *cond) {
  AUTO_PRINT1(cond);
}

void _auto_obj_read(int* addr) {
  AUTO_PRINT1(addr);
}

void _auto_obj_write(int* addr) {
  AUTO_PRINT1(addr);
}

void _auto_call_begin(char* fname, char* ptr) {
  AUTO_PRINTs(fname, ptr);
  /* chao: 11/30/2012
  printf("I demo this to Sree Ram and Sal!\n");
  if (fname != NULL) {
    printf(" Sree Ram wants to see the method name : %s \n", fname);
    printf(" Sal wants to see the address of the object: %d \n", ptr); 
  }
  */
  if (!strncmp("Sample::", fname, 8)) {
    vector<pair<string,int> >* state;
    state = (vector<pair<string,int> >*) clap_extract_state( ptr );
    for(unsigned int i=0; i<state->size(); i++) {
      printf("State.%s() = %d\n", (*state)[i].first.c_str(), (*state)[i].second);
    }
    delete state;
  }
  //-------------------------------------------------------------------
}

void _auto_call_end(char* fname, char* ptr) {
  AUTO_PRINTs(fname, ptr);

  if (!strncmp("Sample::", fname, 8)) {
    vector<pair<string,int> >* state;
    state = (vector<pair<string,int> >*) clap_extract_state( ptr );
    for(unsigned int i=0; i<state->size(); i++) {
      printf("State.%s() = %d\n", (*state)[i].first.c_str(), (*state)[i].second);
    }
    delete state;
  }
  //-------------------------------------------------------------------

}

void _auto_inst_begin(int inst, int stat) {
  AUTO_PRINTi(inst, stat);
}

void _auto_inst_end(int inst, int stat, int retval) {
  AUTO_PRINTi(inst, stat);
}
