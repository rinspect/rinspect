// c::tag-#anon#ST[S32'__lock'|U32'__futex'|U64'__total_seq'|U64'__wakeup_seq'|U64'__woken_seq'|*{V}'__mutex'|U32'__nwaiters'|U32'__broadcast_seq']
// 
struct anon$5;

// c::tag-#anon#ST[v*{SYM#c::tag-timer_event_t#}'next'|v*{SYM#c::tag-timer_event_t#}'prev']
// 
struct anon$0;

// c::tag-#anon#UN[ARR0000000000000000000000000000000000000000000000000000000000000100{S8}'__size'|S32'__align']
// 
union anon$4;

// c::tag-#anon#UN[SYM#c::tag-#anon#ST[S32'__lock'|U32'__futex'|U64'__total_seq'|U64'__wakeup_seq'|U64'__woken_seq'|*{V}'__mutex'|U32'__nwaiters'|U32'__broadcast_seq']#'__data'|ARR0000000000000000000000000000000000000000000000000000000000110000{S8}'__size'|S64'__align']
// 
union anon$3;

// c::tag-#anon#UN[SYM#c::tag-__pthread_mutex_s#'__data'|ARR0000000000000000000000000000000000000000000000000000000000101000{S8}'__size'|S64'__align']
// 
union anon$2;

// c::tag-__pthread_internal_list
// file /usr/include/bits/pthreadtypes.h line 61
struct __pthread_internal_list;

// c::tag-__pthread_mutex_s
// file /usr/include/bits/pthreadtypes.h line 78
struct __pthread_mutex_s;

// c::tag-apr_file_t
// file apr-1.4.6/include/arch/unix/apr_arch_file_io.h line 93
struct apr_file_t;

// c::tag-apr_pool_t
// file apr-1.4.6/include/apr_pools.h line 60
struct apr_pool_t;

// c::tag-apr_proc_t
// file apr-1.4.6/include/apr_thread_proc.h line 133
struct apr_proc_t;

// c::tag-apr_procattr_t
// file apr-1.4.6/include/arch/unix/apr_arch_threadproc.h line 79
struct apr_procattr_t;

// c::tag-apr_socket_t
// file apr-1.4.6/include/apr_network_io.h line 191
struct apr_socket_t;

// c::tag-apr_thread_cond_t
// file apr-1.4.6/include/apr_thread_cond.h line 44
struct apr_thread_cond_t;

// c::tag-apr_thread_mutex_t
// file apr-1.4.6/include/apr_thread_mutex.h line 41
struct apr_thread_mutex_t;

// c::tag-event_conn_state_t
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 43
struct event_conn_state_t;

// c::tag-fd_queue_elem_t
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 56
struct fd_queue_elem_t;

// c::tag-fd_queue_info_t
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 42
struct fd_queue_info_t;

// c::tag-fd_queue_t
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 74
struct fd_queue_t;

// c::tag-recycled_pool
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 20
struct recycled_pool;

// c::tag-rlimit
// file /usr/include/bits/resource.h line 135
struct rlimit;

// c::tag-timer_event_t
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 66
struct timer_event_t;

// c::tag-timers_t
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 76
struct timers_t;

// c::tag-timespec
// file /usr/include/time.h line 120
struct timespec;


#ifndef TRUE
#define TRUE (_Bool)1
#endif
#ifndef FALSE
#define FALSE (_Bool)0
#endif
#ifndef NULL
#define NULL ((void*)0)
#endif
#ifndef FENCE
#define FENCE(x) ((void)0)
#endif
#ifndef IEEE_FLOAT_EQUAL
#define IEEE_FLOAT_EQUAL(x,y) (x==y)
#endif
#ifndef IEEE_FLOAT_NOTEQUAL
#define IEEE_FLOAT_NOTEQUAL(x,y) (x!=y)
#endif

