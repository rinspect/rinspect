#ifndef __CLAP_EVENT_HH__
#define __CLAP_EVENT_HH__

#include "clap_clockvector.hh"
#include "clap_lockset.hh"

#include <cstring> 
#include <cassert>
#include <string> 
#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

enum EventCategory 
{  
  EC_MUTEX,    EC_COND,     EC_RWLOCK,
  EC_OBJECT,   EC_THREAD,   EC_SEMAPHORE,
  EC_SYMMETRY, EC_GLOBAL,   EC_LOCAL,   
  EC_CAS,      EC_PROPERTY, 
  EC_ERROR = 9999
};				


#define DEF_EVENT_CODE(EV, STR, EV_PERM, CAT)   EV,
enum EventType{
  #include "clap_event.def"
  UNKNOWN
};
#undef DEF_EVENT_CODE

EventCategory  get_event_category(EventType  et);
string  event_type_to_string(EventType et);
EventType string_to_event_type(string str);


class Event
{
public:
  Event(EventType typ, int tid, int var, int loc=-1);

  string toXML();
  string toJet();
  string toString();

  void dump() { cout << toString() << endl; }

public:
  EventType type;     
  int thread_id;      
  int eid;

  union{
    int child_id;    
    int mutex_id;    
    int cond_id;     
    int obj_id;  
  };

  int location_id;

  ClockVector clockvec;

  LockSet  lockset;
  VarSet   varset;
  CondSet  condset;

  string thread_function_name;//the function name of the thread(each thread_function has a CFG for the thread)
  string method_name;
  string class_name;
  int index_of_OBJ_CALL;
  map<int,int> prev_events;

  string prev_to_string();

  Event* prev;   // previous event from same thread

  static int count;
};


typedef Event     PolyEvent;
typedef EventType PolyEventType;

typedef Event     TypestEvent;
typedef EventType TypestEventType;

#endif



