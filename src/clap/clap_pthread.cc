#include "clap_pthread.hh"
#include "clap_monitor.hh"
#include "clap_uniquetid.hh"

#include <iostream>
#include <fstream>


//----------------------------------------------------------------------------
// Start of the implementation of a scoped lock
//----------------------------------------------------------------------------
pthread_mutex_t _ClapLock_m = PTHREAD_MUTEX_INITIALIZER;
// to ensure that clap_* functions are sequentialized
class _ClapLock {
public:
  _ClapLock()  { pthread_mutex_lock   (&_ClapLock_m ); }
  ~_ClapLock() { pthread_mutex_unlock (&_ClapLock_m ); }
};

#define CLAP_SCOPED_LOCK  _ClapLock _ClapLock_dummy;  clap_main_start();
#define CLAP_ACQ_LOCK  pthread_mutex_lock(&_ClapLock_m); clap_main_start();
#define CLAP_REL_LOCK  pthread_mutex_unlock(&_ClapLock_m); clap_main_start();

//----------------------------------------------------------------------------
// End of the implementation of a scoped lock
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// has the main_thread_end routine be registered?
//----------------------------------------------------------------------------
void clap_thread_end();
void clap_main_start()
{
  static int flag_atexit_called = 0;
  if (flag_atexit_called == 0) {
    if (monitor_thread_start == NULL) {
      clap_monitor_init();
    }
    monitor_thread_start();
    atexit(clap_thread_end);
    flag_atexit_called = 1;
  }
}
//----------------------------------------------------------------------------
// end of the main_thread_end callback
//----------------------------------------------------------------------------


void clap_thread_start()
{
  CLAP_SCOPED_LOCK; 
  monitor_thread_start();
  /*
  if (flag_atexit_called == 0) {
    //the function will be called before main thread exit
    atexit( clap_thread_end );  
    flag_atexit_called = 1;
  }
  */
}

void clap_thread_end()
{
  CLAP_SCOPED_LOCK; 
  monitor_thread_end();
}

void CLAP_THREAD_END(void*) 
{
  clap_thread_end();
}

void* CLAP_THREAD_ROUTINE(void* arg) 
{
  void* res = NULL;

  void  **args = (void**) arg;
  void *(*actual_routine)(void*) = (void*(*)(void*)) args[0];
  void   *actual_routine_arg = args[1];
  pthread_t parent_thrd = (pthread_t) args[2];
  int *flag = (int*) args[3];

  pthread_t this_thrd = pthread_self();
  unique_thread_add(this_thrd, parent_thrd);
  (*flag) = 1;  // end of unique_thread_add() 

  clap_thread_start();
  {
    // register cleanup routine (for normall or cancelled exit)
    pthread_cleanup_push(CLAP_THREAD_END, (void*)0);
    // execute the thread routine
    res = actual_routine(actual_routine_arg);
    // 1 means leave the cleanup routine in the system 
    pthread_cleanup_pop(1);
  }

  return res;
}

int  CLAP_API clap_thread_create( pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg)
{
  CLAP_SCOPED_LOCK; 
  { 
    int res; 
    void **args = (void**)malloc(sizeof(void*) * 8);
    int flag_child_started = 0;
    args[0] = (void*)start_routine;
    args[1] = arg;
    args[2] = (void*)pthread_self();
    args[3] = (void*)&flag_child_started;

    //add this thread into the pool
    unique_thread_get_tid(pthread_self());

    res = pthread_create(thread, attr, CLAP_THREAD_ROUTINE, args);

    //wait for child thread to be added to the ppl
    while(flag_child_started == 0) ; 

    monitor_thread_create(thread, attr, start_routine, arg);
    return res;
  }
}

int  CLAP_API clap_thread_join(pthread_t thread, void **value_ptr)
{
  int res = pthread_join(thread, value_ptr);
  { 
    CLAP_SCOPED_LOCK; 
    monitor_thread_join(thread, value_ptr);
  }
  return res;
}

void  CLAP_API clap_thread_exit(void *retval)
{
  /*  chao:  do nothing
  { 
    CLAP_SCOPED_LOCK; 
    monitor_thread_end();
  }
  */
  pthread_exit(retval);
}

int  CLAP_API clap_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr)
{
  CLAP_SCOPED_LOCK; 
  { 
    int res = pthread_mutex_init(mutex, attr);
    monitor_mutex_init(mutex,attr);
    return res;
  }
}

int  CLAP_API clap_mutex_destroy(pthread_mutex_t *mutex)
{
  CLAP_SCOPED_LOCK; 
  { 
    monitor_mutex_destroy(mutex);
    int res = pthread_mutex_destroy(mutex);
    return res;
  }
}

