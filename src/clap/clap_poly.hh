/**
 *  @author Chao Wang <chaowang@vt.edu>
 *
 *  @date   8/20/2012
 *
 *  @brief
 *
 *  This is an implementation of the polygraph based predictive analysis
 *  algorithm. 
 *
 *  For every PThreads API function, or a function that is mentioned in a given
 *  type-state automaton, we add a wrapper before the call to that function.
 *
 *  Inside CLAP, function calls are intercepted by "clap_pthread.cc", which then
 *  distributes the calls to "clap_monitor.cc".  Depending on the environment
 *  parameter "CLAP_FLAG", these function calls are handled by one of the
 *  following packages:
 * 
 *      "clap_poly.cc"
 *
 *      "clap_typest.cc"
 *
 *      "clap_echo.cc"
 *
 *      "clap_none.cc"
 *
 *      etc.
 * 
 **/

#ifndef CLAP_POLY_HH
#define CLAP_POLY_HH

#include "clap_uniquetid.hh"

#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

#define POLY_PRINT()                                                 \
  printf("[tid = %-3d] %-20s(   )\n", UTID_self(), __FUNCTION__)        \
  
#define POLY_PRINTs(A,B)                                           \
  printf("[tid = %-3d] %-20s(%-3d)\n", UTID_self(),  A, UOID(B))   \
  
#define POLY_PRINTt(A)                                                  \
  printf("[tid = %-3d] %-20s(%-3d)\n", UTID_self(), __FUNCTION__, UTID(A)) \

#define POLY_PRINT1(A)                                                 \
  printf("[tid = %-3d] %-20s(%-3d)\n", UTID_self(), __FUNCTION__, UOID(A)) \
  
#define POLY_PRINT2(A,B)                                                \
  printf("[tid = %-3d] %-20s(%-3d,%-3d)\n", UTID_self(), __FUNCTION__, UOID(A), UOID(B)) \

#define POLY_PRINTi(A,B)                                                \
  printf("[tid = %-3d] %-20s(%-3d,%-3d)\n", UTID_self(), __FUNCTION__, A, B) \


void _poly_thread_start();
void _poly_thread_end();
void _poly_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg);
void _poly_thread_join(pthread_t thread, void **value_ptr);
void _poly_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
void _poly_mutex_destroy(pthread_mutex_t *mutex);
void _poly_mutex_lock(pthread_mutex_t *mutex);
void _poly_mutex_trylock(pthread_mutex_t *mutex);
void _poly_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);
void _poly_mutex_unlock(pthread_mutex_t *mutex);
void _poly_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
void _poly_cond_destroy(pthread_cond_t *cond);
void _poly_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
void _poly_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
void _poly_cond_broadcast(pthread_cond_t *cond);
void _poly_cond_signal(pthread_cond_t *cond);
void _poly_atomic_load(int* addr, const int mem_odr);
void _poly_atomic_store(int* addr, const int mem_odr);
void _poly_obj_read(int* addr);
void _poly_obj_write(int* addr);
void _poly_call_begin(char* fn, char* ptr);
void _poly_call_end(char* fn, char* ptr);
void _poly_inst_begin(int inst, int stat);
void _poly_inst_end(int inst, int stat, int retval);


#endif //ifndef CLAP_POLY_HH
