
#ifndef __CLAP_H__
#define __CLAP_H__

/**
 *  @author Chao Wang
 *
 *  @brief
 *
 *  For every API function in the PThreads library (NPTL), we have a
 *  wrapper function which, before calling the API function, always
 *  requests permission from the scheduler/model checker. 
 *  
 *  Let the prototype of a PThreads API function be
 *
 *      pthread_xxxx(args);
 *
 *  The corresponding wrapper function is
 *
 *      clap_xxxx(args);
 * 
 **/


#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/wait.h>
#include <poll.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
//#include "clap_atomic.hh"

/// @brief The first few parameters of clap routines are debugging info

#define CLAP_DBG_INFO          char* _file, int _line
#define CLAP_DBG_INFO_PARAM    _file, _line

#define ATOMIC_CALL 1//lu: for atomic function calls

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _MSC_VER 

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. Define CLAP_EXPORTS if you want to create DLL
//
# ifdef CLAP_EXPORTS
#   define CLAP_API __declspec(dllexport)
# else
#   define CLAP_API __declspec(dllimport)
# endif

#else
#   define CLAP_API 
#endif // _MSC_VER

  int  CLAP_API clap_thread_create( pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg);
  int  CLAP_API clap_thread_join(pthread_t thread, void **value_ptr);
  void  CLAP_API clap_thread_exit(void *retval);
  
  int  CLAP_API clap_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
  int  CLAP_API clap_mutex_destroy(pthread_mutex_t *mutex);
  int  CLAP_API clap_mutex_lock(pthread_mutex_t *mutex);
  int  CLAP_API clap_mutex_trylock(pthread_mutex_t *mutex);
  int  CLAP_API clap_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);  
  int  CLAP_API clap_mutex_unlock(pthread_mutex_t *mutex);  

  int  CLAP_API clap_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
  int  CLAP_API clap_cond_destroy(pthread_cond_t *cond);
  int  CLAP_API clap_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
  int  CLAP_API clap_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
  int  CLAP_API clap_cond_broadcast(pthread_cond_t *cond);
  int  CLAP_API clap_cond_signal(pthread_cond_t *cond); 

  int CLAP_API clap_rwlock_destroy(pthread_rwlock_t *rwlock);
  int CLAP_API clap_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
  int CLAP_API clap_rwlock_trywrlock(pthread_rwlock_t *rwlock);
  int CLAP_API clap_rwlock_wrlock(pthread_rwlock_t *rwlock);
  int CLAP_API clap_rwlock_rdlock(pthread_rwlock_t *rwlock);
  int CLAP_API clap_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
  int CLAP_API clap_rwlock_unlock(pthread_rwlock_t *rwlock);

  int  CLAP_API clap_atomic_load(int* addr, const int mem_odr);
  void CLAP_API clap_atomic_store(int* addr, const int val, const int mem_odr);

  void CLAP_API clap_load_pre  (int num_param, ...);
  void CLAP_API clap_load_post (int num_param, ...);

  void CLAP_API clap_store_pre (int num_param, ...);
  void CLAP_API clap_store_post(int num_param, ...);

  void CLAP_API clap_call_pre (int num_param, ...);
  void CLAP_API clap_call_post(int num_param, ...);

  void CLAP_API clap_inst_pre (int num_param, ...);
  void CLAP_API clap_inst_post(int num_param, ...);

  void CLAP_API tap_input_int(void* ptr, int num_bits);

#ifdef __cplusplus
}
#endif



#endif//__CLAP_H__
