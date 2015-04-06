#include "clap_monitor.hh"
#include "clap_none.hh"
#include "clap_echo.hh"
#include "clap_ucg.hh"
#include "clap_eraser.hh"
#include "clap_inst.hh"
#include "clap_typest.hh"
#include "clap_poly.hh"
#include "clap_auto.hh"

#define CLAP_FLAG_NONE     0
#define CLAP_FLAG_ECHO     1
#define CLAP_FLAG_ERASER   2
#define CLAP_FLAG_UCG      3
#define CLAP_FLAG_INST     4
#define CLAP_FLAG_TYPEST   5
#define CLAP_FLAG_POLY     6
#define CLAP_FLAG_AUTO     7
#define CLAP_FLAG_DEFAULT  CLAP_FLAG_AUTO

//----------------------------------------------------------------------------//
// Start of the function pointer definitions
//----------------------------------------------------------------------------//
void (*monitor_thread_start)();
void (*monitor_thread_end)();
void (*monitor_thread_create)(pthread_t *, const pthread_attr_t *, void *(*)(void*), void *);
void (*monitor_thread_join)(pthread_t thread, void **value_ptr);
void (*monitor_mutex_init)(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
void (*monitor_mutex_destroy)(pthread_mutex_t *mutex);
void (*monitor_mutex_lock)(pthread_mutex_t *mutex);
void (*monitor_mutex_trylock)(pthread_mutex_t *mutex);
void (*monitor_mutex_timedlock)(pthread_mutex_t *mutex, const struct timespec *abstime);
void (*monitor_mutex_unlock)(pthread_mutex_t *mutex);
void (*monitor_cond_init)(pthread_cond_t * cond, const pthread_condattr_t * attr);
void (*monitor_cond_destroy)(pthread_cond_t *cond);
void (*monitor_cond_wait)(pthread_cond_t * cond, pthread_mutex_t * mutex);
void (*monitor_cond_timedwait)(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime);
void (*monitor_cond_broadcast)(pthread_cond_t *cond);
void (*monitor_cond_signal)(pthread_cond_t *cond);
void (*monitor_atomic_load)(int* addr, const int mem_odr);
void (*monitor_atomic_store)(int* addr, const int mem_odr);
void (*monitor_obj_read)(int* addr);
void (*monitor_obj_write)(int* addr);
void (*monitor_call_begin)(char* fn, char* ptr);
void (*monitor_call_end)(char* fn, char* ptr);
void (*monitor_inst_begin)(int inst, int stat);
void (*monitor_inst_end)(int inst, int stat, int retval);
//----------------------------------------------------------------------------//
// End of the function pointer definitions
//----------------------------------------------------------------------------//


int clap_read_flag()
{
  char *flag_str = getenv("CLAP_FLAG");
  int flag = (flag_str==NULL) ? CLAP_FLAG_DEFAULT : atoi(flag_str);
  //  flag = CLAP_FLAG_POLY;
  return flag;
}

//----------------------------------------------------------------------------
// Start: set up the monitor function pointers upon initialization
//----------------------------------------------------------------------------
class _ClapMonitor {
public:

  _ClapMonitor() {
    int flag = clap_read_flag();
    switch (flag) {

    case CLAP_FLAG_ECHO: 
      monitor_thread_start    = _echo_thread_start;
      monitor_thread_end      = _echo_thread_end;
      monitor_thread_create   = _echo_thread_create;
      monitor_thread_join     = _echo_thread_join;
      monitor_mutex_init      = _echo_mutex_init;
      monitor_mutex_destroy   = _echo_mutex_destroy;
      monitor_mutex_lock      = _echo_mutex_lock;
      monitor_mutex_trylock   = _echo_mutex_trylock;
      monitor_mutex_timedlock = _echo_mutex_timedlock;
      monitor_mutex_unlock    = _echo_mutex_unlock;
      monitor_cond_init       = _echo_cond_init;
      monitor_cond_destroy    = _echo_cond_destroy;
      monitor_cond_wait       = _echo_cond_wait;
      monitor_cond_timedwait  = _echo_cond_timedwait;
      monitor_cond_broadcast  = _echo_cond_broadcast;
      monitor_cond_signal     = _echo_cond_signal;
      monitor_obj_read        = _echo_obj_read;
      monitor_obj_write       = _echo_obj_write;
      monitor_call_begin      = _echo_call_begin;
      monitor_call_end        = _echo_call_end;
      monitor_inst_begin      = _echo_inst_begin;
      monitor_inst_end        = _echo_inst_end;
      break;

    case CLAP_FLAG_ERASER: 
      monitor_thread_start    = _eraser_thread_start;
      monitor_thread_end      = _eraser_thread_end;
      monitor_thread_create   = _eraser_thread_create;
      monitor_thread_join     = _eraser_thread_join;
      monitor_mutex_init      = _eraser_mutex_init;
      monitor_mutex_destroy   = _eraser_mutex_destroy;
      monitor_mutex_lock      = _eraser_mutex_lock;
      monitor_mutex_trylock   = _eraser_mutex_trylock;
      monitor_mutex_timedlock = _eraser_mutex_timedlock;
      monitor_mutex_unlock    = _eraser_mutex_unlock;
      monitor_cond_init       = _eraser_cond_init;
      monitor_cond_destroy    = _eraser_cond_destroy;
      monitor_cond_wait       = _eraser_cond_wait;
      monitor_cond_timedwait  = _eraser_cond_timedwait;
      monitor_cond_broadcast  = _eraser_cond_broadcast;
      monitor_cond_signal     = _eraser_cond_signal;
      monitor_obj_read        = _eraser_obj_read;
      monitor_obj_write       = _eraser_obj_write;
      monitor_call_begin      = _eraser_call_begin;
      monitor_call_end        = _eraser_call_end;
      monitor_inst_begin      = _eraser_inst_begin;
      monitor_inst_end        = _eraser_inst_end;
      break;

    case CLAP_FLAG_UCG: 
      monitor_thread_start    = _ucg_thread_start;
      monitor_thread_end      = _ucg_thread_end;
      monitor_thread_create   = _ucg_thread_create;
      monitor_thread_join     = _ucg_thread_join;
      monitor_mutex_init      = _ucg_mutex_init;
      monitor_mutex_destroy   = _ucg_mutex_destroy;
      monitor_mutex_lock      = _ucg_mutex_lock;
      monitor_mutex_trylock   = _ucg_mutex_trylock;
      monitor_mutex_timedlock = _ucg_mutex_timedlock;
      monitor_mutex_unlock    = _ucg_mutex_unlock;
      monitor_cond_init       = _ucg_cond_init;
      monitor_cond_destroy    = _ucg_cond_destroy;
      monitor_cond_wait       = _ucg_cond_wait;
      monitor_cond_timedwait  = _ucg_cond_timedwait;
      monitor_cond_broadcast  = _ucg_cond_broadcast;
      monitor_cond_signal     = _ucg_cond_signal;
      monitor_atomic_load     = _ucg_atomic_load;
      monitor_atomic_store    = _ucg_atomic_store;
      monitor_obj_read        = _ucg_obj_read;
      monitor_obj_write       = _ucg_obj_write;
      monitor_call_begin      = _ucg_call_begin;
      monitor_call_end        = _ucg_call_end;
      monitor_inst_begin      = _ucg_inst_begin;
      monitor_inst_end        = _ucg_inst_end;
      break;

    case CLAP_FLAG_INST: 
      monitor_thread_start    = _inst_thread_start;
      monitor_thread_end      = _inst_thread_end;
      monitor_thread_create   = _inst_thread_create;
      monitor_thread_join     = _inst_thread_join;
      monitor_mutex_init      = _inst_mutex_init;
      monitor_mutex_destroy   = _inst_mutex_destroy;
      monitor_mutex_lock      = _inst_mutex_lock;
      monitor_mutex_trylock   = _inst_mutex_trylock;
      monitor_mutex_timedlock = _inst_mutex_timedlock;
      monitor_mutex_unlock    = _inst_mutex_unlock;
      monitor_cond_init       = _inst_cond_init;
      monitor_cond_destroy    = _inst_cond_destroy;
      monitor_cond_wait       = _inst_cond_wait;
      monitor_cond_timedwait  = _inst_cond_timedwait;
      monitor_cond_broadcast  = _inst_cond_broadcast;
      monitor_cond_signal     = _inst_cond_signal;
      monitor_obj_read        = _inst_obj_read;
      monitor_obj_write       = _inst_obj_write;
      monitor_call_begin      = _inst_call_begin;
      monitor_call_end        = _inst_call_end;
      monitor_inst_begin      = _inst_inst_begin;
      monitor_inst_end        = _inst_inst_end;
      break;

    case CLAP_FLAG_TYPEST: 
      monitor_thread_start    = _typest_thread_start;
      monitor_thread_end      = _typest_thread_end;
      monitor_thread_create   = _typest_thread_create;
      monitor_thread_join     = _typest_thread_join;
      monitor_mutex_init      = _typest_mutex_init;
      monitor_mutex_destroy   = _typest_mutex_destroy;
      monitor_mutex_lock      = _typest_mutex_lock;
      monitor_mutex_trylock   = _typest_mutex_trylock;
      monitor_mutex_timedlock = _typest_mutex_timedlock;
      monitor_mutex_unlock    = _typest_mutex_unlock;
      monitor_cond_init       = _typest_cond_init;
      monitor_cond_destroy    = _typest_cond_destroy;
      monitor_cond_wait       = _typest_cond_wait;
      monitor_cond_timedwait  = _typest_cond_timedwait;
      monitor_cond_broadcast  = _typest_cond_broadcast;
      monitor_cond_signal     = _typest_cond_signal;
      monitor_obj_read        = _typest_obj_read;
      monitor_obj_write       = _typest_obj_write;
      monitor_call_begin      = _typest_call_begin;
      monitor_call_end        = _typest_call_end;
      monitor_inst_begin      = _typest_inst_begin;
      monitor_inst_end        = _typest_inst_end;
      break;

    case CLAP_FLAG_POLY: 
      monitor_thread_start    = _poly_thread_start;
      monitor_thread_end      = _poly_thread_end;
      monitor_thread_create   = _poly_thread_create;
      monitor_thread_join     = _poly_thread_join;
      monitor_mutex_init      = _poly_mutex_init;
      monitor_mutex_destroy   = _poly_mutex_destroy;
      monitor_mutex_lock      = _poly_mutex_lock;
      monitor_mutex_trylock   = _poly_mutex_trylock;
      monitor_mutex_timedlock = _poly_mutex_timedlock;
      monitor_mutex_unlock    = _poly_mutex_unlock;
      monitor_cond_init       = _poly_cond_init;
      monitor_cond_destroy    = _poly_cond_destroy;
      monitor_cond_wait       = _poly_cond_wait;
      monitor_cond_timedwait  = _poly_cond_timedwait;
      monitor_cond_broadcast  = _poly_cond_broadcast;
      monitor_cond_signal     = _poly_cond_signal;
      monitor_obj_read        = _poly_obj_read;
      monitor_obj_write       = _poly_obj_write;
      monitor_call_begin      = _poly_call_begin;
      monitor_call_end        = _poly_call_end;
      monitor_inst_begin      = _poly_inst_begin;
      monitor_inst_end        = _poly_inst_end;
      break;

    case CLAP_FLAG_AUTO: 
      monitor_thread_start    = _auto_thread_start;
      monitor_thread_end      = _auto_thread_end;
      monitor_thread_create   = _auto_thread_create;
      monitor_thread_join     = _auto_thread_join;
      monitor_mutex_init      = _auto_mutex_init;
      monitor_mutex_destroy   = _auto_mutex_destroy;
      monitor_mutex_lock      = _auto_mutex_lock;
      monitor_mutex_trylock   = _auto_mutex_trylock;
      monitor_mutex_timedlock = _auto_mutex_timedlock;
      monitor_mutex_unlock    = _auto_mutex_unlock;
      monitor_cond_init       = _auto_cond_init;
      monitor_cond_destroy    = _auto_cond_destroy;
      monitor_cond_wait       = _auto_cond_wait;
      monitor_cond_timedwait  = _auto_cond_timedwait;
      monitor_cond_broadcast  = _auto_cond_broadcast;
      monitor_cond_signal     = _auto_cond_signal;
      monitor_obj_read        = _auto_obj_read;
      monitor_obj_write       = _auto_obj_write;
      monitor_call_begin      = _auto_call_begin;
      monitor_call_end        = _auto_call_end;
      monitor_inst_begin      = _auto_inst_begin;
      monitor_inst_end        = _auto_inst_end;
      break;

    default:
      monitor_thread_start    = _none_thread_start;
      monitor_thread_end      = _none_thread_end;
      monitor_thread_create   = _none_thread_create;
      monitor_thread_join     = _none_thread_join;
      monitor_mutex_init      = _none_mutex_init;
      monitor_mutex_destroy   = _none_mutex_destroy;
      monitor_mutex_lock      = _none_mutex_lock;
      monitor_mutex_trylock   = _none_mutex_trylock;
      monitor_mutex_timedlock = _none_mutex_timedlock;
      monitor_mutex_unlock    = _none_mutex_unlock;
      monitor_cond_init       = _none_cond_init;
      monitor_cond_destroy    = _none_cond_destroy;
      monitor_cond_wait       = _none_cond_wait;
      monitor_cond_timedwait  = _none_cond_timedwait;
      monitor_cond_broadcast  = _none_cond_broadcast;
      monitor_cond_signal     = _none_cond_signal;
      monitor_obj_read        = _none_obj_read;
      monitor_obj_write       = _none_obj_write;
      monitor_call_begin      = _none_call_begin;
      monitor_call_end        = _none_call_end;
      monitor_inst_begin      = _none_inst_begin;
      monitor_inst_end        = _none_inst_end;
    }

  }

  ~_ClapMonitor() {}

  void do_nothing() {}

};

class _ClapMonitor  _ClapMonitor_dummy;
//----------------------------------------------------------------------------
// End: set up the monitor function pointers upon initialization
//----------------------------------------------------------------------------

void clap_monitor_init()
{
  class _ClapMonitor  dummy;
}