// c::__errno_location
// file /usr/include/bits/errno.h line 43
int * __errno_location(void);
// c::__sync_fetch_and_add
// file gcc_builtin_headers_generic.h line 84
int __sync_fetch_and_add();
// c::__sync_fetch_and_sub
// file gcc_builtin_headers_generic.h line 85
int __sync_fetch_and_sub();
// c::__sync_lock_test_and_set
// file gcc_builtin_headers_generic.h line 99
int __sync_lock_test_and_set();
// c::__sync_sub_and_fetch
// file gcc_builtin_headers_generic.h line 91
int __sync_sub_and_fetch();
// c::__sync_synchronize
// file gcc_builtin_headers_generic.h line 98
void __sync_synchronize();
// c::__sync_val_compare_and_swap
// file gcc_builtin_headers_generic.h line 97
int __sync_val_compare_and_swap();
// c::_exit
// file /usr/include/unistd.h line 598
void _exit(int);
// c::access
// file /usr/include/unistd.h line 288
int access(const signed char *, int);
// c::ap_pop_pool
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 252
void ap_pop_pool(struct apr_pool_t **recycled_pool, struct fd_queue_info_t *queue_info);
// c::ap_push_pool
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 216
void ap_push_pool(struct fd_queue_info_t *queue_info, struct apr_pool_t *pool_to_recycle);
// c::ap_queue_destroy
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 311
static int ap_queue_destroy(void *data);
// c::ap_queue_info_create
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 45
int ap_queue_info_create(struct fd_queue_info_t **queue_info, struct apr_pool_t *pool, int max_idlers, int max_recycled_pools);
// c::ap_queue_info_get_idlers
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 207
unsigned int ap_queue_info_get_idlers(struct fd_queue_info_t *queue_info);
// c::ap_queue_info_set_idle
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 48
int ap_queue_info_set_idle(struct fd_queue_info_t *queue_info, struct apr_pool_t *pool_to_recycle);
// c::ap_queue_info_term
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 283
int ap_queue_info_term(struct fd_queue_info_t *queue_info);
// c::ap_queue_info_try_get_idler
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 130
int ap_queue_info_try_get_idler(struct fd_queue_info_t *queue_info);
// c::ap_queue_info_wait_for_idler
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 51
int ap_queue_info_wait_for_idler(struct fd_queue_info_t *queue_info, int *had_to_block);
// c::ap_queue_init
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 327
int ap_queue_init(struct fd_queue_t *queue, int queue_capacity, struct apr_pool_t *a);
// c::ap_queue_interrupt_all
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 480
int ap_queue_interrupt_all(struct fd_queue_t *queue);
// c::ap_queue_pop_something
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 424
int ap_queue_pop_something(struct fd_queue_t *queue, struct apr_socket_t **sd, struct event_conn_state_t **ecs, struct apr_pool_t **p, struct timer_event_t **te_out);
// c::ap_queue_push
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 366
int ap_queue_push(struct fd_queue_t *queue, struct apr_socket_t *sd, struct event_conn_state_t *ecs, struct apr_pool_t *p);
// c::ap_queue_push_timer
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 397
int ap_queue_push_timer(struct fd_queue_t *queue, struct timer_event_t *te);
// c::ap_queue_term
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 491
int ap_queue_term(struct fd_queue_t *queue);
// c::apr_atomic_add32
// file apr-1.4.6/include/apr_atomic.h line 74
unsigned int apr_atomic_add32(volatile unsigned int *mem, unsigned int val);
// c::apr_atomic_cas32
// file apr-1.4.6/atomic/unix/builtins.c line 56
unsigned int apr_atomic_cas32(volatile unsigned int *mem, unsigned int with, unsigned int cmp);
// c::apr_atomic_casptr
// file apr-1.4.6/include/apr_atomic.h line 124
void * apr_atomic_casptr(volatile void **mem, void *with, const void *cmp);
// c::apr_atomic_dec32
// file apr-1.4.6/include/apr_atomic.h line 95
int apr_atomic_dec32(volatile unsigned int *mem);
// c::apr_atomic_inc32
// file apr-1.4.6/include/apr_atomic.h line 88
unsigned int apr_atomic_inc32(volatile unsigned int *mem);
// c::apr_atomic_init
// file apr-1.4.6/atomic/unix/builtins.c line 21
int apr_atomic_init(struct apr_pool_t *p);
// c::apr_atomic_read32
// file apr-1.4.6/include/apr_atomic.h line 59
unsigned int apr_atomic_read32(volatile unsigned int *mem);
// c::apr_atomic_set32
// file apr-1.4.6/atomic/unix/builtins.c line 31
void apr_atomic_set32(volatile unsigned int *mem, unsigned int val);
// c::apr_atomic_sub32
// file apr-1.4.6/atomic/unix/builtins.c line 41
void apr_atomic_sub32(volatile unsigned int *mem, unsigned int val);
// c::apr_atomic_xchg32
// file apr-1.4.6/atomic/unix/builtins.c line 62
unsigned int apr_atomic_xchg32(volatile unsigned int *mem, unsigned int val);
// c::apr_atomic_xchgptr
// file apr-1.4.6/atomic/unix/builtins.c line 74
void * apr_atomic_xchgptr(volatile void **mem, void *with);
// c::apr_file_close
// file apr-1.4.6/include/apr_file_io.h line 243
int apr_file_close(struct apr_file_t *);
// c::apr_file_dup
// file apr-1.4.6/include/apr_file_io.h line 587
int apr_file_dup(struct apr_file_t **, struct apr_file_t *, struct apr_pool_t *);
// c::apr_file_dup2
// file apr-1.4.6/include/apr_file_io.h line 599
int apr_file_dup2(struct apr_file_t *, struct apr_file_t *, struct apr_pool_t *);
// c::apr_file_inherit_set
// file apr-1.4.6/include/apr_file_io.h line 900
int apr_file_inherit_set(struct apr_file_t *);
// c::apr_file_inherit_unset
// file apr-1.4.6/include/apr_file_io.h line 905
int apr_file_inherit_unset(struct apr_file_t *);
// c::apr_file_pipe_create
// file apr-1.4.6/include/apr_file_io.h line 669
int apr_file_pipe_create(struct apr_file_t **, struct apr_file_t **, struct apr_pool_t *);
// c::apr_file_pipe_create_ex
// file apr-1.4.6/include/apr_file_io.h line 694
int apr_file_pipe_create_ex(struct apr_file_t **, struct apr_file_t **, int, struct apr_pool_t *);
// c::apr_file_pool_get
// file apr-1.4.6/include/apr_file_io.h line 894
struct apr_pool_t * apr_file_pool_get(struct apr_file_t *);
// c::apr_gid_get
// file apr-1.4.6/include/apr_user.h line 133
int apr_gid_get(unsigned int *, const signed char *, struct apr_pool_t *);
// c::apr_palloc
// file fdqueue_main.c line 17
void * apr_palloc(struct apr_pool_t *p, unsigned long int size);
// c::apr_pool_cleanup_for_exec
// file apr-1.4.6/include/apr_pools.h line 690
void apr_pool_cleanup_for_exec(void);
// c::apr_pool_cleanup_kill
// file apr-1.4.6/include/apr_pools.h line 638
void apr_pool_cleanup_kill(struct apr_pool_t *, const void *, int (*)(void *));
// c::apr_pool_cleanup_null
// file apr-1.4.6/include/apr_pools.h line 682
int apr_pool_cleanup_null(void *);
// c::apr_pool_cleanup_register
// file apr-1.4.6/include/apr_pools.h line 603
void apr_pool_cleanup_register(struct apr_pool_t *, const void *, int (*)(void *), int (*)(void *));
// c::apr_pool_cleanup_run
// file apr-1.4.6/include/apr_pools.h line 670
int apr_pool_cleanup_run(struct apr_pool_t *, void *, int (*)(void *));
// c::apr_pool_destroy
// file apr-1.4.6/include/apr_pools.h line 385
void apr_pool_destroy(struct apr_pool_t *);
// c::apr_proc_create
// file apr-1.4.6/threadproc/unix/proc.c line 344
int apr_proc_create(struct apr_proc_t *new, const signed char *progname, const signed char * const *args, const signed char * const *env, struct apr_procattr_t *attr, struct apr_pool_t *pool);
// c::apr_proc_detach
// file apr-1.4.6/include/apr_thread_proc.h line 686
int apr_proc_detach(int);
// c::apr_proc_fork
// file apr-1.4.6/threadproc/unix/proc.c line 219
int apr_proc_fork(struct apr_proc_t *proc, struct apr_pool_t *pool);
// c::apr_proc_wait
// file apr-1.4.6/threadproc/unix/proc.c line 610
int apr_proc_wait(struct apr_proc_t *proc, int *exitcode, int, int);
// c::apr_proc_wait_all_procs
// file apr-1.4.6/threadproc/unix/proc.c line 600
int apr_proc_wait_all_procs(struct apr_proc_t *proc, int *exitcode, int, int, struct apr_pool_t *p);
// c::apr_procattr_addrspace_set
// file apr-1.4.6/threadproc/unix/proc.c line 307
int apr_procattr_addrspace_set(struct apr_procattr_t *attr, int addrspace);
// c::apr_procattr_child_err_set
// file apr-1.4.6/threadproc/unix/proc.c line 161
int apr_procattr_child_err_set(struct apr_procattr_t *attr, struct apr_file_t *child_err, struct apr_file_t *parent_err);
// c::apr_procattr_child_errfn_set
// file apr-1.4.6/threadproc/unix/proc.c line 293
int apr_procattr_child_errfn_set(struct apr_procattr_t *attr, void (*errfn)(struct apr_pool_t *, int, const signed char *));
// c::apr_procattr_child_errfn_set::errfn$object
// 
void errfn$object(struct apr_pool_t *, int, const signed char *);
// c::apr_procattr_child_in_set
// file apr-1.4.6/threadproc/unix/proc.c line 93
int apr_procattr_child_in_set(struct apr_procattr_t *attr, struct apr_file_t *child_in, struct apr_file_t *parent_in);
// c::apr_procattr_child_out_set
// file apr-1.4.6/threadproc/unix/proc.c line 127
int apr_procattr_child_out_set(struct apr_procattr_t *attr, struct apr_file_t *child_out, struct apr_file_t *parent_out);
// c::apr_procattr_cmdtype_set
// file apr-1.4.6/threadproc/unix/proc.c line 205
int apr_procattr_cmdtype_set(struct apr_procattr_t *attr, int);
// c::apr_procattr_create
// file apr-1.4.6/threadproc/unix/proc.c line 28
int apr_procattr_create(struct apr_procattr_t **new, struct apr_pool_t *pool);
// c::apr_procattr_detach_set
// file apr-1.4.6/threadproc/unix/proc.c line 212
int apr_procattr_detach_set(struct apr_procattr_t *attr, int detach);
// c::apr_procattr_dir_set
// file apr-1.4.6/threadproc/unix/proc.c line 194
int apr_procattr_dir_set(struct apr_procattr_t *attr, const signed char *dir);
// c::apr_procattr_error_check_set
// file apr-1.4.6/threadproc/unix/proc.c line 300
int apr_procattr_error_check_set(struct apr_procattr_t *attr, int chk);
// c::apr_procattr_group_set
// file apr-1.4.6/threadproc/unix/proc.c line 334
int apr_procattr_group_set(struct apr_procattr_t *attr, const signed char *groupname);
// c::apr_procattr_io_set
// file apr-1.4.6/threadproc/unix/proc.c line 42
int apr_procattr_io_set(struct apr_procattr_t *attr, int in, int out, int err);
// c::apr_procattr_limit_set
// file apr-1.4.6/threadproc/unix/proc.c line 669
int apr_procattr_limit_set(struct apr_procattr_t *attr, int what, struct rlimit *limit);
// c::apr_procattr_user_set
// file apr-1.4.6/threadproc/unix/proc.c line 314
int apr_procattr_user_set(struct apr_procattr_t *attr, const signed char *username, const signed char *password);
// c::apr_psprintf
// file apr-1.4.6/include/apr_strings.h line 174
signed char * apr_psprintf(struct apr_pool_t *, const signed char *, ...);
// c::apr_pstrdup
// file apr-1.4.6/include/apr_strings.h line 95
signed char * apr_pstrdup(struct apr_pool_t *, const signed char *);
// c::apr_random_after_fork
// file apr-1.4.6/include/apr_random.h line 145
void apr_random_after_fork(struct apr_proc_t *);
// c::apr_signal
// file apr-1.4.6/include/apr_signal.h line 64
void (*)(int) apr_signal(int, void (*)(int));
// c::apr_thread_cond_broadcast
// file apr-1.4.6/include/apr_thread_cond.h line 117
int apr_thread_cond_broadcast(struct apr_thread_cond_t *cond);
// c::apr_thread_cond_create
// file apr-1.4.6/include/apr_thread_cond.h line 59
int apr_thread_cond_create(struct apr_thread_cond_t **cond, struct apr_pool_t *pool);
// c::apr_thread_cond_destroy
// file apr-1.4.6/include/apr_thread_cond.h line 123
int apr_thread_cond_destroy(struct apr_thread_cond_t *cond);
// c::apr_thread_cond_pool_get
// file apr-1.4.6/locks/unix/thread_cond.c line 133
struct apr_pool_t * apr_thread_cond_pool_get(struct apr_thread_cond_t *thethread_cond);
// c::apr_thread_cond_signal
// file apr-1.4.6/include/apr_thread_cond.h line 108
int apr_thread_cond_signal(struct apr_thread_cond_t *cond);
// c::apr_thread_cond_timedwait
// file apr-1.4.6/locks/unix/thread_cond.c line 77
int apr_thread_cond_timedwait(struct apr_thread_cond_t *cond, struct apr_thread_mutex_t *mutex, long int timeout);
// c::apr_thread_cond_wait
// file apr-1.4.6/include/apr_thread_cond.h line 77
int apr_thread_cond_wait(struct apr_thread_cond_t *cond, struct apr_thread_mutex_t *mutex);
// c::apr_thread_mutex_create
// file apr-1.4.6/include/apr_thread_mutex.h line 65
int apr_thread_mutex_create(struct apr_thread_mutex_t **mutex, unsigned int flags, struct apr_pool_t *pool);
// c::apr_thread_mutex_destroy
// file apr-1.4.6/include/apr_thread_mutex.h line 94
int apr_thread_mutex_destroy(struct apr_thread_mutex_t *mutex);
// c::apr_thread_mutex_lock
// file apr-1.4.6/include/apr_thread_mutex.h line 73
int apr_thread_mutex_lock(struct apr_thread_mutex_t *mutex);
// c::apr_thread_mutex_pool_get
// file apr-1.4.6/locks/unix/thread_mutex.c line 136
struct apr_pool_t * apr_thread_mutex_pool_get(struct apr_thread_mutex_t *thethread_mutex);
// c::apr_thread_mutex_trylock
// file apr-1.4.6/locks/unix/thread_mutex.c line 102
int apr_thread_mutex_trylock(struct apr_thread_mutex_t *mutex);
// c::apr_thread_mutex_unlock
// file apr-1.4.6/include/apr_thread_mutex.h line 88
int apr_thread_mutex_unlock(struct apr_thread_mutex_t *mutex);
// c::apr_time_now
// file apr-1.4.6/include/apr_time.h line 88
long int apr_time_now(void);
// c::apr_uid_get
// file apr-1.4.6/include/apr_user.h line 88
int apr_uid_get(unsigned int *, unsigned int *, const signed char *, struct apr_pool_t *);
// c::apr_unix_file_cleanup
// file apr-1.4.6/include/arch/unix/apr_arch_file_io.h line 162
int apr_unix_file_cleanup(void *);
// c::chdir
// file /usr/include/unistd.h line 493
int chdir(const signed char *);
// c::close
// file /usr/include/unistd.h line 350
int close(int);
// c::dup2
// file /usr/include/unistd.h line 529
int dup2(int, int);
// c::execv
// file /usr/include/unistd.h line 558
int execv(const signed char *, signed char * const *);
// c::execve
// file /usr/include/unistd.h line 546
int execve(const signed char *, signed char * const *, signed char * const *);
// c::execvp
// file /usr/include/unistd.h line 573
int execvp(const signed char *, signed char * const *);
// c::fork
// file /usr/include/unistd.h line 773
int fork(void);
// c::geteuid
// file /usr/include/unistd.h line 695
unsigned int geteuid(void);
// c::getpid
// file /usr/include/unistd.h line 623
int getpid(void);
// c::limit_proc
// file apr-1.4.6/threadproc/unix/proc.c line 241
static int limit_proc(struct apr_procattr_t *attr);
// c::malloc
// file /usr/include/stdlib.h line 471
void * malloc(unsigned long int);
// c::memcpy
// file /usr/include/string.h line 43
void * memcpy(void *, const void *, unsigned long int);
// c::memset
// file /usr/include/string.h line 64
void * memset(void *, int, unsigned long int);
// c::pthread_cond_broadcast
// file /usr/include/pthread.h line 957
int pthread_cond_broadcast(union anon$3 *);
// c::pthread_cond_destroy
// file /usr/include/pthread.h line 949
int pthread_cond_destroy(union anon$3 *);
// c::pthread_cond_init
// file /usr/include/pthread.h line 944
int pthread_cond_init(union anon$3 *, union anon$4 *);
// c::pthread_cond_signal
// file /usr/include/pthread.h line 953
int pthread_cond_signal(union anon$3 *);
// c::pthread_cond_timedwait
// file /usr/include/pthread.h line 976
int pthread_cond_timedwait(union anon$3 *, union anon$2 *, struct timespec *);
// c::pthread_cond_wait
// file /usr/include/pthread.h line 965
int pthread_cond_wait(union anon$3 *, union anon$2 *);
// c::pthread_mutex_destroy
// file /usr/include/pthread.h line 728
int pthread_mutex_destroy(union anon$2 *);
// c::pthread_mutex_init
// file /usr/include/pthread.h line 723
int pthread_mutex_init(union anon$2 *, union anon$4 *);
// c::pthread_mutex_lock
// file /usr/include/pthread.h line 736
int pthread_mutex_lock(union anon$2 *);
// c::pthread_mutex_trylock
// file /usr/include/pthread.h line 732
int pthread_mutex_trylock(union anon$2 *);
// c::pthread_mutex_unlock
// file /usr/include/pthread.h line 747
int pthread_mutex_unlock(union anon$2 *);
// c::pthread_mutexattr_destroy
// file /usr/include/pthread.h line 786
int pthread_mutexattr_destroy(union anon$4 *);
// c::pthread_mutexattr_init
// file /usr/include/pthread.h line 782
int pthread_mutexattr_init(union anon$4 *);
// c::pthread_mutexattr_settype
// file /usr/include/pthread.h line 809
int pthread_mutexattr_settype(union anon$4 *, int);
// c::queue_info_cleanup
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 42
static int queue_info_cleanup(void *data_);
// c::setgid
// file /usr/include/unistd.h line 734
int setgid(unsigned int);
// c::setrlimit
// file /usr/include/sys/resource.h line 70
int setrlimit(int, struct rlimit *);
// c::setuid
// file /usr/include/unistd.h line 717
int setuid(unsigned int);
// c::strlen
// file /usr/include/string.h line 397
unsigned long int strlen(const signed char *);
// c::thread_cond_cleanup
// file apr-1.4.6/locks/unix/thread_cond.c line 24
static int thread_cond_cleanup(void *data);
// c::thread_mutex_cleanup
// file apr-1.4.6/locks/unix/thread_mutex.c line 23
static int thread_mutex_cleanup(void *data);
// c::waitpid
// file /usr/include/sys/wait.h line 139
int waitpid(int, int *, int);
// c::worker_thread
// file fdqueue_main.c line 27
void worker_thread(void);