int  CLAP_API clap_mutex_lock(pthread_mutex_t *mutex)
{
  int res = pthread_mutex_lock(mutex);
  {
    CLAP_SCOPED_LOCK;
    monitor_mutex_lock(mutex);
  }
  return res;
}

int  CLAP_API clap_mutex_trylock(pthread_mutex_t *mutex)
{
  int res = pthread_mutex_trylock(mutex);
  if (res) { 
    CLAP_SCOPED_LOCK; 
    monitor_mutex_lock(mutex);
  }
  return res;
}

int  CLAP_API clap_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime)  
{
  int res = pthread_mutex_timedlock(mutex, abstime);
  if (res) { 
    CLAP_SCOPED_LOCK; 
    monitor_mutex_lock(mutex);
  }
  return res;
}

int  CLAP_API clap_mutex_unlock(pthread_mutex_t *mutex)  
{
  CLAP_SCOPED_LOCK; 
  { 
    int res = pthread_mutex_unlock(mutex);
    monitor_mutex_unlock(mutex);
    return res;
  }
}


int  CLAP_API clap_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr)
{
  CLAP_SCOPED_LOCK; 
  { 
    int res = pthread_cond_init(cond, attr);
    monitor_cond_init(cond, attr);
    return res;
  }
}

int  CLAP_API clap_cond_destroy(pthread_cond_t *cond)
{
  CLAP_SCOPED_LOCK; 
  { 
    monitor_cond_destroy(cond);
    int res = pthread_cond_destroy(cond);
    return res;
  }
}

int  CLAP_API clap_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex)
{
  {
    CLAP_SCOPED_LOCK; 
    monitor_mutex_unlock(mutex);
  }

  int res = pthread_cond_wait(cond, mutex);

  { 
    CLAP_SCOPED_LOCK; 
    monitor_mutex_lock(mutex);
    monitor_cond_wait(cond, mutex);
  }

  return res;
}

int  CLAP_API clap_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime)
{
  int res = pthread_cond_timedwait(cond, mutex, abstime);
  { 
    CLAP_SCOPED_LOCK; 
    monitor_cond_wait(cond, mutex);
  }
  return res;
}

int  CLAP_API clap_cond_broadcast(pthread_cond_t *cond)
{
  CLAP_SCOPED_LOCK; 
  { 
    int res = pthread_cond_broadcast(cond);
    monitor_cond_broadcast(cond);
    return res;
  }
}

int  CLAP_API clap_cond_signal(pthread_cond_t *cond)
{ 
  CLAP_SCOPED_LOCK; 
  {
    int res = pthread_cond_signal(cond);
    monitor_cond_signal(cond);
    return res;
  }
}

int CLAP_API clap_rwlock_destroy(pthread_rwlock_t *rwlock)
{
  int res = pthread_rwlock_destroy(rwlock);
  return res;
}

int CLAP_API clap_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr)
{
  int res = pthread_rwlock_init(rwlock, attr);
  return res;
}

int CLAP_API clap_rwlock_trywrlock(pthread_rwlock_t *rwlock)
{
  int res = pthread_rwlock_trywrlock(rwlock);
  return res;
}

int CLAP_API clap_rwlock_wrlock(pthread_rwlock_t *rwlock)
{
  int res = pthread_rwlock_wrlock(rwlock);
  return res;
}

int CLAP_API clap_rwlock_rdlock(pthread_rwlock_t *rwlock)
{
  int res = pthread_rwlock_rdlock(rwlock);
  return res;
}

int CLAP_API clap_rwlock_tryrdlock(pthread_rwlock_t *rwlock)
{
  int res = pthread_rwlock_tryrdlock(rwlock);
  return res;
}

int CLAP_API clap_rwlock_unlock(pthread_rwlock_t *rwlock)
{
  int res = pthread_rwlock_unlock(rwlock);
  return res;
}

int CLAP_API clap_atomic_load(int* addr, const int mem_odr)
{
  CLAP_SCOPED_LOCK;
  {
    monitor_atomic_load(addr, mem_odr);
    return *addr;
  }
}

void CLAP_API clap_atomic_store(int* addr, const int val, const int mem_odr)
{
  CLAP_SCOPED_LOCK;
  {
    *addr = val;
    monitor_atomic_store(addr, mem_odr);
  }
}

void clap_obj_read(int* addr)
{
  monitor_obj_read(addr);
}

void clap_obj_write(int* addr)
{
  monitor_obj_write(addr);
}

