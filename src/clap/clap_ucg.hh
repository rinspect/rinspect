#ifndef CLAP_UCG_HH
#define CLAP_UCG_HH

#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <fstream>
#include "clap_ucg_edge.hh"

using namespace std;
/*
#define UCG_PRINT()                                                    \
  printf("[tid= %8x] %s()\n", (unsigned)pthread_self(), __FUNCTION__);

#define UCG_PRINT1(A)                                                  \
  printf("[tid= %8x] %s(%0x)\n", (unsigned)pthread_self(), __FUNCTION__, \
         (unsigned)A);

#define UCG_PRINT2(A,B)                                                \
  printf("[tid= %8x] %s(%0x, %0x)\n", (unsigned)pthread_self(), __FUNCTION__, \
         (unsigned)A,   (unsigned)B);
*/

#define UCG_PRINT()                                                    \
  printf("[tid = %d] %s()\n", map_tid((unsigned)pthread_self()), __FUNCTION__);

#define UCG_PRINT1(A)                                                  \
  printf("[tid = %d] %s(%u)\n", map_tid((unsigned)pthread_self()), __FUNCTION__, \
         (unsigned)A);

#define UCG_PRINT2(A,B)                                                \
  printf("[tid = %d] %s(%u, %u)\n", map_tid((unsigned)pthread_self()), __FUNCTION__, \
         (unsigned)A,   (unsigned)B);



/*
event_t event_create();
int map_mutex(pthread_mutex_t *mutex);
int map_obj(int *addr);
int map_cond(pthread_cond_t *cond);
locks_held_t get_locks_held(pthread_t *thread);
*/
//extern void ucg_edge(map<unsigned, vector<event_t> > thread_routine, vector<vector<int> > edge);


void _ucg_thread_start();
void _ucg_thread_end();
void _ucg_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg);
void _ucg_thread_join(pthread_t thread, void **value_ptr);
void _ucg_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
void _ucg_mutex_destroy(pthread_mutex_t *mutex);
void _ucg_mutex_lock(pthread_mutex_t *mutex);
void _ucg_mutex_trylock(pthread_mutex_t *mutex);
void _ucg_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);
void _ucg_mutex_unlock(pthread_mutex_t *mutex);
void _ucg_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
void _ucg_cond_destroy(pthread_cond_t *cond);
void _ucg_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
void _ucg_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
void _ucg_cond_broadcast(pthread_cond_t *cond);
void _ucg_cond_signal(pthread_cond_t *cond);
void _ucg_atomic_load(int* addr, const int mem_odr);
void _ucg_atomic_store(int* addr, const int mem_odr);
void _ucg_obj_read(int* addr);
void _ucg_obj_write(int* addr);
void _ucg_call_begin(char* fn, char* ptr);
void _ucg_call_end(char* fn, char* ptr);
void _ucg_inst_begin(int inst, int stat);
void _ucg_inst_end(int inst, int stat, int retval);


#endif //CLAP_UCG_HH
