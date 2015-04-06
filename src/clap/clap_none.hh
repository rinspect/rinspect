#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/*
// for debugging only

#define NONE_PRINT()                                                    \
  printf("[tid= %8x] %s()\n", (unsigned)pthread_self(), __FUNCTION__);

#define NONE_PRINT1(A)                                                  \
  printf("[tid= %8x] %s(%0x)\n", (unsigned)pthread_self(), __FUNCTION__, \
         (unsigned)A);

#define NONE_PRINT2(A,B)                                                \
  printf("[tid= %8x] %s(%0x, %0x)\n", (unsigned)pthread_self(), __FUNCTION__, \
         (unsigned)A,   (unsigned)B);
*/

#define NONE_PRINT()  
#define NONE_PRINT1(A)
#define NONE_PRINT2(A,B)


void _none_thread_start();
void _none_thread_end();
void _none_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg);
void _none_thread_join(pthread_t thread, void **value_ptr);
void _none_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
void _none_mutex_destroy(pthread_mutex_t *mutex);
void _none_mutex_lock(pthread_mutex_t *mutex);
void _none_mutex_trylock(pthread_mutex_t *mutex);
void _none_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);
void _none_mutex_unlock(pthread_mutex_t *mutex);
void _none_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
void _none_cond_destroy(pthread_cond_t *cond);
void _none_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
void _none_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
void _none_cond_broadcast(pthread_cond_t *cond);
void _none_cond_signal(pthread_cond_t *cond);
void _none_obj_read(int* addr);
void _none_obj_write(int* addr);
void _none_call_begin(char* fn, char* ptr);
void _none_call_end(char* fn, char* ptr);
void _none_inst_begin(int inst, int stat);
void _none_inst_end(int inst, int stat, int retval);


