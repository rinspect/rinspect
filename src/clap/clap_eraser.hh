#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <map>
using namespace std;

#define ERASER_PRINT()                                                    \
  printf("[tid= %8x] %s()\n", (unsigned)pthread_self(), __FUNCTION__);

#define ERASER_PRINT1(A)                                                  \
  printf("[tid= %8x] %s(%0x)\n", (unsigned)pthread_self(), __FUNCTION__, \
         (unsigned)A);

#define ERASER_PRINT2(A,B)                                                \
  printf("[tid= %8x] %s(%0x, %0x)\n", (unsigned)pthread_self(), __FUNCTION__, \
         (unsigned)A,   (unsigned)B);

void _eraser_thread_start();
void _eraser_thread_end();
void _eraser_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg);
void _eraser_thread_join(pthread_t thread, void **value_ptr);
void _eraser_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
void _eraser_mutex_destroy(pthread_mutex_t *mutex);
void _eraser_mutex_lock(pthread_mutex_t *mutex);
void _eraser_mutex_trylock(pthread_mutex_t *mutex);
void _eraser_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);
void _eraser_mutex_unlock(pthread_mutex_t *mutex);
void _eraser_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
void _eraser_cond_destroy(pthread_cond_t *cond);
void _eraser_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
void _eraser_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
void _eraser_cond_broadcast(pthread_cond_t *cond);
void _eraser_cond_signal(pthread_cond_t *cond);
void _eraser_obj_read(int* addr);
void _eraser_obj_write(int* addr);
void _eraser_call_begin(char* fn, char* ptr);
void _eraser_call_end(char* fn, char* ptr);
void _eraser_inst_begin(int inst, int stat);
void _eraser_inst_end(int inst, int stat, int retval);


