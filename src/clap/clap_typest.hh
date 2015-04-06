/**
 *  @author Chao Wang <chaowang@vt.edu>
 *
 *  @date   9/2/2012
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
 *      "clap_typest.cc"
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

#ifndef __CLAP_TYPEST_H__
#define __CLAP_TYPEST_H__

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

#define TYPEST_PRINT()                                                  \
  printf("tid= %-3d type= %-16s\n", UTID_self(), __FUNCTION__+8)        \

#define TYPEST_PRINTs(A,B)                                              \
  printf("\ntid= %-3d type= %-16s obj= %d         method= %s\n", UTID_self(),  __FUNCTION__+8, UOID(B), A) \
  
#define TYPEST_PRINTt(A)                                                \
  printf("tid= %-3d type= %-16s child= %-3d\n", UTID_self(), __FUNCTION__+8, UTID(A)) \
  
#define TYPEST_PRINT1(A)                                                \
  printf("tid= %-3d type= %-16s obj= %d\n",UTID_self(), __FUNCTION__+8, UOID(A)) \
  
#define TYPEST_PRINT2(A,B)                                              \
  printf("tid= %-3d type= %-16s obj= %d obj2= %d\n", UTID_self(), __FUNCTION__+8, UOID(A), UOID(B)) \
  
#define TYPEST_PRINTi(A,B)                                              \
  printf("tid= %-3d type= %-16s obj= %d obj2= %d\n", UTID_self(), __FUNCTION__+8, A, B) \
  

void _typest_thread_start();
void _typest_thread_end();
void _typest_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg);
void _typest_thread_join(pthread_t thread, void **value_ptr);
void _typest_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
void _typest_mutex_destroy(pthread_mutex_t *mutex);
void _typest_mutex_lock(pthread_mutex_t *mutex);
void _typest_mutex_trylock(pthread_mutex_t *mutex);
void _typest_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);
void _typest_mutex_unlock(pthread_mutex_t *mutex);
void _typest_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
void _typest_cond_destroy(pthread_cond_t *cond);
void _typest_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
void _typest_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
void _typest_cond_broadcast(pthread_cond_t *cond);
void _typest_cond_signal(pthread_cond_t *cond);
void _typest_obj_read(int* addr);
void _typest_obj_write(int* addr);
void _typest_call_begin(char* fn, char* ptr);
void _typest_call_end(char* fn, char* ptr);
void _typest_inst_begin(int inst, int stat);
void _typest_inst_end(int inst, int stat, int retval);


#endif //ifndef CLAP_TYPEST_HH
