/**
 *  @author Chao Wang <chaowang@vt.edu>
 *
 *  @date   11/30/2012
 *
 *  @brief
 *
 *  This is an implementation of the type-state automaton checking, predicting,
 *  and repair tool.  
 *
 *  For every PThreads API function, or a function that is mentioned in a given
 *  type-state automaton, we add a wrapper before the call to that function.
 *
 *  Inside CLAP, function calls are intercepted by "clap_pthread.cc", which then
 *  distributes the calls to "clap_monitor.cc".  Depending on the environment
 *  parameter "CLAP_FLAG", these function calls are handled by one of the
 *  following packages:
 * 
 *      "clap_auto.cc"
 *
 *      "clap_poly.cc"
 *
 *      "clap_echo.cc"
 *
 *      "clap_none.cc"
 *
 *      etc.
 * 
 **/

#ifndef __CLAP_AUTO_H__
#define __CLAP_AUTO_H__

#include "clap_uniquetid.hh"

#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

#define AUTO_PRINT()                                                  \
  printf("tid= %-3d type= %-16s\n", UTID_self(), __FUNCTION__+6)        \

#define AUTO_PRINTs(A,B)                                              \
  printf("\ntid= %-3d type= %-16s obj= %d         method= %s\n", UTID_self(),  __FUNCTION__+6, UOID(B), A) \
  
#define AUTO_PRINTt(A)                                                \
  printf("tid= %-3d type= %-16s child= %-3d\n", UTID_self(), __FUNCTION__+6, UTID(A)) \
  
#define AUTO_PRINT1(A)                                                \
  printf("tid= %-3d type= %-16s obj= %d\n",UTID_self(), __FUNCTION__+6, UOID(A)) \
  
#define AUTO_PRINT2(A,B)                                              \
  printf("tid= %-3d type= %-16s obj= %d obj2= %d\n", UTID_self(), __FUNCTION__+6, UOID(A), UOID(B)) \
  
#define AUTO_PRINTi(A,B)                                              \
  printf("tid= %-3d type= %-16s obj= %d obj2= %d\n", UTID_self(), __FUNCTION__+6, A, B) \
  

void _auto_thread_start();
void _auto_thread_end();
void _auto_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg);
void _auto_thread_join(pthread_t thread, void **value_ptr);
void _auto_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
void _auto_mutex_destroy(pthread_mutex_t *mutex);
void _auto_mutex_lock(pthread_mutex_t *mutex);
void _auto_mutex_trylock(pthread_mutex_t *mutex);
void _auto_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);
void _auto_mutex_unlock(pthread_mutex_t *mutex);
void _auto_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
void _auto_cond_destroy(pthread_cond_t *cond);
void _auto_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
void _auto_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
void _auto_cond_broadcast(pthread_cond_t *cond);
void _auto_cond_signal(pthread_cond_t *cond);
void _auto_obj_read(int* addr);
void _auto_obj_write(int* addr);
void _auto_call_begin(char* fn, char* ptr);
void _auto_call_end(char* fn, char* ptr);
void _auto_inst_begin(int inst, int stat);
void _auto_inst_end(int inst, int stat, int retval);

#endif //ifndef CLAP_AUTO_HH
