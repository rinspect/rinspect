#ifndef __INSPECT_PROGRAM_STATE_HH__
#define __INSPECT_PROGRAM_STATE_HH__

#include <vector>
#include <ext/hash_set>
#include <string>

#include "transition_set.hh"
#include "scheduler_object_table.hh"
#include "inspect_event.hh"


using std::vector;
using __gnu_cxx::hash_set;
using __gnu_cxx::hash;



class ProgramState
{
public:
  ProgramState();
  ProgramState(ProgramState& state);
  
  ProgramState & operator=(ProgramState &another);
  bool operator==(ProgramState &another);
  bool operator!=(ProgramState &another);

  size_t hash_number();
  
  void update_enabled_set(InspectEvent &event);
  void update_disabled_set(InspectEvent &event);
  
  bool alive(int tid);
  bool check_race();  
  void add_transition(InspectEvent &event);
  
  bool is_enabled(InspectEvent &event);
  bool is_disabled(InspectEvent &event);

  void execute_transition(InspectEvent &event);

  string toString();
  
public:
  TransitionSet  enabled;
  TransitionSet  disabled;

  SchedulerMutexIndex mutexes;
  SchedulerRwlockIndex rwlocks;
};




namespace __gnu_cxx
{
  template<>
  struct hash<ProgramState*>
  {
    size_t operator()(ProgramState *st) const {
      return st->hash_number();
    }
  };  
};


struct EqProgState
{
  bool operator()(ProgramState * st1, ProgramState * st2) const
  {
    return (*st1 == *st2);
  }
};




class ProgramStateTable
{
public:
  //typedef hash_set<ProgramState*, hash<ProgramState*>, EqProgState>::iterator iterator;
  typedef vector<ProgramState*>::iterator  iterator;

public:  
  ProgramStateTable();
  ~ProgramStateTable();

  void insert(ProgramState * state);
  void remove(ProgramState * state);
  bool has_member(ProgramState *);
  
  size_t  size(){ return states.size(); } 

  string toString();
public:
  //hash_set<ProgramState*, hash<ProgramState*>, EqProgState>  states;
  vector<ProgramState*>  states;
};






#endif