struct anon$5
{
  // __lock
  int __lock;
  // __futex
  unsigned int __futex;
  // __total_seq
  unsigned long int __total_seq;
  // __wakeup_seq
  unsigned long int __wakeup_seq;
  // __woken_seq
  unsigned long int __woken_seq;
  // __mutex
  void *__mutex;
  // __nwaiters
  unsigned int __nwaiters;
  // __broadcast_seq
  unsigned int __broadcast_seq;
};

struct timer_event_t
{
  // link
  struct anon$0 link;
  // when
  long int when;
  // cbfunc
  void (*cbfunc)(void *);
  // baton
  void *baton;
};

struct anon$0
{
  // next
  struct timer_event_t * volatile next;
  // prev
  struct timer_event_t * volatile prev;
};

union anon$4
{
  // __size
  signed char __size[4];
  // __align
  int __align;
};

union anon$3
{
  // __data
  struct anon$5 __data;
  // __size
  signed char __size[48];
  // __align
  long int __align;
};

struct __pthread_internal_list
{
  // __prev
  struct __pthread_internal_list *__prev;
  // __next
  struct __pthread_internal_list *__next;
};

struct __pthread_mutex_s
{
  // __lock
  int __lock;
  // __count
  unsigned int __count;
  // __owner
  int __owner;
  // __nusers
  unsigned int __nusers;
  // __kind
  int __kind;
  // __spins
  int __spins;
  // __list
  struct __pthread_internal_list __list;
};

union anon$2
{
  // __data
  struct __pthread_mutex_s __data;
  // __size
  signed char __size[40];
  // __align
  long int __align;
};

struct apr_thread_mutex_t
{
  // pool
  struct apr_pool_t *pool;
  // mutex
  union anon$2 mutex;
};

struct apr_file_t
{
  // pool
  struct apr_pool_t *pool;
  // filedes
  int filedes;
  // fname
  signed char *fname;
  // flags
  int flags;
  // eof_hit
  int eof_hit;
  // is_pipe
  int is_pipe;
  // timeout
  long int timeout;
  // buffered
  int buffered;
  // blocking
  int;
  // ungetchar
  int ungetchar;
  // buffer
  signed char *buffer;
  // bufpos
  unsigned long int bufpos;
  // bufsize
  unsigned long int bufsize;
  // dataRead
  unsigned long int dataRead;
  // direction
  int direction;
  // filePtr
  long int filePtr;
  // thlock
  struct apr_thread_mutex_t *thlock;
};

struct apr_proc_t
{
  // pid
  int pid;
  // in
  struct apr_file_t *in;
  // out
  struct apr_file_t *out;
  // err
  struct apr_file_t *err;
};

struct rlimit
{
  // rlim_cur
  unsigned long int rlim_cur;
  // rlim_max
  unsigned long int rlim_max;
};

struct apr_procattr_t
{
  // pool
  struct apr_pool_t *pool;
  // parent_in
  struct apr_file_t *parent_in;
  // child_in
  struct apr_file_t *child_in;
  // parent_out
  struct apr_file_t *parent_out;
  // child_out
  struct apr_file_t *child_out;
  // parent_err
  struct apr_file_t *parent_err;
  // child_err
  struct apr_file_t *child_err;
  // currdir
  signed char *currdir;
  // cmdtype
  int cmdtype;
  // detached
  int detached;
  // limit_cpu
  struct rlimit *limit_cpu;
  // limit_mem
  struct rlimit *limit_mem;
  // limit_nproc
  struct rlimit *limit_nproc;
  // limit_nofile
  struct rlimit *limit_nofile;
  // errfn
  void (*errfn)(struct apr_pool_t *, int, const signed char *);
  // errchk
  int errchk;
  // uid
  unsigned int uid;
  // gid
  unsigned int gid;
};

struct apr_thread_cond_t
{
  // pool
  struct apr_pool_t *pool;
  // cond
  union anon$3 cond;
};

struct fd_queue_elem_t
{
  // sd
  struct apr_socket_t *sd;
  // p
  struct apr_pool_t *p;
  // ecs
  struct event_conn_state_t *ecs;
};

struct recycled_pool
{
  // pool
  struct apr_pool_t *pool;
  // next
  struct recycled_pool *next;
};

struct fd_queue_info_t
{
  // idlers
  int idlers;
  // idlers_mutex
  struct apr_thread_mutex_t *idlers_mutex;
  // wait_for_idler
  struct apr_thread_cond_t *wait_for_idler;
  // terminated
  int terminated;
  // max_idlers
  int max_idlers;
  // max_recycled_pools
  int max_recycled_pools;
  // recycled_pools_count
  unsigned int recycled_pools_count;
  // recycled_pools
  struct recycled_pool *recycled_pools;
};

struct timers_t
{
  // next
  struct timer_event_t * volatile next;
  // prev
  struct timer_event_t * volatile prev;
};

struct fd_queue_t
{
  // timers
  struct timers_t timers;
  // data
  struct fd_queue_elem_t *data;
  // nelts
  unsigned int nelts;
  // bounds
  unsigned int bounds;
  // in
  unsigned int in;
  // out
  unsigned int out;
  // one_big_mutex
  struct apr_thread_mutex_t *one_big_mutex;
  // not_empty
  struct apr_thread_cond_t *not_empty;
  // terminated
  int terminated;
};

struct timespec
{
  // tv_sec
  long int tv_sec;
  // tv_nsec
  long int tv_nsec;
};


// c::M_pool
// file fdqueue_main.c line 24
struct apr_pool_t *M_pool;
// c::M_pool
// file fdqueue_main.c line 24
struct apr_pool_t *M_pool = ((struct apr_pool_t *)NULL);
// c::M_queue_info
// file fdqueue_main.c line 25
struct fd_queue_info_t *M_queue_info;
// c::M_queue_info
// file fdqueue_main.c line 25
struct fd_queue_info_t *M_queue_info = ((struct fd_queue_info_t *)NULL);
// c::no_file
// file apr-1.4.6/threadproc/unix/proc.c line 26
static struct apr_file_t no_file;
// c::no_file
// file apr-1.4.6/threadproc/unix/proc.c line 26
static struct apr_file_t no_file = { .pool=(struct apr_pool_t *)NULL, .filedes=-1, .fname=((signed char *)NULL),
    .flags=0, .eof_hit=0,
    .is_pipe=0, .timeout=0, .buffered=0, .blocking=/*enum*/0,
    .ungetchar=0, .buffer=((signed char *)NULL), .bufpos=0,
    .bufsize=0, .dataRead=0, .direction=0, .filePtr=0,
    .thlock=((struct apr_thread_mutex_t *)NULL) };
// c::pool_handed_back
// file fdqueue_main.c line 22
_Bool pool_handed_back;
// c::pool_handed_back
// file fdqueue_main.c line 22
_Bool pool_handed_back = FALSE;

// c::ap_pop_pool
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 252
void ap_pop_pool(struct apr_pool_t **recycled_pool, struct fd_queue_info_t *queue_info)
{
  *recycled_pool = (struct apr_pool_t *)NULL;
  struct recycled_pool *first_pool;
  void *return_value_apr_atomic_casptr$1;
  do
  {
    first_pool = queue_info->recycled_pools;
    if(first_pool == ((struct recycled_pool *)NULL))
      goto __CPROVER_DUMP_L4;

    return_value_apr_atomic_casptr$1=apr_atomic_casptr((volatile void **)(void *)&queue_info->recycled_pools, (void *)first_pool->next, (const void *)first_pool);
    if(!((struct recycled_pool *)return_value_apr_atomic_casptr$1 == first_pool))
      goto __CPROVER_DUMP_L3;

    *recycled_pool = first_pool->pool;
    if(queue_info->max_recycled_pools >= 0)
      apr_atomic_dec32(&queue_info->recycled_pools_count);

    goto __CPROVER_DUMP_L4;

  __CPROVER_DUMP_L3:
    ;
  }
  while(TRUE);

__CPROVER_DUMP_L4:
  ;
}

// c::ap_push_pool
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 216
void ap_push_pool(struct fd_queue_info_t *queue_info, struct apr_pool_t *pool_to_recycle)
{
  struct recycled_pool *new_recycle;
  if(pool_to_recycle == ((struct apr_pool_t *)NULL))
    return;

  unsigned int return_value_apr_atomic_read32$1;
  unsigned int cnt;
  if(queue_info->max_recycled_pools >= 0)
  {
    return_value_apr_atomic_read32$1=apr_atomic_read32(&queue_info->recycled_pools_count);
    cnt = return_value_apr_atomic_read32$1;
    if(cnt >= (unsigned int)queue_info->max_recycled_pools)
    {
      apr_pool_destroy(pool_to_recycle);
      return;
    }

    apr_atomic_inc32(&queue_info->recycled_pools_count);
  }

  void *return_value_apr_palloc$2;
  return_value_apr_palloc$2=apr_palloc(pool_to_recycle, 16 /*[[struct recycled_pool]]*/);
  new_recycle = (struct recycled_pool *)return_value_apr_palloc$2;
  new_recycle->pool = pool_to_recycle;
  struct recycled_pool *next;
  void *return_value_apr_atomic_casptr$3;
  do
  {
    next = queue_info->recycled_pools;
    new_recycle->next = next;
    return_value_apr_atomic_casptr$3=apr_atomic_casptr((volatile void **)(void *)&queue_info->recycled_pools, (void *)new_recycle, (const void *)next);
    if((struct recycled_pool *)return_value_apr_atomic_casptr$3 == next)
      goto __CPROVER_DUMP_L5;

  }
  while(TRUE);

__CPROVER_DUMP_L5:
  ;
}

// c::ap_queue_destroy
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 311
static int ap_queue_destroy(void *data)
{
  struct fd_queue_t *queue = (struct fd_queue_t *)data;
  apr_thread_cond_destroy(queue->not_empty);
  apr_thread_mutex_destroy(queue->one_big_mutex);
  return 0;
}

// c::ap_queue_info_create
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 45
int ap_queue_info_create(struct fd_queue_info_t **queue_info, struct apr_pool_t *pool, int max_idlers, int max_recycled_pools)
{
  int rv;
  struct fd_queue_info_t *qi;
  void *return_value_apr_palloc$1;
  return_value_apr_palloc$1=apr_palloc(pool, 48 /*[[struct fd_queue_info_t]]*/);
  void *return_value_memset$2;
  return_value_memset$2=memset(return_value_apr_palloc$1, 0, 48 /*[[struct fd_queue_info_t]]*/);
  qi = (struct fd_queue_info_t *)return_value_memset$2;
  rv=apr_thread_mutex_create(&qi->idlers_mutex, (unsigned int)0, pool);
  if(!(rv == 0))
    return rv;

  rv=apr_thread_cond_create(&qi->wait_for_idler, pool);
  if(!(rv == 0))
    return rv;

  qi->recycled_pools = (struct recycled_pool *)NULL;
  qi->max_recycled_pools = max_recycled_pools;
  qi->max_idlers = max_idlers;
  apr_pool_cleanup_register(pool, (const void *)qi, queue_info_cleanup, apr_pool_cleanup_null);
  *queue_info = qi;
  return 0;
}

// c::ap_queue_info_get_idlers
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 207
unsigned int ap_queue_info_get_idlers(struct fd_queue_info_t *queue_info)
{
  int val;
  unsigned int return_value_apr_atomic_read32$1;
  return_value_apr_atomic_read32$1=apr_atomic_read32((unsigned int *)&queue_info->idlers);
  val = (int)return_value_apr_atomic_read32$1;
  if(val < 0)
    return (unsigned int)0;

  return (unsigned int)val;
}

