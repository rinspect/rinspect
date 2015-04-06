#ifndef __INSPECTOR_PTHREAD_HH__
#define __INSPECTOR_PTHREAD_HH__

/**
 *  For the threading call, we need to handle them by ourselves
 * 
 */

//#define _XOPEN_SOURCE 500 


//#ifndef __USE_UNIX98
//#define __USE_UNIX98
//#endif

#include "naling.def"
#include <pthread.h>
#include "inspect_event.hh"

#ifdef __cplusplus
extern "C"
{
#endif

  extern const int  DummyLocation;

  enum OBJECT_TYPE      { INT_OBJECT=0, FLOAT_OBJECT=1, CHAR_OBJECT=2, BINARY_OBJECT=3, UNKNOWN_OBJECT=99 };
  enum OBJECT_CTRL_INFO { DATA_OBJECT=0, CONTROL_OBJECT=1};
  enum LOCAL_STATE_FLAG { LOCAL_STATE_UNCHANGED=0, LOCAL_STATE_CHANGED=1};  
  
  void inspect_exit(int);
  
  void inspect_main_start();
  void inspect_main_end();
  
  void inspect_thread_start(const char * func_name);
  void inspect_thread_end();
  
  void inspect_obj_reg(void * obj_addr);
  void inspect_obj_read(void * obj_addr, int inst_id);
  void inspect_obj_write(void * obj_addr, int inst_id);  

  InspectEvent * inspect_obj_call(char * fname, void * obj_ptr);
  InspectEvent * inspect_obj_resp(char *fname, void * obj_addr,char* retval, int return_value);
  
  void inspect_symmetry_point(int point_no);

  int inspect_get_thread_id();
  

  void inspect_local_info(int position, enum LOCAL_STATE_FLAG flag);
  void inspect_local_snapshot_begin();
  void inspect_local_snapshot_end();
  void inspect_local_int(int addr);
  void inspect_local_double(double addr);
  void inspect_local_binary(int sz, void * addr);
  

  int inspect_thread_create(pthread_t * thread,
			    const pthread_attr_t * attr,
			    void *(*start_routine)(void*), 
			    void * arg);

  void inspect_thread_exit(void *value_ptr);
  
  void inspect_thread_cancel(pthread_t thread);

  int inspect_thread_join(pthread_t thread, void **value_ptr);
  
  
  int inspect_mutex_init(pthread_mutex_t * mutex,
			 const pthread_mutexattr_t * attr);
  
  int inspect_mutex_destroy(pthread_mutex_t *mutex);
  
  int inspect_mutex_lock(pthread_mutex_t *mutex);
  
  int inspect_mutex_trylock(pthread_mutex_t *mutex);
  
  int inspect_mutex_unlock(pthread_mutex_t *mutex);
  

  int inspect_cond_destroy(pthread_cond_t *cond);
  
  int inspect_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
  
  int inspect_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
  
  
  int inspect_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex,
			     const struct timespec * abstime);
  
  
  int inspect_cond_broadcast(pthread_cond_t *cond);
  
  int inspect_cond_signal(pthread_cond_t *cond); 

  void inspect_assert();

//   int inspect_rwlock_init(pthread_rwlock_t * rwlock,
// 			  const pthread_rwlockattr_t * attr,
// 			  enum LOCAL_STATE_FLAG lscf,
// 			  int location_id);
//   int inspect_rwlock_destroy(pthread_rwlock_t *rwlock, enum LOCAL_STATE_FLAG lscf, int location_id);
//   int inspect_rwlock_rdlock(pthread_rwlock_t *rwlock, enum LOCAL_STATE_FLAG lscf, int location_id);
//   int inspect_rwlock_tryrdlock(pthread_rwlock_t *rwlock, enum LOCAL_STATE_FLAG lscf, int location_id);
//   int inspect_rwlock_wrlock(pthread_rwlock_t *rwlock, enum LOCAL_STATE_FLAG lscf, int location_id);
//   int inspect_rwlock_trywrlock(pthread_rwlock_t *rwlock, enum LOCAL_STATE_FLAG lscf, int location_id);
//   int inspect_rwlock_unlock(pthread_rwlock_t *rwlock, enum LOCAL_STATE_FLAG lscf, int location_id);
//   ;  
  int inspect_mutexattr_destroy(pthread_mutexattr_t *attr);
  
  int inspect_mutexattr_init(pthread_mutexattr_t *attr);

  void inspect_start_sc_thread();
  void * global_objects_state_capturing(void *arg);

  int is_stateful_search();

  extern const int SC_THREAD_ID;

#ifdef __cplusplus
}
#endif

#ifdef NLZ_PREL
/*
void inspect_obj_write_relax(void* obj_addr, int value, int uid);
void inspect_obj_read_relax(void* obj_add, int uid);
void inspect_after_any();
*/
#endif 

#ifdef NLZ_COMM
void inspect_obj_write_rinspect(void* obj_addr, int value, int uid);
void inspect_obj_read_rinspect(void* obj_add, int uid);
void inspect_commit_obj_write();
void send_write_vector(bool IsAtomic);
bool buffer_has_value();
int inspect_check_real_addr(void* addr);
#endif
#ifdef NLZ_ATOMIC
void inspect_obj_membar_rinspect(void* obj_addr, int inst_id);
#endif



#endif
