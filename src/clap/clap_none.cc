#include "clap_none.hh"
  
void _none_thread_start()
{
  NONE_PRINT();
}

void _none_thread_end()
{
  NONE_PRINT();
}

void _none_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg)
{
  NONE_PRINT1(*thread);
}

void _none_thread_join(pthread_t thread, void **value_ptr)
{
  NONE_PRINT1(thread);
}

void _none_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr)
{
  NONE_PRINT1(mutex);
}

void _none_mutex_destroy(pthread_mutex_t *mutex)
{
  NONE_PRINT1(mutex);
}

void _none_mutex_lock(pthread_mutex_t *mutex)
{
  NONE_PRINT1(mutex);
}

void _none_mutex_trylock(pthread_mutex_t *mutex)
{
  NONE_PRINT1(mutex);
}

void _none_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime)  
{
  NONE_PRINT1(mutex);
}

void _none_mutex_unlock(pthread_mutex_t *mutex)  
{
  NONE_PRINT1(mutex);
}

void _none_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr)
{
  NONE_PRINT1(cond);
}

void _none_cond_destroy(pthread_cond_t *cond)
{
  NONE_PRINT1(cond);
}

void _none_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex)
{
  NONE_PRINT2(cond, mutex);
}

void _none_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime)
{
  NONE_PRINT2(cond, mutex);
}

void _none_cond_broadcast(pthread_cond_t *cond)
{
  NONE_PRINT1(cond);
}

void _none_cond_signal(pthread_cond_t *cond)
{ 
  NONE_PRINT1(cond);
}

void _none_obj_read(int* addr)
{
  NONE_PRINT1(addr);  
}

void _none_obj_write(int* addr)
{
  NONE_PRINT1(addr);  
}

void _none_call_begin(char* fname, char* ptr)
{
  NONE_PRINT1(fname);  
}

void _none_call_end(char* fname, char* ptr)
{
  NONE_PRINT1(fname);  
}

void _none_inst_begin(int inst, int stat)
{
  NONE_PRINT2(inst, stat);
}

void _none_inst_end(int inst, int stat, int retval)
{
  NONE_PRINT2(inst, stat);
}