void CLAP_API clap_load_pre(int num_param, ...)
{
  // acquire the lock to be released in "load_post"
  CLAP_ACQ_LOCK;
  {
    assert(num_param == 1);
    va_list ap;
    int *addr;
    va_start(ap, num_param);
    addr = va_arg(ap, int*);
    va_end(ap);
    ////
    clap_obj_read(addr);
  }
}

void CLAP_API clap_load_post (int num_param, ...)
{
  // release the lock acquired in "load_pre"
  CLAP_REL_LOCK;
}

void CLAP_API clap_store_pre (int num_param, ...)
{
  // acquire the lock to be released in "store_post"
  CLAP_ACQ_LOCK; 
  {
    assert(num_param == 1);
    va_list ap;
    int *addr;
    va_start(ap, num_param);
    addr = va_arg(ap, int*);
    va_end(ap);
    ////
    clap_obj_write(addr);
  }
}

void CLAP_API clap_store_post(int num_param, ...)
{
  // release the lock acquired in "store_pre"
  CLAP_REL_LOCK;
}


#if ATOMIC_CALL
pthread_mutex_t call_lock = PTHREAD_MUTEX_INITIALIZER;
#endif


void CLAP_API clap_call_pre(int num_param, ...)
{
#if !ATOMIC_CALL
	CLAP_SCOPED_LOCK;
#endif

#if ATOMIC_CALL
	pthread_mutex_lock(&call_lock);
#endif

  {
    va_list ap;
    va_start(ap, num_param);
    char *fname = va_arg(ap, char*);
    char *ptr = 0;
    if (num_param >= 2) {
      ptr = va_arg(ap, char*);
    }
    va_end(ap);
    ////
    monitor_call_begin(fname, ptr);
  }
}

void CLAP_API clap_call_post (int num_param, ...)
{
#if !ATOMIC_CALL
	CLAP_SCOPED_LOCK;
#endif

  {
    va_list ap;
    va_start(ap, num_param);
    char *fname = va_arg(ap, char*);
    char *ptr = 0;
    if (num_param >= 2) {
      ptr = va_arg(ap, char*);
    }
    va_end(ap);
    ////
    monitor_call_end(fname, ptr);
  }

#if ATOMIC_CALL
	pthread_mutex_unlock(&call_lock);
#endif

}

void CLAP_API clap_inst_pre(int num_param, ...)
{
  CLAP_SCOPED_LOCK; 
  {
    assert(num_param >= 1);
    va_list ap;
    int inst, stat;
    va_start(ap, num_param);
    inst = va_arg(ap, int);
    stat = va_arg(ap, int);
    va_end(ap);
    ////
    monitor_inst_begin(inst,stat);
  }
}

void CLAP_API clap_inst_post (int num_param, ...)
{
  CLAP_SCOPED_LOCK; 
  {
    assert(num_param >= 1);
    va_list ap;
    int inst, stat, retval;
    va_start(ap, num_param);
    inst = va_arg(ap, int);
    stat = va_arg(ap, int);
    retval = va_arg(ap, int);
    va_end(ap);
    ////
    monitor_inst_end(inst,stat,retval);
  }
}


void CLAP_API tap_input_int(void* addr, int nBit)
{
  CLAP_SCOPED_LOCK; 
  {
    //1. create a new 'havoc_v#' variable
    static int havoc_v_cnt = 0;
    char havoc_v[64];
    sprintf(havoc_v,"havoc_v%d", ++havoc_v_cnt);

    //2. read the value of 'havoc_v#' from file
    bool is_available = false;
    long hvValue;
    {
      ifstream hin("tap.input.txt");
      if (!hin.fail()) {
        while(!hin.eof()) {
          string hvName;
          string hvEqv;
          int    hvNum;
          hin >> hvName >> hvEqv >> hvNum;
          if (!strcmp(hvName.c_str(),havoc_v) && hvEqv == "=") {
            is_available = true;
            hvValue = hvNum;

            if (true) {
              cout << "\n HAVOC: " << havoc_v << " = " << hvValue << "\n";
            }
          }
        }
      }
    }
    
    //3. change the value of *(addr)
    if (is_available)  {
      if (nBit/8 == sizeof(char)) 
        *((char*)addr) = (char)hvValue; 
      else if (nBit/8 == sizeof(short))
        *((short*)addr) = (short)hvValue; 
      else if (nBit/8 == sizeof(int))
        *((int*)addr) = (int)hvValue;  
      else if (nBit/8 == sizeof(long))
        *((long*)addr) = (long)hvValue;  
      else {
        assert(0);//type not yet supported
      }
    }

  }

}
