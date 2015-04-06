
#ifndef __INSPECTOR_CLAP_H__
#define __INSPECTOR_CLAP_H__

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
 *      clap_xxxx(__FILE__,__LINE__,args);
 * 
 **/

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/wait.h>
#include <poll.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <map>
#include <string>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <sstream>

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

   /*
    * Structure describing a barrier
    */
   typedef struct _barrier_clap {
      pthread_mutex_t      mutex;
      pthread_cond_t       cond;
      int                  counter;
      int                  threshold;
   } BARRIER_CLAP;

   /*
    * Structure describing a read-write lock.
    */
   typedef struct rwlock_tag {
      pthread_mutex_t     mutex;
      pthread_cond_t      read;           /* wait for read */
      pthread_cond_t      write;          /* wait for write */
      int                 valid;          /* set when valid */
      int                 r_active;       /* readers active */
      int                 w_active;       /* writer active */
      int                 r_wait;         /* readers waiting */
      int                 w_wait;         /* writers waiting */
   } RWLOCK_CLAP;

  
  /*
   * Structure describing a semaphore.
   */
  typedef struct sem_tag {
    int value;
    //  int wakeups;
    pthread_mutex_t lock;
    pthread_cond_t  cond;
  } SEM_CLAP;


  void CLAP_API clap_thread_start();
  void CLAP_API clap_thread_end();

  void  CLAP_API clap_atom_start();
  void  CLAP_API clap_atom_end();

  void CLAP_API clap_watch_objs_in_thread(int val); //added 

  void CLAP_API clap_set_watch_shared_objs(bool val);
  void CLAP_API clap_disable_watch_shared_objs();
  void CLAP_API clap_enable_watch_shared_objs();
  void CLAP_API clap_enable_target_trace();
  void CLAP_API clap_disable_target_trace();
  
  int  CLAP_API clap_thread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg);
  void CLAP_API clap_thread_exit(void *value_ptr);
  void CLAP_API clap_thread_yield();
  int  CLAP_API clap_thread_cancel(pthread_t thread);
  int  CLAP_API clap_thread_join(pthread_t thread, void **value_ptr);
  void CLAP_API clap_thread_exit(void* ret);
  long* clap___sync_lock_test_and_set (long **ptr, long* value, ...);
  #ifdef HAVE_PTHREAD_TRYJOIN_NP
  int  CLAP_API clap_thread_tryjoin_np(pthread_t thread, void **value_ptr);
#endif // HAVE_PTHREAD_TRYJOIN_NP
#ifdef HAVE_PTHREAD_TIMEDJOIN_NP
  int  CLAP_API clap_thread_timedjoin_np(pthread_t thread, void **value_ptr, struct timespec* abstime);
#endif // HAVE_PTHREAD_TIMEDJOIN_NP
  int  CLAP_API clap_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
  int  CLAP_API clap_mutex_destroy(pthread_mutex_t *mutex);
  int  CLAP_API clap_mutex_lock(pthread_mutex_t *mutex);
  int  CLAP_API clap_mutex_trylock(pthread_mutex_t *mutex);
  int  CLAP_API clap_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);  
  int  CLAP_API clap_mutex_unlock(pthread_mutex_t *mutex);  
#ifdef __USE_XOPEN2K
  int  CLAP_API clap_spin_init(pthread_spinlock_t * spin, int pshared);
  int  CLAP_API clap_spin_destroy(pthread_spinlock_t * spin);
  int  CLAP_API clap_spin_lock(pthread_spinlock_t * spin);
  int  CLAP_API clap_spin_unlock(pthread_spinlock_t * spin);
  int  CLAP_API clap_spin_trylock(pthread_spinlock_t *spin);
