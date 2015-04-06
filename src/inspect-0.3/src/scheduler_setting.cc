#include "scheduler_setting.hh"
#include <cstdlib>

SchedulerSetting  setting;


SchedulerSetting::SchedulerSetting()
{
  standalone_flag = false;
  yices_flag=false;
  lazy_flag = false;
  stateful_flag = false;
  symmetry_flag = false;
  deadlock_only_flag = false;
  race_only_flag = false;
  report_race_flag = false;
  max_threads = 32;
  max_errors = 1;
  timeout_val = 150;

  //-------------------------------- chao -------------------------------------
  target_trace = false;
  lin_check = -1;   // -1 (disabled)  0 (serial)  1 (concurrent)
  replay_file = "";
  max_runs = -1;
  max_seconds = -1;
  max_pcb = -1;
  max_pset = -1;
  max_events = -1;   //unlimited
  max_spins = -1; //unlimited
  //-------------------------------- chao -------------------------------------

  #ifdef NLZ_FLAG
  memory_model=SC_MODEL;//the default value
  #endif

  #ifdef NLZ_NO_DPOR
  disable_dpor_flag=false; 
  #endif
  #ifdef NLZ_NO_SLEEP
  disable_sleepset_flag=false; 
  #endif 
  #ifdef NLZ_BOUND
  max_bound=-1;
  #endif
  target = "";
  target_argc = -1;
  target_argv = NULL;
  socket_file = string("/tmp/_") + string(getenv("USER")) + "_inspect_socket";
}


void set_stateful_flag()
{
  setting.stateful_flag = true;
}


void clear_stateful_flag()
{
  setting.stateful_flag = false;
}

void set_lazy_flag()
{
  setting.lazy_flag = true;
}

void clear_lazy_flag()
{
  setting.lazy_flag = false;
}

void set_standalone_flag()
{
  setting.standalone_flag = true;
}

void clear_standalone_flag()
{
  setting.standalone_flag = false;
}

void set_symmetry_flag()
{
  setting.symmetry_flag = true;
}

void clear_symmetry_flag()
{
  setting.symmetry_flag = false;
}

void set_max_pcb(int pcb)
{
  setting.max_pcb = pcb;
}
 
void set_max_pset(int pset)
{
  setting.max_pset = pset;
}