// c::ap_queue_info_set_idle
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 48
int ap_queue_info_set_idle(struct fd_queue_info_t *queue_info, struct apr_pool_t *pool_to_recycle)
{
  int rv;
  int prev_idlers;
  ap_push_pool(queue_info, pool_to_recycle);
  unsigned int return_value_apr_atomic_inc32$1;
  return_value_apr_atomic_inc32$1=apr_atomic_inc32((unsigned int *)&queue_info->idlers);
  prev_idlers = (int)return_value_apr_atomic_inc32$1;
  if(prev_idlers < 0)
  {
    rv=apr_thread_mutex_lock(queue_info->idlers_mutex);
    if(!(rv == 0))
    {
      (void)0;
      return rv;
    }

    rv=apr_thread_cond_signal(queue_info->wait_for_idler);
    if(!(rv == 0))
    {
      apr_thread_mutex_unlock(queue_info->idlers_mutex);
      return rv;
    }

    rv=apr_thread_mutex_unlock(queue_info->idlers_mutex);
    if(!(rv == 0))
      return rv;

  }

  return 0;
}

// c::ap_queue_info_term
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 283
int ap_queue_info_term(struct fd_queue_info_t *queue_info)
{
  int rv;
  rv=apr_thread_mutex_lock(queue_info->idlers_mutex);
  if(!(rv == 0))
    return rv;

  queue_info->terminated = 1;
  apr_thread_cond_broadcast(queue_info->wait_for_idler);
  int return_value_apr_thread_mutex_unlock$1;
  return_value_apr_thread_mutex_unlock$1=apr_thread_mutex_unlock(queue_info->idlers_mutex);
  return return_value_apr_thread_mutex_unlock$1;
}

// c::ap_queue_info_try_get_idler
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 130
int ap_queue_info_try_get_idler(struct fd_queue_info_t *queue_info)
{
  int prev_idlers;
  prev_idlers=apr_atomic_dec32((unsigned int *)&queue_info->idlers);
  if(prev_idlers <= 0)
  {
    apr_atomic_inc32((unsigned int *)&queue_info->idlers);
    return 11;
  }

  return 0;
}

// c::ap_queue_info_wait_for_idler
// file httpd-2.4.2/server/mpm/event/fdqueue.h line 51
int ap_queue_info_wait_for_idler(struct fd_queue_info_t *queue_info, int *had_to_block)
{
  int rv;
  int prev_idlers;
  unsigned int return_value_apr_atomic_add32$1;
  return_value_apr_atomic_add32$1=apr_atomic_add32((unsigned int *)&queue_info->idlers, (unsigned int)-1);
  prev_idlers = (int)return_value_apr_atomic_add32$1;
  int rv2;
  if(prev_idlers <= 0)
  {
    rv=apr_thread_mutex_lock(queue_info->idlers_mutex);
    if(!(rv == 0))
    {
      (void)0;
      apr_atomic_inc32((unsigned int *)&queue_info->idlers);
      return rv;
    }

    if(queue_info->idlers < 0)
    {
      *had_to_block = 1;
      rv=apr_thread_cond_wait(queue_info->wait_for_idler, queue_info->idlers_mutex);
      if(!(rv == 0))
      {
        (void)0;
        rv2=apr_thread_mutex_unlock(queue_info->idlers_mutex);
        if(!(rv2 == 0))
          return rv2;

        return rv;
      }

    }

    rv=apr_thread_mutex_unlock(queue_info->idlers_mutex);
    if(!(rv == 0))
      return rv;

  }

  if(!(queue_info->terminated == 0))
    return 20000 + 50000 + 14;

  else
    return 0;
}

// c::ap_queue_init
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 327
int ap_queue_init(struct fd_queue_t *queue, int queue_capacity, struct apr_pool_t *a)
{
  int i;
  int rv;
  int return_value_apr_thread_mutex_create$1;
  return_value_apr_thread_mutex_create$1=apr_thread_mutex_create(&queue->one_big_mutex, (unsigned int)0, a);
  rv = return_value_apr_thread_mutex_create$1;
  if(!(rv == 0))
    return rv;

  int return_value_apr_thread_cond_create$2;
  return_value_apr_thread_cond_create$2=apr_thread_cond_create(&queue->not_empty, a);
  rv = return_value_apr_thread_cond_create$2;
  if(!(rv == 0))
    return rv;

  do
  {
    (&queue->timers)->next = (struct timer_event_t *)((signed char *)&(&queue->timers)->next - (long int)((signed char *)&((struct timer_event_t *)NULL)->link - ((signed char *)NULL)));
    (&queue->timers)->prev = (struct timer_event_t *)((signed char *)&(&queue->timers)->next - (long int)((signed char *)&((struct timer_event_t *)NULL)->link - ((signed char *)NULL)));
  }
  while(FALSE);
  void *return_value_apr_palloc$3;
  return_value_apr_palloc$3=apr_palloc(a, (unsigned long int)queue_capacity * 24 /*[[struct fd_queue_elem_t]]*/);
  queue->data = (struct fd_queue_elem_t *)return_value_apr_palloc$3;
  queue->bounds = (unsigned int)queue_capacity;
  queue->nelts = (unsigned int)0;
  queue->in = (unsigned int)0;
  queue->out = (unsigned int)0;
  i = 0;
  while(!(i >= queue_capacity))
  {
    (queue->data + (long int)i)->sd = (struct apr_socket_t *)NULL;
    i = i + 1;
  }
  apr_pool_cleanup_register(a, (const void *)queue, ap_queue_destroy, apr_pool_cleanup_null);
  return 0;
}

// c::ap_queue_interrupt_all
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 480
int ap_queue_interrupt_all(struct fd_queue_t *queue)
{
  int rv;
  int return_value_apr_thread_mutex_lock$1;
  return_value_apr_thread_mutex_lock$1=apr_thread_mutex_lock(queue->one_big_mutex);
  rv = return_value_apr_thread_mutex_lock$1;
  if(!(rv == 0))
    return rv;

  apr_thread_cond_broadcast(queue->not_empty);
  int return_value_apr_thread_mutex_unlock$2;
  return_value_apr_thread_mutex_unlock$2=apr_thread_mutex_unlock(queue->one_big_mutex);
  return return_value_apr_thread_mutex_unlock$2;
}

// c::ap_queue_pop_something
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 424
int ap_queue_pop_something(struct fd_queue_t *queue, struct apr_socket_t **sd, struct event_conn_state_t **ecs, struct apr_pool_t **p, struct timer_event_t **te_out)
{
  struct fd_queue_elem_t *elem;
  int rv;
  int return_value_apr_thread_mutex_lock$1;
  return_value_apr_thread_mutex_lock$1=apr_thread_mutex_lock(queue->one_big_mutex);
  rv = return_value_apr_thread_mutex_lock$1;
  if(!(rv == 0))
    return rv;

  _Bool tmp_condition$4 = queue->nelts == (unsigned int)0;
  _Bool tmp_condition$5;
  if(tmp_condition$4)
    tmp_condition$5 = (&queue->timers)->next == (struct timer_event_t *)((signed char *)&(&queue->timers)->next - (long int)((signed char *)&((struct timer_event_t *)NULL)->link - ((signed char *)NULL)));

  _Bool tmp_condition$2;
  _Bool tmp_condition$3;
  if(tmp_condition$4 && tmp_condition$5)
  {
    if(queue->terminated == 0)
      apr_thread_cond_wait(queue->not_empty, queue->one_big_mutex);

    tmp_condition$2 = queue->nelts == (unsigned int)0;
    if(tmp_condition$2)
      tmp_condition$3 = (&queue->timers)->next == (struct timer_event_t *)((signed char *)&(&queue->timers)->next - (long int)((signed char *)&((struct timer_event_t *)NULL)->link - ((signed char *)NULL)));

    if(tmp_condition$2 && tmp_condition$3)
    {
      rv=apr_thread_mutex_unlock(queue->one_big_mutex);
      if(!(rv == 0))
        return rv;

      if(!(queue->terminated == 0))
        return 20000 + 50000 + 14;

      else
        return 4;
    }

  }

  *te_out = (struct timer_event_t *)NULL;
  if(!(queue->timers.next == (struct timer_event_t *)((signed char *)&(&queue->timers)->next + -((signed char *)0 - ((signed char *)NULL)))))
  {
    *te_out = (&queue->timers)->next;
    do
    {
      (*te_out)->link.prev->link.next = (*te_out)->link.next;
      (*te_out)->link.next->link.prev = (*te_out)->link.prev;
    }
    while(FALSE);
  }

  else
  {
    elem = &queue->data[(long int)queue->out];
    queue->out = queue->out + 1;
    if(queue->out >= queue->bounds)
    {
      queue->out = queue->out - queue->bounds;
      queue->out;
    }

    queue->nelts = queue->nelts - 1;
    *sd = elem->sd;
    *ecs = elem->ecs;
    *p = elem->p;
  }
  rv=apr_thread_mutex_unlock(queue->one_big_mutex);
  return rv;
}

// c::ap_queue_push
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 366
int ap_queue_push(struct fd_queue_t *queue, struct apr_socket_t *sd, struct event_conn_state_t *ecs, struct apr_pool_t *p)
{
  struct fd_queue_elem_t *elem;
  int rv;
  int return_value_apr_thread_mutex_lock$1;
  return_value_apr_thread_mutex_lock$1=apr_thread_mutex_lock(queue->one_big_mutex);
  rv = return_value_apr_thread_mutex_lock$1;
  if(!(rv == 0))
    return rv;

  (void)0;
  (void)0;
  elem = &queue->data[(long int)queue->in];
  queue->in = queue->in + 1;
  if(queue->in >= queue->bounds)
  {
    queue->in = queue->in - queue->bounds;
    queue->in;
  }

  elem->sd = sd;
  elem->ecs = ecs;
  elem->p = p;
  queue->nelts = queue->nelts + 1;
  apr_thread_cond_signal(queue->not_empty);
  int return_value_apr_thread_mutex_unlock$2;
  return_value_apr_thread_mutex_unlock$2=apr_thread_mutex_unlock(queue->one_big_mutex);
  rv = return_value_apr_thread_mutex_unlock$2;
  if(!(rv == 0))
    return rv;

  return 0;
}

// c::ap_queue_push_timer
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 397
int ap_queue_push_timer(struct fd_queue_t *queue, struct timer_event_t *te)
{
  int rv;
  int return_value_apr_thread_mutex_lock$1;
  return_value_apr_thread_mutex_lock$1=apr_thread_mutex_lock(queue->one_big_mutex);
  rv = return_value_apr_thread_mutex_lock$1;
  if(!(rv == 0))
    return rv;

  (void)0;
  do
  {
    te->link.next = (struct timer_event_t *)((signed char *)&(&queue->timers)->next - (long int)((signed char *)&((struct timer_event_t *)NULL)->link - ((signed char *)NULL)));
    te->link.prev = ((struct timer_event_t *)((signed char *)&(&queue->timers)->next - (long int)((signed char *)&((struct timer_event_t *)NULL)->link - ((signed char *)NULL))))->link.prev;
    ((struct timer_event_t *)((signed char *)&(&queue->timers)->next - (long int)((signed char *)&((struct timer_event_t *)NULL)->link - ((signed char *)NULL))))->link.prev->link.next = te;
    ((struct timer_event_t *)((signed char *)&(&queue->timers)->next - (long int)((signed char *)&((struct timer_event_t *)NULL)->link - ((signed char *)NULL))))->link.prev = te;
  }
  while(FALSE);
  apr_thread_cond_signal(queue->not_empty);
  int return_value_apr_thread_mutex_unlock$2;
  return_value_apr_thread_mutex_unlock$2=apr_thread_mutex_unlock(queue->one_big_mutex);
  rv = return_value_apr_thread_mutex_unlock$2;
  if(!(rv == 0))
    return rv;

  return 0;
}

