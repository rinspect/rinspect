#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <map>

using namespace std;

#define ECHO_PRINT()                                                    \
  printf("[tid= %8x] %-16s()\n", (unsigned)pthread_self(), __FUNCTION__);

#define ECHO_PRINTs(A,B)                                                \
  printf("[tid= %8x] %-16s( \"%s\", %0x)\n", (unsigned)pthread_self(), __FUNCTION__, \
         A, (unsigned int)B);

#define ECHO_PRINT1(A)                                                  \
  printf("[tid= %8x] %-16s(%0x)\n", (unsigned)pthread_self(), __FUNCTION__, \
         (unsigned)A);

#define ECHO_PRINT2(A,B)                                                \
  printf("[tid= %8x] %-16s(%0x, %0x)\n", (unsigned)pthread_self(), __FUNCTION__, \
         (unsigned)A,   (unsigned)B);

#define ECHO_PRINTi(A,B)                                                 \
  printf("[tid= %8x] %-16s(%d, %d)\n", (unsigned)pthread_self(), __FUNCTION__, \
         (unsigned)A, (unsigned)B);

void _echo_thread_start();
void _echo_thread_end();
void _echo_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg);
void _echo_thread_join(pthread_t thread, void **value_ptr);
void _echo_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
void _echo_mutex_destroy(pthread_mutex_t *mutex);
void _echo_mutex_lock(pthread_mutex_t *mutex);
void _echo_mutex_trylock(pthread_mutex_t *mutex);
void _echo_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);
void _echo_mutex_unlock(pthread_mutex_t *mutex);
void _echo_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
void _echo_cond_destroy(pthread_cond_t *cond);
void _echo_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
void _echo_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
void _echo_cond_broadcast(pthread_cond_t *cond);
void _echo_cond_signal(pthread_cond_t *cond);
void _echo_obj_read(int* addr);
void _echo_obj_write(int* addr);
void _echo_call_begin(char* fn, char* ptr);
void _echo_call_end(char* fn, char* ptr);
void _echo_inst_begin(int inst, int stat);
void _echo_inst_end(int inst, int stat, int);


