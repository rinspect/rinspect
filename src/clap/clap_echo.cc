#include "clap_echo.hh"
#include "clap_uniquetid.hh"

  
void _echo_thread_start()
{
  ECHO_PRINT();
}

void _echo_thread_end()
{
  ECHO_PRINT();
}

void _echo_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg)
{
  ECHO_PRINT1(*thread);
}

void _echo_thread_join(pthread_t thread, void **value_ptr)
{
  ECHO_PRINT1(thread);
}

void _echo_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr)
{
  ECHO_PRINT1(mutex);
}

void _echo_mutex_destroy(pthread_mutex_t *mutex)
{
  ECHO_PRINT1(mutex);
}

void _echo_mutex_lock(pthread_mutex_t *mutex)
{
  ECHO_PRINT1(mutex);
}

void _echo_mutex_trylock(pthread_mutex_t *mutex)
{
  ECHO_PRINT1(mutex);
}

void _echo_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime)  
{
  ECHO_PRINT1(mutex);
}

void _echo_mutex_unlock(pthread_mutex_t *mutex)  
{
  ECHO_PRINT1(mutex);
}

void _echo_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr)
{
  ECHO_PRINT1(cond);
}

void _echo_cond_destroy(pthread_cond_t *cond)
{
  ECHO_PRINT1(cond);
}

void _echo_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex)
{
  ECHO_PRINT2(cond, mutex);
}

void _echo_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime)
{
  ECHO_PRINT2(cond, mutex);
}

void _echo_cond_broadcast(pthread_cond_t *cond)
{
  ECHO_PRINT1(cond);
}

void _echo_cond_signal(pthread_cond_t *cond)
{ 
  ECHO_PRINT1(cond);
}

void _echo_obj_read(int* addr)
{
  ECHO_PRINT1(addr);  
}

void _echo_obj_write(int* addr)
{
  ECHO_PRINT1(addr);  
}

void _echo_call_begin(char* fname, char* ptr)
{
  ECHO_PRINTs(fname, ptr);  
}

void _echo_call_end(char* fname, char* ptr)
{
  ECHO_PRINTs(fname, ptr);  
}

void _echo_inst_begin(int inst, int stat)
{
  ECHO_PRINTi(inst, stat);  
}

void _echo_inst_end(int inst, int stat, int retval)
{
  ECHO_PRINTi(inst, stat);
}