// c::ap_queue_term
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 491
int ap_queue_term(struct fd_queue_t *queue)
{
  int rv;
  int return_value_apr_thread_mutex_lock$1;
  return_value_apr_thread_mutex_lock$1=apr_thread_mutex_lock(queue->one_big_mutex);
  rv = return_value_apr_thread_mutex_lock$1;
  if(!(rv == 0))
    return rv;

  queue->terminated = 1;
  int return_value_apr_thread_mutex_unlock$2;
  return_value_apr_thread_mutex_unlock$2=apr_thread_mutex_unlock(queue->one_big_mutex);
  rv = return_value_apr_thread_mutex_unlock$2;
  if(!(rv == 0))
    return rv;

  int return_value_ap_queue_interrupt_all$3;
  return_value_ap_queue_interrupt_all$3=ap_queue_interrupt_all(queue);
  return return_value_ap_queue_interrupt_all$3;
}

// c::apr_atomic_add32
// file apr-1.4.6/include/apr_atomic.h line 74
unsigned int apr_atomic_add32(volatile unsigned int *mem, unsigned int val)
{
  volatile unsigned int return_value___sync_fetch_and_add$1;
  __CPROVER_atomic_begin();
  return_value___sync_fetch_and_add$1 = *mem;
  *mem = *mem + val;
  __CPROVER_atomic_end();
  return return_value___sync_fetch_and_add$1;
}

// c::apr_atomic_cas32
// file apr-1.4.6/atomic/unix/builtins.c line 56
unsigned int apr_atomic_cas32(volatile unsigned int *mem, unsigned int with, unsigned int cmp)
{
  volatile unsigned int return_value___sync_val_compare_and_swap$1;
  __CPROVER_atomic_begin();
  return_value___sync_val_compare_and_swap$1 = *mem;
  *mem = *mem == cmp ? with : *mem;
  __CPROVER_atomic_end();
  return return_value___sync_val_compare_and_swap$1;
}

// c::apr_atomic_casptr
// file apr-1.4.6/include/apr_atomic.h line 124
void * apr_atomic_casptr(volatile void **mem, void *with, const void *cmp)
{
  volatile void *return_value___sync_val_compare_and_swap$1;
  __CPROVER_atomic_begin();
  return_value___sync_val_compare_and_swap$1 = *mem;
  *mem = *mem == cmp ? with : *mem;
  __CPROVER_atomic_end();
  return (void *)return_value___sync_val_compare_and_swap$1;
}

// c::apr_atomic_dec32
// file apr-1.4.6/include/apr_atomic.h line 95
int apr_atomic_dec32(volatile unsigned int *mem)
{
  volatile unsigned int return_value___sync_sub_and_fetch$1;
  __CPROVER_atomic_begin();
  *mem = *mem - (volatile unsigned int)1;
  return_value___sync_sub_and_fetch$1 = *mem;
  __CPROVER_atomic_end();
  return (int)return_value___sync_sub_and_fetch$1;
}

// c::apr_atomic_inc32
// file apr-1.4.6/include/apr_atomic.h line 88
unsigned int apr_atomic_inc32(volatile unsigned int *mem)
{
  volatile unsigned int return_value___sync_fetch_and_add$1;
  __CPROVER_atomic_begin();
  return_value___sync_fetch_and_add$1 = *mem;
  *mem = *mem + (volatile unsigned int)1;
  __CPROVER_atomic_end();
  return return_value___sync_fetch_and_add$1;
}

// c::apr_atomic_init
// file apr-1.4.6/atomic/unix/builtins.c line 21
int apr_atomic_init(struct apr_pool_t *p)
{
  return 0;
}

// c::apr_atomic_read32
// file apr-1.4.6/include/apr_atomic.h line 59
unsigned int apr_atomic_read32(volatile unsigned int *mem)
{
  return *mem;
}

// c::apr_atomic_set32
// file apr-1.4.6/atomic/unix/builtins.c line 31
void apr_atomic_set32(volatile unsigned int *mem, unsigned int val)
{
  *mem = val;
}

// c::apr_atomic_sub32
// file apr-1.4.6/atomic/unix/builtins.c line 41
void apr_atomic_sub32(volatile unsigned int *mem, unsigned int val)
{
  __CPROVER_atomic_begin();
  *mem = *mem - val;
  __CPROVER_atomic_end();
}

// c::apr_atomic_xchg32
// file apr-1.4.6/atomic/unix/builtins.c line 62
unsigned int apr_atomic_xchg32(volatile unsigned int *mem, unsigned int val)
{
  __sync_synchronize();
  volatile unsigned int return_value___sync_lock_test_and_set$1;
  return return_value___sync_lock_test_and_set$1;
}

// c::apr_atomic_xchgptr
// file apr-1.4.6/atomic/unix/builtins.c line 74
void * apr_atomic_xchgptr(volatile void **mem, void *with)
{
  __sync_synchronize();
  volatile void *return_value___sync_lock_test_and_set$1;
  return (void *)return_value___sync_lock_test_and_set$1;
}

// c::apr_palloc
// file fdqueue_main.c line 17
void * apr_palloc(struct apr_pool_t *p, unsigned long int size)
{
  void *return_value_malloc$1;
  return_value_malloc$1=malloc(size);
  return return_value_malloc$1;
}

