#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <map>

using namespace std;

#define INST_PRINT()   
#define INST_PRINTs(A) 
#define INST_PRINT1(A) 
#define INST_PRINT2(A,B) 
/*
#define INST_PRINTi(A,B) \   
  printf("%d %d %d\n", (unsigned)unique_thread_get_tid(pthread_self()), \
       (unsigned)A, (unsigned)B);
*/
#define INST_PRINTi(A,B,C)                                           \
  toTrace << ((int)unique_thread_get_tid(pthread_self())) << " "    \
  << ((int)A)  << " " << ((int)B) << " " << ((int)C) << endl


void _inst_thread_start();
void _inst_thread_end();
void _inst_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg);
void _inst_thread_join(pthread_t thread, void **value_ptr);
void _inst_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
void _inst_mutex_destroy(pthread_mutex_t *mutex);
void _inst_mutex_lock(pthread_mutex_t *mutex);
void _inst_mutex_trylock(pthread_mutex_t *mutex);
void _inst_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);
void _inst_mutex_unlock(pthread_mutex_t *mutex);
void _inst_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
void _inst_cond_destroy(pthread_cond_t *cond);
void _inst_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
void _inst_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
void _inst_cond_broadcast(pthread_cond_t *cond);
void _inst_cond_signal(pthread_cond_t *cond);
void _inst_obj_read(int* addr);
void _inst_obj_write(int* addr);
void _inst_call_begin(char* fn, char* ptr);
void _inst_call_end(char* fn, char* ptr);
void _inst_inst_begin(int inst, int stat);
void _inst_inst_end(int inst, int stat, int retval);


