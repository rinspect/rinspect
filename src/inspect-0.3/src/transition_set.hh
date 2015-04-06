
#ifndef __TRANSITION_SET_H__
#define __TRANSITION_SET_H__


#include <vector>
#include <ext/hash_map>
#include <functional>
#include "inspect_event.hh"

using std::vector;
using namespace __gnu_cxx; //::hash_map;
using std::unary_function;

#ifdef NLZ_EVEC
typedef hash_map<int, std::vector<InspectEvent>, hash<int> >  InspectEventMap;
#else
typedef hash_map<int, InspectEvent, hash<int> >  InspectEventMap;
#endif
typedef InspectEventMap::iterator  InspectEventMapIterator;

/**
 *  the state of 
 *
 */

class TransitionSet
{
public:
    typedef InspectEventMapIterator  iterator;
#ifdef NLZ_EVEC
    typedef std::vector<InspectEvent>::iterator Iterator_ev;    // iterator of event vector
    bool has_write_but_read(int tid);
    bool has_read(int tid);
#endif
public:
  TransitionSet();
  TransitionSet(TransitionSet&);
  ~TransitionSet();
  
  TransitionSet& operator = (TransitionSet&);
  
  inline bool empty() { return events.size() == 0; }   
  inline int size()   {  return events.size(); } 

  bool has_member(InspectEvent &event); 
  bool has_member(int tid);
  void remove(int tid);
  void remove(InspectEvent &event);
  void insert(InspectEvent &event);
  void remove_depedent_events(InspectEvent &event);
  
#ifdef NLZ_EVEC
    InspectEvent& get_front_transition(int tid);
    InspectEvent& get_front_transition();
    std::vector<InspectEvent>& get_transition_vec(int tid);
#else
    InspectEvent& get_transition(int tid);
    InspectEvent& get_transition();
#endif
  iterator begin() { return events.begin(); }
  iterator end()   { return events.end(); }
 
  InspectEvent get_race_event(InspectEvent &event);
#ifdef NLZ_EVEC
    std::vector<InspectEvent> get_race_events(InspectEvent& event);
    std::string toString();
#endif
    
  bool has_rwlock_rdlock(int rwlock_id);
  bool has_rwlock_wrlock(int rwlock_id);
  
  bool operator ==(TransitionSet &another);
  bool operator !=(TransitionSet &another);

public:
#ifdef NLZ_EVEC
    hash_map<int, std::vector<InspectEvent>, hash<int> > events;
#else
    hash_map<int, InspectEvent, hash<int> > events;
#endif
};



#endif