// c::apr_proc_create
// file apr-1.4.6/threadproc/unix/proc.c line 344
int apr_proc_create(struct apr_proc_t *new, const signed char *progname, const signed char * const *args, const signed char * const *env, struct apr_procattr_t *attr, struct apr_pool_t *pool)
{
  int i;
  const signed char * const empty_envp[1] = { (const signed char * const )NULL };
  if(env == ((const signed char * const *)NULL))
    env = empty_envp;

  new->in = attr->parent_in;
  new->err = attr->parent_err;
  new->out = attr->parent_out;
  int return_value_access$2;
  int *return_value___errno_location$1;
  _Bool tmp_condition$5;
  _Bool tmp_condition$6;
  _Bool tmp_condition$7;
  _Bool tmp_condition$8;
  int return_value_access$4;
  int *return_value___errno_location$3;
  if(!(attr->errchk == 0))
  {
    if(!(attr->currdir == ((signed char *)NULL)))
    {
      return_value_access$2=access(attr->currdir, 1);
      if(return_value_access$2 == -1)
      {
        return_value___errno_location$1=__errno_location();
        return *return_value___errno_location$1;
      }

    }

    tmp_condition$6 = attr->cmdtype == (int)/*enum*/1;
    if(!tmp_condition$6)
      tmp_condition$7 = attr->cmdtype == (int)/*enum*/2;

    tmp_condition$5 = tmp_condition$6 ? TRUE : (tmp_condition$7 ? TRUE : FALSE);
    if(!tmp_condition$5)
      tmp_condition$8 = (int)*progname == 47;

    if(!tmp_condition$5 && !tmp_condition$8)
      goto __CPROVER_DUMP_L6;

    return_value_access$4=access(progname, 1);
    if(return_value_access$4 == -1)
    {
      return_value___errno_location$3=__errno_location();
      return *return_value___errno_location$3;
    }

  }


__CPROVER_DUMP_L6:
  ;
  int return_value_fork$45;
  return_value_fork$45=fork();
  new->pid = return_value_fork$45;
  int *return_value___errno_location$9;
  struct apr_pool_t *return_value_apr_file_pool_get$10;
  struct apr_pool_t *return_value_apr_file_pool_get$11;
  struct apr_pool_t *return_value_apr_file_pool_get$12;
  _Bool tmp_condition$15;
  _Bool tmp_condition$16;
  _Bool tmp_condition$13;
  _Bool tmp_condition$14;
  _Bool tmp_condition$19;
  _Bool tmp_condition$20;
  _Bool tmp_condition$17;
  _Bool tmp_condition$18;
  _Bool tmp_condition$23;
  _Bool tmp_condition$24;
  _Bool tmp_condition$21;
  _Bool tmp_condition$22;
  int return_value_chdir$26;
  int *return_value___errno_location$25;
  _Bool tmp_condition$29;
  _Bool tmp_condition$30;
  unsigned int return_value_geteuid$31;
  int return_value_setgid$28;
  int *return_value___errno_location$27;
  _Bool tmp_condition$34;
  _Bool tmp_condition$35;
  unsigned int return_value_geteuid$36;
  int return_value_setuid$33;
  int *return_value___errno_location$32;
  int return_value_limit_proc$38;
  int *return_value___errno_location$37;
  _Bool tmp_condition$42;
  _Bool tmp_condition$43;
  int onearg_len;
  const signed char *newargs[4];
  unsigned long int return_value_strlen$39;
  signed char *ch;
  signed char *onearg;
  void *return_value_apr_palloc$40;
  unsigned long int return_value_strlen$41;
  unsigned long int len;
  signed char *desc;
  int *return_value___errno_location$44;
  if(new->pid < 0)
  {
    return_value___errno_location$9=__errno_location();
    return *return_value___errno_location$9;
  }

  else
    if(new->pid == 0)
    {
      if(!(attr->child_in == ((struct apr_file_t *)NULL)))
      {
        return_value_apr_file_pool_get$10=apr_file_pool_get(attr->child_in);
        apr_pool_cleanup_kill(return_value_apr_file_pool_get$10, (const void *)attr->child_in, apr_unix_file_cleanup);
      }

      if(!(attr->child_out == ((struct apr_file_t *)NULL)))
      {
        return_value_apr_file_pool_get$11=apr_file_pool_get(attr->child_out);
        apr_pool_cleanup_kill(return_value_apr_file_pool_get$11, (const void *)attr->child_out, apr_unix_file_cleanup);
      }

      if(!(attr->child_err == ((struct apr_file_t *)NULL)))
      {
        return_value_apr_file_pool_get$12=apr_file_pool_get(attr->child_err);
        apr_pool_cleanup_kill(return_value_apr_file_pool_get$12, (const void *)attr->child_err, apr_unix_file_cleanup);
      }

      apr_pool_cleanup_for_exec();
      tmp_condition$15 = (_Bool)attr->child_in;
      if(tmp_condition$15)
        tmp_condition$16 = attr->child_in->filedes == -1;

      if(tmp_condition$15 && tmp_condition$16)
        close(0);

      else
      {
        tmp_condition$13 = (_Bool)attr->child_in;
        if(tmp_condition$13)
          tmp_condition$14 = attr->child_in->filedes != 0;

        if(tmp_condition$13 && tmp_condition$14)
        {
          dup2(attr->child_in->filedes, 0);
          apr_file_close(attr->child_in);
        }

      }
      tmp_condition$19 = (_Bool)attr->child_out;
      if(tmp_condition$19)
        tmp_condition$20 = attr->child_out->filedes == -1;

      if(tmp_condition$19 && tmp_condition$20)
        close(1);

      else
      {
        tmp_condition$17 = (_Bool)attr->child_out;
        if(tmp_condition$17)
          tmp_condition$18 = attr->child_out->filedes != 1;

        if(tmp_condition$17 && tmp_condition$18)
        {
          dup2(attr->child_out->filedes, 1);
          apr_file_close(attr->child_out);
        }

      }
      tmp_condition$23 = (_Bool)attr->child_err;
      if(tmp_condition$23)
        tmp_condition$24 = attr->child_err->filedes == -1;

      if(tmp_condition$23 && tmp_condition$24)
        close(2);

      else
      {
        tmp_condition$21 = (_Bool)attr->child_err;
        if(tmp_condition$21)
          tmp_condition$22 = attr->child_err->filedes != 2;

        if(tmp_condition$21 && tmp_condition$22)
        {
          dup2(attr->child_err->filedes, 2);
          apr_file_close(attr->child_err);
        }

      }
      apr_signal(17, ((void (*)(int))NULL));
      if(!(attr->currdir == ((signed char *)NULL)))
      {
        return_value_chdir$26=chdir(attr->currdir);
        if(return_value_chdir$26 == -1)
        {
          if(!(attr->errfn == ((void (*)(struct apr_pool_t *, int, const signed char *))NULL)))
          {
            return_value___errno_location$25=__errno_location();
            attr->errfn(pool, *return_value___errno_location$25, "change of working directory failed");
          }

          _exit(-1);
        }

      }

      tmp_condition$29 = attr->gid != (unsigned int)-1;
      if(tmp_condition$29)
      {
        return_value_geteuid$31=geteuid();
        tmp_condition$30 = !((_Bool)return_value_geteuid$31);
      }

      if(tmp_condition$29 && tmp_condition$30)
      {
        return_value_setgid$28=setgid(attr->gid);
        if(!(return_value_setgid$28 == 0))
        {
          if(!(attr->errfn == ((void (*)(struct apr_pool_t *, int, const signed char *))NULL)))
          {
            return_value___errno_location$27=__errno_location();
            attr->errfn(pool, *return_value___errno_location$27, "setting of group failed");
          }

          _exit(-1);
        }

      }

      tmp_condition$34 = attr->uid != (unsigned int)-1;
      if(tmp_condition$34)
      {
        return_value_geteuid$36=geteuid();
        tmp_condition$35 = !((_Bool)return_value_geteuid$36);
      }

      if(tmp_condition$34 && tmp_condition$35)
      {
        return_value_setuid$33=setuid(attr->uid);
        if(!(return_value_setuid$33 == 0))
        {
          if(!(attr->errfn == ((void (*)(struct apr_pool_t *, int, const signed char *))NULL)))
          {
            return_value___errno_location$32=__errno_location();
            attr->errfn(pool, *return_value___errno_location$32, "setting of user failed");
          }

          _exit(-1);
        }

      }

      return_value_limit_proc$38=limit_proc(attr);
      if(!(return_value_limit_proc$38 == 0))
      {
        if(!(attr->errfn == ((void (*)(struct apr_pool_t *, int, const signed char *))NULL)))
        {
          return_value___errno_location$37=__errno_location();
          attr->errfn(pool, *return_value___errno_location$37, "setting of resource limits failed");
        }

        _exit(-1);
      }

      tmp_condition$42 = attr->cmdtype == (int)/*enum*/0;
      if(!tmp_condition$42)
        tmp_condition$43 = attr->cmdtype == (int)/*enum*/4;

      if(tmp_condition$42 || tmp_condition$43)
      {
        onearg_len = 0;
        newargs[(long int)0] = "/bin/sh";
        newargs[(long int)1] = "-c";
        i = 0;
        while(!(args[(long int)i] == ((const signed char * const )NULL)))
        {
          return_value_strlen$39=strlen(args[(long int)i]);
          onearg_len = onearg_len + (int)return_value_strlen$39;
          onearg_len;
          onearg_len = onearg_len + 1;
          i = i + 1;
        }
        switch(i)
        {

          case 0:
            goto __CPROVER_DUMP_L41;
          case 1:
            {
              newargs[(long int)2] = args[(long int)0];
              goto __CPROVER_DUMP_L41;
            }
          default:
            {
              return_value_apr_palloc$40=apr_palloc(pool, (unsigned long int)onearg_len);
              onearg = (signed char *)return_value_apr_palloc$40;
              ch = onearg;
              i = 0;
              while(!(args[(long int)i] == ((const signed char * const )NULL)))
              {
                return_value_strlen$41=strlen(args[(long int)i]);
                len = return_value_strlen$41;
                memcpy((void *)ch, (const void *)args[(long int)i], len);
                ch = ch + (long int)len;
                ch;
                *ch = (signed char)32;
                ch = ch + 1;
                ch;
                i = i + 1;
                i;
              }
              ch = ch - 1;
              ch;
              *ch = (signed char)0;
              newargs[(long int)2] = onearg;
            }
        }

      __CPROVER_DUMP_L41:
        ;
        newargs[(long int)3] = (const signed char *)NULL;
        if(!(attr->detached == 0))
          apr_proc_detach(1);

        if(attr->cmdtype == 0)
          execve("/bin/sh", (signed char ** const )newargs, (signed char ** const )env);

        else
          execv("/bin/sh", (signed char ** const )newargs);
      }

      else
        if(attr->cmdtype == 1)
        {
          if(!(attr->detached == 0))
            apr_proc_detach(1);

          execve(progname, (signed char ** const )args, (signed char ** const )env);
        }

        else
          if(attr->cmdtype == 2)
          {
            if(!(attr->detached == 0))
              apr_proc_detach(1);

            execv(progname, (signed char ** const )args);
          }

          else
          {
            if(!(attr->detached == 0))
              apr_proc_detach(1);

            execvp(progname, (signed char ** const )args);
          }
      if(!(attr->errfn == ((void (*)(struct apr_pool_t *, int, const signed char *))NULL)))
      {
        desc=apr_psprintf(pool, "exec of '%s' failed", progname);
        return_value___errno_location$44=__errno_location();
        attr->errfn(pool, *return_value___errno_location$44, desc);
      }

      _exit(-1);
    }

  _Bool tmp_condition$46 = (_Bool)attr->child_in;
  _Bool tmp_condition$47;
  if(tmp_condition$46)
    tmp_condition$47 = attr->child_in->filedes != -1;

  if(tmp_condition$46 && tmp_condition$47)
    apr_file_close(attr->child_in);

  _Bool tmp_condition$48 = (_Bool)attr->child_out;
  _Bool tmp_condition$49;
  if(tmp_condition$48)
    tmp_condition$49 = attr->child_out->filedes != -1;

  if(tmp_condition$48 && tmp_condition$49)
    apr_file_close(attr->child_out);

  _Bool tmp_condition$50 = (_Bool)attr->child_err;
  _Bool tmp_condition$51;
  if(tmp_condition$50)
    tmp_condition$51 = attr->child_err->filedes != -1;

  if(tmp_condition$50 && tmp_condition$51)
    apr_file_close(attr->child_err);

  return 0;
}

// c::apr_proc_fork
// file apr-1.4.6/threadproc/unix/proc.c line 219
int apr_proc_fork(struct apr_proc_t *proc, struct apr_pool_t *pool)
{
  int pid;
  memset((void *)proc, 0, 32 /*[[struct apr_proc_t]]*/);
  int return_value_fork$2;
  return_value_fork$2=fork();
  pid = return_value_fork$2;
  int *return_value___errno_location$1;
  if(pid < 0)
  {
    return_value___errno_location$1=__errno_location();
    return *return_value___errno_location$1;
  }

  else
    if(pid == 0)
    {
      proc->pid=getpid();
      apr_random_after_fork(proc);
      return 20000 + 50000 + 1;
    }

  proc->pid = pid;
  return 20000 + 50000 + 2;
}

// c::apr_proc_wait
// file apr-1.4.6/threadproc/unix/proc.c line 610
int apr_proc_wait(struct apr_proc_t *proc, int *exitcode, int, int)
{
union anon$6
{
  // __in
  int __in;
  // __i
  int __i;
};


union anon$7
{
  // __in
  int __in;
  // __i
  int __i;
};


  int pstatus;
  int waitpid_options = 2;
  int exit_int;
  int ignore;
  int;
  if(exitcode == ((int *)NULL))
    exitcode = &ignore;

  if(exitwhy == ((int)NULL))
    exitwhy = &ignorewhy;

  if(!(waithow == /*enum*/0))
  {
    waitpid_options = waitpid_options | 1;
    waitpid_options;
  }

  _Bool tmp_condition$1;
  _Bool tmp_condition$2;
  int *return_value___errno_location$3;
  do
  {
    pstatus=waitpid(proc->pid, &exit_int, waitpid_options);
    tmp_condition$1 = pstatus < 0;
    if(tmp_condition$1)
    {
      return_value___errno_location$3=__errno_location();
      tmp_condition$2 = *return_value___errno_location$3 == 4;
    }

  }
  while(tmp_condition$1 && tmp_condition$2);
  if(pstatus > 0)
  {
    proc->pid = pstatus;
    if((127 & ((union anon$6){ .__in=exit_int }).__i) == 0)
    {
      *exitwhy = /*enum*/1;
      *exitcode = (((union anon$6){ .__in=exit_int }).__i & 65280) >> 8;
    }

    else
      if((int)((signed char)(127 & ((union anon$7){ .__in=exit_int }).__i) + 1) >> 1 > 0)
      {
        *exitwhy = /*enum*/2;
        if(!((128 & ((union anon$6){ .__in=exit_int }).__i) == 0))
        {
          *exitwhy = *exitwhy | (int)/*enum*/4;
          *exitwhy;
        }

        *exitcode = ((union anon$7){ .__in=exit_int }).__i & 127;
      }

      else
        return 20000 + 14;
    return 20000 + 50000 + 5;
  }

  else
    if(pstatus == 0)
      return 20000 + 50000 + 6;

  int *return_value___errno_location$4;
  return_value___errno_location$4=__errno_location();
  return *return_value___errno_location$4;
}

// c::apr_proc_wait_all_procs
// file apr-1.4.6/threadproc/unix/proc.c line 600
int apr_proc_wait_all_procs(struct apr_proc_t *proc, int *exitcode, int, int, struct apr_pool_t *p)
{
  proc->pid = -1;
  int return_value_apr_proc_wait$1;
  return_value_apr_proc_wait$1=apr_proc_wait(proc, exitcode, exitwhy, waithow);
  return return_value_apr_proc_wait$1;
}

// c::apr_procattr_addrspace_set
// file apr-1.4.6/threadproc/unix/proc.c line 307
int apr_procattr_addrspace_set(struct apr_procattr_t *attr, int addrspace)
{
  return 0;
}

// c::apr_procattr_child_err_set
// file apr-1.4.6/threadproc/unix/proc.c line 161
int apr_procattr_child_err_set(struct apr_procattr_t *attr, struct apr_file_t *child_err, struct apr_file_t *parent_err)
{
  int rv = 0;
  _Bool tmp_condition$2;
  _Bool tmp_condition$3;
  _Bool tmp_condition$4 = attr->child_err == (struct apr_file_t *)NULL;
  _Bool tmp_condition$5;
  if(tmp_condition$4)
    tmp_condition$5 = attr->parent_err == (struct apr_file_t *)NULL;

  tmp_condition$3 = tmp_condition$4 ? (tmp_condition$5 ? TRUE : FALSE) : FALSE;
  tmp_condition$2 = tmp_condition$3 ? (child_err == (struct apr_file_t *)NULL ? TRUE : FALSE) : FALSE;
  int return_value_apr_file_pipe_create$1;
  if(parent_err == ((struct apr_file_t *)NULL) && tmp_condition$2)
  {
    return_value_apr_file_pipe_create$1=apr_file_pipe_create(&attr->parent_err, &attr->child_err, attr->pool);
    rv = return_value_apr_file_pipe_create$1;
    if(rv == 0)
      rv=apr_file_inherit_unset(attr->parent_err);

  }

  _Bool tmp_condition$7;
  _Bool tmp_condition$8;
  int return_value_apr_file_dup$6;
  if(!(child_err == ((struct apr_file_t *)NULL)))
  {
    if(rv == 0)
    {
      tmp_condition$7 = (_Bool)attr->child_err;
      if(tmp_condition$7)
        tmp_condition$8 = attr->child_err->filedes != -1;

      if(tmp_condition$7 && tmp_condition$8)
        rv=apr_file_dup2(attr->child_err, child_err, attr->pool);

      else
      {
        attr->child_err = (struct apr_file_t *)NULL;
        return_value_apr_file_dup$6=apr_file_dup(&attr->child_err, child_err, attr->pool);
        rv = return_value_apr_file_dup$6;
        if(rv == 0)
          rv=apr_file_inherit_set(attr->child_err);

      }
    }

  }

  if(!(parent_err == ((struct apr_file_t *)NULL)))
  {
    if(rv == 0)
    {
      if(!(attr->parent_err == ((struct apr_file_t *)NULL)))
        rv=apr_file_dup2(attr->parent_err, parent_err, attr->pool);

      else
        rv=apr_file_dup(&attr->parent_err, parent_err, attr->pool);
    }

  }

  return rv;
}

