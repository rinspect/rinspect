#ifndef __INSPECT_SCHEDULER__SETTING_HH__
#define __INSPECT_SCHEDULER__SETTING_HH__

#include "naling.def"
#ifdef NLZ_FLAG
#include "memory_model_enum.hh"
#endif

#include <string>

using std::string;

class SchedulerSetting
{
public:
  SchedulerSetting();

public:
  bool standalone_flag;
  bool yices_flag;
  bool lazy_flag;
  bool stateful_flag;
  bool symmetry_flag;

  bool deadlock_only_flag;
  bool race_only_flag;
  bool report_race_flag;

  //-------------------------------- chao -------------------------------------
  bool target_trace;
  int  lin_check;
  string replay_file;
  int  max_pcb;
  int  max_pset;
  int  max_runs;
  int  max_seconds;
  int  max_events;        // max number of events allowed in each run
  int  max_spins;         // max times allowed to spin on the same event
  //-------------------------------- chao -------------------------------------

#ifdef NLZ_FLAG
  MemoryModel memory_model;
#endif
#ifdef NLZ_NO_DPOR
    bool disable_dpor_flag;
#endif
#ifdef NLZ_NO_SLEEPSET
    bool disable_sleepset_flag;
#endif
#ifdef NLZ_BBOUND
    int max_bound;
#endif
    
  int  max_threads;
  int  max_errors;
  int  timeout_val;
  string  socket_file;

  string  target;
  int target_argc;
  char ** target_argv; 
};

extern SchedulerSetting  setting;

void set_stateful_flag();
void clear_stateful_flag();

void set_lazy_flag();
void clear_lazy_flag();

void set_standalone_flag();
void clear_standalone_flag();

void set_symmetry_flag();
void clear_symmetry_flag();

void set_max_pcb(int pcb);
void set_max_pset(int pset);

#endif


