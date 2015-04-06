#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/wait.h>
#include <poll.h>
#include <unistd.h>
#include <assert.h>

extern void (*monitor_thread_start)();
extern void (*monitor_thread_end)();
extern void (*monitor_thread_create)(pthread_t *, const pthread_attr_t *, void *(*)(void*), void *);
extern void (*monitor_thread_join)(pthread_t thread, void **value_ptr);
extern void (*monitor_mutex_init)(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
extern void (*monitor_mutex_destroy)(pthread_mutex_t *mutex);
extern void (*monitor_mutex_lock)(pthread_mutex_t *mutex);
extern void (*monitor_mutex_trylock)(pthread_mutex_t *mutex);
extern void (*monitor_mutex_timedlock)(pthread_mutex_t *mutex, const struct timespec *abstime);
extern void (*monitor_mutex_unlock)(pthread_mutex_t *mutex);
extern void (*monitor_cond_init)(pthread_cond_t * cond, const pthread_condattr_t * attr);
extern void (*monitor_cond_destroy)(pthread_cond_t *cond);
extern void (*monitor_cond_wait)(pthread_cond_t * cond, pthread_mutex_t * mutex);
extern void (*monitor_cond_timedwait)(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
extern void (*monitor_cond_broadcast)(pthread_cond_t *cond);
extern void (*monitor_cond_signal)(pthread_cond_t *cond);
extern void (*monitor_atomic_load)(int* addr, const int mem_odr);
extern void (*monitor_atomic_store)(int* addr, const int mem_odr);
extern void (*monitor_obj_read)(int* addr);
extern void (*monitor_obj_write)(int* addr);
extern void (*monitor_call_begin)(char* fn, char* ptr);
extern void (*monitor_call_end)(char* fn, char* ptr);
extern void (*monitor_inst_begin)(int inst, int stat);
extern void (*monitor_inst_end)(int inst, int stat, int retval);

extern void clap_monitor_init();