// c::apr_procattr_child_errfn_set
// file apr-1.4.6/threadproc/unix/proc.c line 293
int apr_procattr_child_errfn_set(struct apr_procattr_t *attr, void (*errfn)(struct apr_pool_t *, int, const signed char *))
{
  attr->errfn = errfn;
  return 0;
}

// c::apr_procattr_child_in_set
// file apr-1.4.6/threadproc/unix/proc.c line 93
int apr_procattr_child_in_set(struct apr_procattr_t *attr, struct apr_file_t *child_in, struct apr_file_t *parent_in)
{
  int rv = 0;
  _Bool tmp_condition$2;
  _Bool tmp_condition$3;
  _Bool tmp_condition$4 = attr->child_in == (struct apr_file_t *)NULL;
  _Bool tmp_condition$5;
  if(tmp_condition$4)
    tmp_condition$5 = attr->parent_in == (struct apr_file_t *)NULL;

  tmp_condition$3 = tmp_condition$4 ? (tmp_condition$5 ? TRUE : FALSE) : FALSE;
  tmp_condition$2 = tmp_condition$3 ? (child_in == (struct apr_file_t *)NULL ? TRUE : FALSE) : FALSE;
  int return_value_apr_file_pipe_create$1;
  if(parent_in == ((struct apr_file_t *)NULL) && tmp_condition$2)
  {
    return_value_apr_file_pipe_create$1=apr_file_pipe_create(&attr->child_in, &attr->parent_in, attr->pool);
    rv = return_value_apr_file_pipe_create$1;
    if(rv == 0)
      rv=apr_file_inherit_unset(attr->parent_in);

  }

  _Bool tmp_condition$7;
  _Bool tmp_condition$8;
  int return_value_apr_file_dup$6;
  if(!(child_in == ((struct apr_file_t *)NULL)))
  {
    if(rv == 0)
    {
      tmp_condition$7 = (_Bool)attr->child_in;
      if(tmp_condition$7)
        tmp_condition$8 = attr->child_in->filedes != -1;

      if(tmp_condition$7 && tmp_condition$8)
        rv=apr_file_dup2(attr->child_in, child_in, attr->pool);

      else
      {
        attr->child_in = (struct apr_file_t *)NULL;
        return_value_apr_file_dup$6=apr_file_dup(&attr->child_in, child_in, attr->pool);
        rv = return_value_apr_file_dup$6;
        if(rv == 0)
          rv=apr_file_inherit_set(attr->child_in);

      }
    }

  }

  if(!(parent_in == ((struct apr_file_t *)NULL)))
  {
    if(rv == 0)
    {
      if(!(attr->parent_in == ((struct apr_file_t *)NULL)))
        rv=apr_file_dup2(attr->parent_in, parent_in, attr->pool);

      else
        rv=apr_file_dup(&attr->parent_in, parent_in, attr->pool);
    }

  }

  return rv;
}

// c::apr_procattr_child_out_set
// file apr-1.4.6/threadproc/unix/proc.c line 127
int apr_procattr_child_out_set(struct apr_procattr_t *attr, struct apr_file_t *child_out, struct apr_file_t *parent_out)
{
  int rv = 0;
  _Bool tmp_condition$2;
  _Bool tmp_condition$3;
  _Bool tmp_condition$4 = attr->child_out == (struct apr_file_t *)NULL;
  _Bool tmp_condition$5;
  if(tmp_condition$4)
    tmp_condition$5 = attr->parent_out == (struct apr_file_t *)NULL;

  tmp_condition$3 = tmp_condition$4 ? (tmp_condition$5 ? TRUE : FALSE) : FALSE;
  tmp_condition$2 = tmp_condition$3 ? (child_out == (struct apr_file_t *)NULL ? TRUE : FALSE) : FALSE;
  int return_value_apr_file_pipe_create$1;
  if(parent_out == ((struct apr_file_t *)NULL) && tmp_condition$2)
  {
    return_value_apr_file_pipe_create$1=apr_file_pipe_create(&attr->parent_out, &attr->child_out, attr->pool);
    rv = return_value_apr_file_pipe_create$1;
    if(rv == 0)
      rv=apr_file_inherit_unset(attr->parent_out);

  }

  _Bool tmp_condition$7;
  _Bool tmp_condition$8;
  int return_value_apr_file_dup$6;
  if(!(child_out == ((struct apr_file_t *)NULL)))
  {
    if(rv == 0)
    {
      tmp_condition$7 = (_Bool)attr->child_out;
      if(tmp_condition$7)
        tmp_condition$8 = attr->child_out->filedes != -1;

      if(tmp_condition$7 && tmp_condition$8)
        rv=apr_file_dup2(attr->child_out, child_out, attr->pool);

      else
      {
        attr->child_out = (struct apr_file_t *)NULL;
        return_value_apr_file_dup$6=apr_file_dup(&attr->child_out, child_out, attr->pool);
        rv = return_value_apr_file_dup$6;
        if(rv == 0)
          rv=apr_file_inherit_set(attr->child_out);

      }
    }

  }

  if(!(parent_out == ((struct apr_file_t *)NULL)))
  {
    if(rv == 0)
    {
      if(!(attr->parent_out == ((struct apr_file_t *)NULL)))
        rv=apr_file_dup2(attr->parent_out, parent_out, attr->pool);

      else
        rv=apr_file_dup(&attr->parent_out, parent_out, attr->pool);
    }

  }

  return rv;
}

// c::apr_procattr_cmdtype_set
// file apr-1.4.6/threadproc/unix/proc.c line 205
int apr_procattr_cmdtype_set(struct apr_procattr_t *attr, int)
{
  attr->cmdtype = (int)cmd;
  return 0;
}

// c::apr_procattr_create
// file apr-1.4.6/threadproc/unix/proc.c line 28
int apr_procattr_create(struct apr_procattr_t **new, struct apr_pool_t *pool)
{
  void *return_value_apr_palloc$1;
  return_value_apr_palloc$1=apr_palloc(pool, 128 /*[[struct apr_procattr_t]]*/);
  void *return_value_memset$2;
  return_value_memset$2=memset(return_value_apr_palloc$1, 0, 128 /*[[struct apr_procattr_t]]*/);
  *new = (struct apr_procattr_t *)return_value_memset$2;
  if(*new == ((struct apr_procattr_t *)NULL))
    return 12;

  (*new)->pool = pool;
  (*new)->cmdtype = (int)/*enum*/1;
  (*new)->gid = (unsigned int)-1;
  (*new)->uid = (*new)->gid;
  return 0;
}

// c::apr_procattr_detach_set
// file apr-1.4.6/threadproc/unix/proc.c line 212
int apr_procattr_detach_set(struct apr_procattr_t *attr, int detach)
{
  attr->detached = detach;
  return 0;
}

// c::apr_procattr_dir_set
// file apr-1.4.6/threadproc/unix/proc.c line 194
int apr_procattr_dir_set(struct apr_procattr_t *attr, const signed char *dir)
{
  attr->currdir=apr_pstrdup(attr->pool, dir);
  if(!(attr->currdir == ((signed char *)NULL)))
    return 0;

  return 12;
}

// c::apr_procattr_error_check_set
// file apr-1.4.6/threadproc/unix/proc.c line 300
int apr_procattr_error_check_set(struct apr_procattr_t *attr, int chk)
{
  attr->errchk = chk;
  return 0;
}

// c::apr_procattr_group_set
// file apr-1.4.6/threadproc/unix/proc.c line 334
int apr_procattr_group_set(struct apr_procattr_t *attr, const signed char *groupname)
{
  int rv;
  int return_value_apr_gid_get$1;
  return_value_apr_gid_get$1=apr_gid_get(&attr->gid, groupname, attr->pool);
  rv = return_value_apr_gid_get$1;
  if(!(rv == 0))
    attr->gid = (unsigned int)-1;

  return rv;
}

// c::apr_procattr_io_set
// file apr-1.4.6/threadproc/unix/proc.c line 42
int apr_procattr_io_set(struct apr_procattr_t *attr, int in, int out, int err)
{
  int rv;
  int return_value_apr_file_pipe_create_ex$1;
  if(!(in == 0))
  {
    if(in == 8)
      goto __CPROVER_DUMP_L5;

    if(in == 4)
      in = 3;

    else
      if(in == 3)
        in = 4;

    return_value_apr_file_pipe_create_ex$1=apr_file_pipe_create_ex(&attr->child_in, &attr->parent_in, in, attr->pool);
    rv = return_value_apr_file_pipe_create_ex$1;
    if(rv == 0)
      rv=apr_file_inherit_unset(attr->parent_in);

    if(!(rv == 0))
      return rv;

  }

  else
  {

  __CPROVER_DUMP_L5:
    ;
    if(in == 8)
      attr->child_in = &no_file;

  }
  int return_value_apr_file_pipe_create_ex$2;
  if(!(out == 0))
  {
    if(out == 8)
      goto __CPROVER_DUMP_L9;

    return_value_apr_file_pipe_create_ex$2=apr_file_pipe_create_ex(&attr->parent_out, &attr->child_out, out, attr->pool);
    rv = return_value_apr_file_pipe_create_ex$2;
    if(rv == 0)
      rv=apr_file_inherit_unset(attr->parent_out);

    if(!(rv == 0))
      return rv;

  }

  else
  {

  __CPROVER_DUMP_L9:
    ;
    if(out == 8)
      attr->child_out = &no_file;

  }
  int return_value_apr_file_pipe_create_ex$3;
  if(!(err == 0))
  {
    if(err == 8)
      goto __CPROVER_DUMP_L13;

    return_value_apr_file_pipe_create_ex$3=apr_file_pipe_create_ex(&attr->parent_err, &attr->child_err, err, attr->pool);
    rv = return_value_apr_file_pipe_create_ex$3;
    if(rv == 0)
      rv=apr_file_inherit_unset(attr->parent_err);

    if(!(rv == 0))
      return rv;

  }

  else
  {

  __CPROVER_DUMP_L13:
    ;
    if(err == 8)
      attr->child_err = &no_file;

  }
  return 0;
}

// c::apr_procattr_limit_set
// file apr-1.4.6/threadproc/unix/proc.c line 669
int apr_procattr_limit_set(struct apr_procattr_t *attr, int what, struct rlimit *limit)
{
  switch(what)
  {

    case 0:
      {
        attr->limit_cpu = limit;
        goto __CPROVER_DUMP_L5;
      }
    case 1:
      {
        attr->limit_mem = limit;
        goto __CPROVER_DUMP_L5;
      }
    case 2:
      {
        attr->limit_nproc = limit;
        goto __CPROVER_DUMP_L5;
      }
    case 3:
      attr->limit_nofile = limit;
    default:
      {

      __CPROVER_DUMP_L5:
        ;
        return 0;
      }
  }
}

