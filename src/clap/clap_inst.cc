#include "clap_inst.hh"
#include "clap_uniquetid.hh"
#include <iostream>
#include <fstream>

ofstream toTrace("trace.txt");

  
void _inst_thread_start()
{
  INST_PRINT();
}

void _inst_thread_end()
{
  INST_PRINT();
}

void _inst_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg)
{
  INST_PRINT1(*thread);
}

void _inst_thread_join(pthread_t thread, void **value_ptr)
{
  INST_PRINT1(thread);
}

void _inst_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr)
{
  INST_PRINT1(mutex);
}

void _inst_mutex_destroy(pthread_mutex_t *mutex)
{
  INST_PRINT1(mutex);
}

void _inst_mutex_lock(pthread_mutex_t *mutex)
{
  INST_PRINT1(mutex);
}

void _inst_mutex_trylock(pthread_mutex_t *mutex)
{
  INST_PRINT1(mutex);
}

void _inst_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime)  
{
  INST_PRINT1(mutex);
}

void _inst_mutex_unlock(pthread_mutex_t *mutex)  
{
  INST_PRINT1(mutex);
}

void _inst_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr)
{
  INST_PRINT1(cond);
}

void _inst_cond_destroy(pthread_cond_t *cond)
{
  INST_PRINT1(cond);
}

void _inst_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex)
{
  INST_PRINT2(cond, mutex);
}

void _inst_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime)
{
  INST_PRINT2(cond, mutex);
}

void _inst_cond_broadcast(pthread_cond_t *cond)
{
  INST_PRINT1(cond);
}

void _inst_cond_signal(pthread_cond_t *cond)
{ 
  INST_PRINT1(cond);
}

void _inst_obj_read(int* addr)
{
  INST_PRINT1(addr);  
}

void _inst_obj_write(int* addr)
{
  INST_PRINT1(addr);  
}

void _inst_call_begin(char* fname, char* ptr)
{
  INST_PRINTs(fname);  
}

void _inst_call_end(char* fname, char* ptr)
{
  INST_PRINTs(fname);  
}

void _inst_inst_begin(int inst, int stat)
{
  INST_PRINTi(inst, stat, 0);
}

void _inst_inst_end(int inst, int stat, int retval)
{
  INST_PRINTi(inst, 0, retval);
}