#endif//__USE_XOPEN2K

  int  CLAP_API clap_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
  int  CLAP_API clap_cond_destroy(pthread_cond_t *cond);
  int  CLAP_API clap_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
  int  CLAP_API clap_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
  int  CLAP_API clap_cond_broadcast(pthread_cond_t *cond);
  int  CLAP_API clap_cond_signal(pthread_cond_t *cond); 

  int  CLAP_API clap_barrier_init(pthread_barrier_t* barrier, const pthread_barrierattr_t* attr, unsigned int count);
  int  CLAP_API clap_key_create(pthread_key_t *__key, void (*__destr_function) (void*));

  int  CLAP_API clap_barrier_destroy(pthread_barrier_t* barrier);
  int  CLAP_API clap_barrier_wait(pthread_barrier_t* barrier);

#ifdef __USE_XOPEN2K
  int  CLAP_API clap_barrier_init(pthread_barrier_t* barrier, const pthread_barrierattr_t* attr, unsigned int count);
  int CLAP_API clap_key_create(pthread_key_t *__key, void (*__destr_function) (void*));

  int  CLAP_API clap_barrier_destroy(pthread_barrier_t* barrier);
  int  CLAP_API clap_barrier_wait(pthread_barrier_t* barrier);
#endif//__USE_XOPEN2K

#if defined __USE_UNIX98 || defined __USE_XOPEN2K
  int  CLAP_API clap_rwlock_init(pthread_rwlock_t * rwlock, const pthread_rwlockattr_t * attr);
  int  CLAP_API clap_rwlock_destroy(pthread_rwlock_t *rwlock);
  int  CLAP_API clap_rwlock_rdlock(pthread_rwlock_t *rwlock);
  int  CLAP_API clap_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
  int  CLAP_API clap_rwlock_timedrdlock(pthread_rwlock_t *rwlock, const struct timespec *abstime);  
  int  CLAP_API clap_rwlock_wrlock(pthread_rwlock_t *rwlock);
  int  CLAP_API clap_rwlock_trywrlock(pthread_rwlock_t *rwlock);
  int  CLAP_API clap_rwlock_timedwrlock(pthread_rwlock_t *rwlock, const struct timespec *abstime);  
  int  CLAP_API clap_rwlock_unlock(pthread_rwlock_t *rwlock);  
#endif//defined __USE_UNIX98 || defined __USE_XOPEN2K

  int    CLAP_API clap_sem_init(sem_t *sem, int pshared, unsigned int value);
  int    CLAP_API clap_sem_destroy(sem_t *sem);
  sem_t* CLAP_API clap_sem_open(char *name, int oflag, ...);
  int    CLAP_API clap_sem_close(sem_t *sem);
  int    CLAP_API clap_sem_unlink(char *name);
  int    CLAP_API clap_sem_wait(sem_t *sem);
  int    CLAP_API clap_sem_timedwait(sem_t * sem, struct timespec* abstime);
  int    CLAP_API clap_sem_trywait(sem_t *sem);
  int    CLAP_API clap_sem_post(sem_t *sem);
  int    CLAP_API clap_sem_getvalue(sem_t * sem, int * sval);

  int  CLAP_API clap_semctl(int, int, int, ...);
  int  CLAP_API clap_semget(key_t, int, int);
  int  CLAP_API clap_semop(int, struct sembuf*, size_t);
  int  CLAP_API clap_semtimedop(int, struct sembuf*, size_t, struct timespec*);

  void CLAP_API clap_load_pre(int n_param, ...);
  void CLAP_API clap_load_post(int n_param, ...);
  void CLAP_API clap_store_pre(int n_param, ...);
  void CLAP_API clap_store_post(int n_param, ...);
  void CLAP_API clap_cmpxchg_pre(int n_param, ...);
  void CLAP_API clap_cmpxchg_post(int n_param, ...);
  void CLAP_API clap_atomicrmw_pre(int n_param, ...);
  void CLAP_API clap_atomicrmw_post(int n_param, ...);

  void CLAP_API clap_call_pre(int n_param, ...);
  void CLAP_API clap_call_post(int n_param, ...);

  void CLAP_API clap___assert_fail (const char *__assertion, const char *__file,
                                    unsigned int __line, const char *__function);

#ifdef __cplusplus
}
#endif



#endif//__INSPECTOR_CLAP_H__