// c::apr_procattr_user_set
// file apr-1.4.6/threadproc/unix/proc.c line 314
int apr_procattr_user_set(struct apr_procattr_t *attr, const signed char *username, const signed char *password)
{
  int rv;
  unsigned int gid;
  int return_value_apr_uid_get$1;
  return_value_apr_uid_get$1=apr_uid_get(&attr->uid, &gid, username, attr->pool);
  rv = return_value_apr_uid_get$1;
  if(!(rv == 0))
  {
    attr->uid = (unsigned int)-1;
    return rv;
  }

  if(attr->gid == 4294967295)
    attr->gid = gid;

  return 0;
}

// c::apr_thread_cond_broadcast
// file apr-1.4.6/include/apr_thread_cond.h line 117
int apr_thread_cond_broadcast(struct apr_thread_cond_t *cond)
{
  int rv;
  rv=pthread_cond_broadcast(&cond->cond);
  return rv;
}

// c::apr_thread_cond_create
// file apr-1.4.6/include/apr_thread_cond.h line 59
int apr_thread_cond_create(struct apr_thread_cond_t **cond, struct apr_pool_t *pool)
{
  struct apr_thread_cond_t *new_cond;
  int rv;
  void *return_value_apr_palloc$1;
  return_value_apr_palloc$1=apr_palloc(pool, 56 /*[[struct apr_thread_cond_t]]*/);
  new_cond = (struct apr_thread_cond_t *)return_value_apr_palloc$1;
  new_cond->pool = pool;
  int return_value_pthread_cond_init$2;
  return_value_pthread_cond_init$2=pthread_cond_init(&new_cond->cond, (union anon$4 *)NULL);
  rv = return_value_pthread_cond_init$2;
  if(!(rv == 0))
    return rv;

  apr_pool_cleanup_register(new_cond->pool, (void *)new_cond, thread_cond_cleanup, apr_pool_cleanup_null);
  *cond = new_cond;
  return 0;
}

// c::apr_thread_cond_destroy
// file apr-1.4.6/include/apr_thread_cond.h line 123
int apr_thread_cond_destroy(struct apr_thread_cond_t *cond)
{
  int return_value_apr_pool_cleanup_run$1;
  return_value_apr_pool_cleanup_run$1=apr_pool_cleanup_run(cond->pool, (void *)cond, thread_cond_cleanup);
  return return_value_apr_pool_cleanup_run$1;
}

// c::apr_thread_cond_pool_get
// file apr-1.4.6/locks/unix/thread_cond.c line 133
struct apr_pool_t * apr_thread_cond_pool_get(struct apr_thread_cond_t *thethread_cond)
{
  return thethread_cond->pool;
}

// c::apr_thread_cond_signal
// file apr-1.4.6/include/apr_thread_cond.h line 108
int apr_thread_cond_signal(struct apr_thread_cond_t *cond)
{
  int rv;
  rv=pthread_cond_signal(&cond->cond);
  return rv;
}

// c::apr_thread_cond_timedwait
// file apr-1.4.6/locks/unix/thread_cond.c line 77
int apr_thread_cond_timedwait(struct apr_thread_cond_t *cond, struct apr_thread_mutex_t *mutex, long int timeout)
{
  int rv;
  long int then;
  struct timespec abstime;
  long int return_value_apr_time_now$1;
  return_value_apr_time_now$1=apr_time_now();
  then = return_value_apr_time_now$1 + timeout;
  abstime.tv_sec = then / 1000000;
  abstime.tv_nsec = (then % 1000000) * (signed long int)1000;
  rv=pthread_cond_timedwait(&cond->cond, &mutex->mutex, &abstime);
  if(rv == 110)
    return 20000 + 50000 + 7;

  return rv;
}

// c::apr_thread_cond_wait
// file apr-1.4.6/include/apr_thread_cond.h line 77
int apr_thread_cond_wait(struct apr_thread_cond_t *cond, struct apr_thread_mutex_t *mutex)
{
  int rv;
  rv=pthread_cond_wait(&cond->cond, &mutex->mutex);
  return rv;
}

// c::apr_thread_mutex_create
// file apr-1.4.6/include/apr_thread_mutex.h line 65
int apr_thread_mutex_create(struct apr_thread_mutex_t **mutex, unsigned int flags, struct apr_pool_t *pool)
{
  struct apr_thread_mutex_t *new_mutex;
  int rv;
  void *return_value_apr_palloc$1;
  return_value_apr_palloc$1=apr_palloc(pool, 48 /*[[struct apr_thread_mutex_t]]*/);
  void *return_value_memset$2;
  return_value_memset$2=memset(return_value_apr_palloc$1, 0, 48 /*[[struct apr_thread_mutex_t]]*/);
  new_mutex = (struct apr_thread_mutex_t *)return_value_memset$2;
  new_mutex->pool = pool;
  union anon$4 mattr;
  if(!((1 & flags) == 0))
  {
    rv=pthread_mutexattr_init(&mattr);
    if(!(rv == 0))
      return rv;

    rv=pthread_mutexattr_settype(&mattr, (int)/*enum*/1);
    if(!(rv == 0))
    {
      pthread_mutexattr_destroy(&mattr);
      return rv;
    }

    rv=pthread_mutex_init(&new_mutex->mutex, &mattr);
    pthread_mutexattr_destroy(&mattr);
  }

  else
    rv=pthread_mutex_init(&new_mutex->mutex, (union anon$4 *)NULL);
  if(!(rv == 0))
    return rv;

  apr_pool_cleanup_register(new_mutex->pool, (const void *)new_mutex, thread_mutex_cleanup, apr_pool_cleanup_null);
  *mutex = new_mutex;
  return 0;
}

// c::apr_thread_mutex_destroy
// file apr-1.4.6/include/apr_thread_mutex.h line 94
int apr_thread_mutex_destroy(struct apr_thread_mutex_t *mutex)
{
  int return_value_apr_pool_cleanup_run$1;
  return_value_apr_pool_cleanup_run$1=apr_pool_cleanup_run(mutex->pool, (void *)mutex, thread_mutex_cleanup);
  return return_value_apr_pool_cleanup_run$1;
}

// c::apr_thread_mutex_lock
// file apr-1.4.6/include/apr_thread_mutex.h line 73
int apr_thread_mutex_lock(struct apr_thread_mutex_t *mutex)
{
  int rv;
  rv=pthread_mutex_lock(&mutex->mutex);
  return rv;
}

// c::apr_thread_mutex_pool_get
// file apr-1.4.6/locks/unix/thread_mutex.c line 136
struct apr_pool_t * apr_thread_mutex_pool_get(struct apr_thread_mutex_t *thethread_mutex)
{
  return thethread_mutex->pool;
}

// c::apr_thread_mutex_trylock
// file apr-1.4.6/locks/unix/thread_mutex.c line 102
int apr_thread_mutex_trylock(struct apr_thread_mutex_t *mutex)
{
  int rv;
  rv=pthread_mutex_trylock(&mutex->mutex);
  if(!(rv == 0))
    return rv == 16 ? 20000 + 50000 + 25 : rv;

  return 0;
}

// c::apr_thread_mutex_unlock
// file apr-1.4.6/include/apr_thread_mutex.h line 88
int apr_thread_mutex_unlock(struct apr_thread_mutex_t *mutex)
{
  int status;
  status=pthread_mutex_unlock(&mutex->mutex);
  return status;
}

// c::limit_proc
// file apr-1.4.6/threadproc/unix/proc.c line 241
static int limit_proc(struct apr_procattr_t *attr)
{
  int return_value_setrlimit$2;
  int *return_value___errno_location$1;
  if(!(attr->limit_cpu == ((struct rlimit *)NULL)))
  {
    return_value_setrlimit$2=setrlimit(/*enum*/0, attr->limit_cpu);
    if(!(return_value_setrlimit$2 == 0))
    {
      return_value___errno_location$1=__errno_location();
      return *return_value___errno_location$1;
    }

  }

  int return_value_setrlimit$4;
  int *return_value___errno_location$3;
  if(!(attr->limit_nproc == ((struct rlimit *)NULL)))
  {
    return_value_setrlimit$4=setrlimit(/*enum*/6, attr->limit_nproc);
    if(!(return_value_setrlimit$4 == 0))
    {
      return_value___errno_location$3=__errno_location();
      return *return_value___errno_location$3;
    }

  }

  int return_value_setrlimit$6;
  int *return_value___errno_location$5;
  if(!(attr->limit_nofile == ((struct rlimit *)NULL)))
  {
    return_value_setrlimit$6=setrlimit(/*enum*/7, attr->limit_nofile);
    if(!(return_value_setrlimit$6 == 0))
    {
      return_value___errno_location$5=__errno_location();
      return *return_value___errno_location$5;
    }

  }

  int return_value_setrlimit$8;
  int *return_value___errno_location$7;
  if(!(attr->limit_mem == ((struct rlimit *)NULL)))
  {
    return_value_setrlimit$8=setrlimit(/*enum*/9, attr->limit_mem);
    if(!(return_value_setrlimit$8 == 0))
    {
      return_value___errno_location$7=__errno_location();
      return *return_value___errno_location$7;
    }

  }

  return 0;
}

// c::main
// file fdqueue_main.c line 33
int main()
{
  int max_idlers = 10;
  int max_recycled_pools = 10;
  ap_queue_info_create(&M_queue_info, M_pool, max_idlers, max_recycled_pools);

__CPROVER_ASYNC_1:
  worker_thread();
  int had_to_block;
  ap_queue_info_wait_for_idler(M_queue_info, &had_to_block);
  /* pool handed back */
  assert(pool_handed_back);
}

// c::queue_info_cleanup
// file httpd-2.4.2/server/mpm/event/fdqueue.c line 42
static int queue_info_cleanup(void *data_)
{
  struct fd_queue_info_t *qi = (struct fd_queue_info_t *)data_;
  apr_thread_cond_destroy(qi->wait_for_idler);
  apr_thread_mutex_destroy(qi->idlers_mutex);
  struct recycled_pool *first_pool;
  void *return_value_apr_atomic_casptr$1;
  do
  {
    first_pool = qi->recycled_pools;
    if(first_pool == ((struct recycled_pool *)NULL))
      goto __CPROVER_DUMP_L3;

    return_value_apr_atomic_casptr$1=apr_atomic_casptr((volatile void **)(void *)&qi->recycled_pools, (void *)first_pool->next, (const void *)first_pool);
    if((struct recycled_pool *)return_value_apr_atomic_casptr$1 == first_pool)
      apr_pool_destroy(first_pool->pool);

  }
  while(TRUE);

__CPROVER_DUMP_L3:
  ;
  return 0;
}

// c::thread_cond_cleanup
// file apr-1.4.6/locks/unix/thread_cond.c line 24
static int thread_cond_cleanup(void *data)
{
  struct apr_thread_cond_t *cond = (struct apr_thread_cond_t *)data;
  int rv;
  rv=pthread_cond_destroy(&cond->cond);
  return rv;
}

// c::thread_mutex_cleanup
// file apr-1.4.6/locks/unix/thread_mutex.c line 23
static int thread_mutex_cleanup(void *data)
{
  struct apr_thread_mutex_t *mutex = (struct apr_thread_mutex_t *)data;
  int rv;
  rv=pthread_mutex_destroy(&mutex->mutex);
  return rv;
}

// c::worker_thread
// file fdqueue_main.c line 27
void worker_thread(void)
{
  pool_handed_back = 1 == 0 ? FALSE : TRUE;
  ap_queue_info_set_idle(M_queue_info, M_pool);
}
