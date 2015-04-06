#include "transition_set.hh"
#include <cassert>
#include <algorithm>
#include "yices_path_computer_singleton.hh"

using namespace std;
using namespace __gnu_cxx;

TransitionSet::TransitionSet()
{
  events.clear();
}


TransitionSet::TransitionSet(TransitionSet & another)
{
  events = another.events;
}


TransitionSet::~TransitionSet()
{ }


TransitionSet & TransitionSet::operator= (TransitionSet & another)
{
  events = another.events;
  return  *this;
}


bool TransitionSet::has_member(InspectEvent &event)
{
  int tid;
  InspectEventMapIterator it;

  tid = event.thread_id;
  it = events.find(tid);

  if (it == events.end()) return false;

#ifdef NLZ_EVEC
  for(Iterator_ev it_ev=it->second.begin();it_ev!=it->second.end();it_ev++)
      if ( *it_ev == event) return true;
  return false;
#else
  return it->second == event;
#endif
}

#ifdef NLZ_EVEC
bool TransitionSet::has_write_but_read(int tid){
  InspectEventMapIterator it = events.find(tid);
  if (it == events.end()) return false;
  bool write_found = false;
  for(Iterator_ev it_ev=it->second.begin();it_ev!=it->second.end();it_ev++){
      if (it_ev->type == OBJ_READ) return false;
      if (it_ev->type == OBJ_WRITE) {write_found = true;}
  }
  return write_found;
}

bool TransitionSet::has_read(int tid){
  InspectEventMapIterator it = events.find(tid);
  if (it == events.end()) return false;
  for(Iterator_ev it_ev=it->second.begin();it_ev!=it->second.end();it_ev++){
      if (it_ev->type == OBJ_READ) return true;
  }
  return false;
}

#endif


bool TransitionSet::has_member(int tid)
{
  iterator it;
  it = events.find(tid);
  return (it != events.end());
}

#ifdef NLZ_EVEC
void TransitionSet::remove(int tid)
{
  if (! has_member(tid) ) return;

 InspectEventMapIterator it = events.find(tid);
  for(Iterator_ev it_ev=it->second.begin();it_ev!=it->second.end();it_ev++){
    
       it->second.erase(it_ev);
	  if (it->second.empty()) { events.erase(it); }
	
      }
  }
#else
void TransitionSet::remove(int tid)
{
  InspectEventMapIterator it;
  it = events.find(tid);
  if (it != events.end()) events.erase(it);
}
#endif

void TransitionSet::remove(InspectEvent &event)
{
  if (! has_member(event) ) return;

#ifdef NLZ_EVEC
  InspectEventMapIterator it = events.find(event.thread_id);
  for(Iterator_ev it_ev=it->second.begin();it_ev!=it->second.end();it_ev++){
      if ( *it_ev == event){
	  it->second.erase(it_ev);
	  if (it->second.empty()) { events.erase(it); }
	  return;
      }
  }
#else
  remove(event.thread_id);
#endif
}


void TransitionSet::insert(InspectEvent &event)
{
  InspectEventMapIterator it;

  //it = events.find(event.thread_id);

//   if (it != events.end() )
//     assert(it->second.invalid() );

#ifdef NLZ_EVEC
  std::vector<InspectEvent>& ev_vec = events[event.thread_id];
  std::vector<InspectEvent>::iterator vit;
  for (vit=ev_vec.begin(); vit != ev_vec.end(); vit++){
      if (*vit == event) break;
      else{
      }
  }

  if (vit == ev_vec.end()){

      ev_vec.push_back(event);
  }else{
      *vit = event;//TODO: CHECK why do i reset event to *vit?? some future set will be changed
  }
#else
  events[event.thread_id] = event;
#endif
}



#ifdef NLZ_EVEC
std::vector<InspectEvent>& TransitionSet::get_transition_vec(int tid){
    iterator it = events.find(tid);
    assert (it != events.end() && "empty transtion vector");
    return it->second;
}
#endif


#ifdef NLZ_EVEC
InspectEvent& TransitionSet::get_front_transition(int tid)
{
  InspectEventMapIterator it;
  it = events.find(tid);
  if (it == events.end()) return InspectEvent::dummyEvent;
  if (it->second.empty()){
      std::cout<<"!!!!!!!!!!!!!!!!!!!!!!! code is not good enough in transition_set.cc"<<std::endl;
      return InspectEvent::dummyEvent;
  }else{
      return it->second.front();
  }
}
#else
InspectEvent& TransitionSet::get_transition(int tid)
{
  InspectEventMapIterator it;
  it = events.find(tid);
  if (it == events.end()) return InspectEvent::dummyEvent;
  return it->second;
}
#endif


#ifdef NLZ_EVEC
InspectEvent& TransitionSet::get_front_transition()
{
  InspectEventMapIterator it;
  if (events.empty()) return InspectEvent::dummyEvent;
  it = events.begin();
  if (it->second.empty()){
      std::cout<<"!!!!!!!!!!!!!!!!!!!!!!! code is not good enough in transition_set.cc"<<std::endl;
      return InspectEvent::dummyEvent;
  }else{
      return it->second.front();
  }
}
#else
InspectEvent& TransitionSet::get_transition()
{
  InspectEventMapIterator it;
  if (events.empty()) return InspectEvent::dummyEvent;
  it = events.begin();
  return it->second;
}
#endif


void TransitionSet::remove_depedent_events(InspectEvent &event)
{
  iterator  it;
  InspectEvent tmpev;
  vector<InspectEvent>  tmp_vec;
  vector<InspectEvent>::iterator  vit;

  tmp_vec.clear();

#ifdef NLZ_EVEC
  for (it = events.begin(); it != events.end(); it++){
    for(Iterator_ev it_ev=it->second.begin();it_ev!=it->second.end();it_ev++){
	if (event.dependent(*it_ev)){
	    tmp_vec.push_back(event);
	}
    }
  }

  for (vit = tmp_vec.begin(); vit != tmp_vec.end(); vit++){
      tmpev = *vit;
      vector<InspectEvent>& ev_vec = events[tmpev.thread_id]; 
      for(Iterator_ev it_ev=ev_vec.begin();it_ev!=ev_vec.end();it_ev++){
	  if (*it_ev==tmpev){
	      it_ev->clear();
	  }
      }
  }
#else
  for (it = events.begin(); it != events.end(); it++){
      if (event.dependent(it->second)){//no *it->second
	  tmp_vec.push_back(event);
      }
  }

  for (vit = tmp_vec.begin(); vit != tmp_vec.end(); vit++){
    tmpev = *vit;
    events[tmpev.thread_id].clear();
  }
#endif
}



#ifdef NLZ_EVEC // can return more than one race_event
std::vector<InspectEvent> TransitionSet::get_race_events(InspectEvent& event){
  iterator it;
  InspectEvent tmpev;
  std::vector<InspectEvent> race_events;
  for (it = events.begin(); it != events.end(); it++){
    for(Iterator_ev it_ev=it->second.begin(); it_ev!=it->second.end(); it_ev++){    
       tmpev = *it_ev;
       if (tmpev.thread_id == event.thread_id) continue;	       
       if (tmpev.type != OBJ_WRITE && event.type != OBJ_WRITE) continue;
       if (tmpev.obj_id == event.obj_id ) race_events.push_back(tmpev);
    } 
  }
  return race_events;
}

#else  // define get_race_event
InspectEvent TransitionSet::get_race_event(InspectEvent &event)
{
  iterator it;
  InspectEvent tmpev;

#ifdef NLZ_EVEC
  for (it = events.begin(); it != events.end(); it++){
    for(Iterator_ev it_ev=it->second.begin(); it_ev!=it->second.end(); it_ev++){    
       tmpev = *it_ev;
       if (tmpev.thread_id == event.thread_id) continue;	       
       if (tmpev.type != OBJ_WRITE && event.type != OBJ_WRITE) continue;
       if (tmpev.obj_id == event.obj_id ) return tmpev;  // TODO: here may be more than one race_event
    } 
  }
#else
  for (it = events.begin(); it != events.end(); it++){
      tmpev = it->second;
      if (tmpev.thread_id == event.thread_id) continue;	       
      if (tmpev.type != OBJ_WRITE && event.type != OBJ_WRITE) continue;
      if (tmpev.obj_id == event.obj_id ) return tmpev;
  }
#endif

  return InspectEvent::dummyEvent;  
}
#endif





bool TransitionSet::has_rwlock_rdlock(int rwlock_id)
{
  iterator it;
#ifdef NLZ_EVEC
  for (it = events.begin(); it != events.end(); it++){
    for(Iterator_ev it_ev=it->second.begin();it_ev!=it->second.end();it_ev++){ 
	if((*it_ev).type == RWLOCK_RDLOCK && (*it_ev).rwlock_id == rwlock_id) 
	    return true;
    }
  }
#else
  for (it = events.begin(); it != events.end(); it++){
      if(it->second.type == RWLOCK_RDLOCK && it->second.rwlock_id == rwlock_id) 
	  return true;
  }
#endif
  return false;
}


bool TransitionSet::has_rwlock_wrlock(int rwlock_id)
{
  iterator it;
#ifdef NLZ_EVEC
  for (it = events.begin(); it != events.end(); it++){
    for(Iterator_ev it_ev=it->second.begin();it_ev!=it->second.end();it_ev++){ 
	if((*it_ev).type == RWLOCK_WRLOCK && (*it_ev).rwlock_id == rwlock_id) 
	    return true;
    }
  }
#else
  for (it = events.begin(); it != events.end(); it++){
      if(it->second.type == RWLOCK_WRLOCK && it->second.rwlock_id == rwlock_id) 
	  return true;
  }
#endif
  return false;
}


bool TransitionSet::operator==(TransitionSet &another)
{
  iterator it;
  int tid;
  InspectEvent e1, e2;
  if (this->size() != another.size()) return false;

#ifdef NLZ_EVEC
  for(it = events.begin(); it != events.end(); it++){  // slightly different from scalar implemation
      tid = it->first;
      vector<InspectEvent> ev_vec1 = it->second;
      InspectEventMapIterator it_another = another.events.find(tid);
      if (it_another == another.events.end()) return false;
      vector<InspectEvent> ev_vec2 = it_another->second;
      if (ev_vec1.size() != ev_vec2.size()) return false;
      for (std::size_t i=0; i< ev_vec1.size(); ++i){
	  if (ev_vec1[i]!=ev_vec2[i]) return false;  // TODO: what if two vectors are just in different order
      }
  }
#else
  for(it = events.begin(); it != events.end(); it++){
      tid = it->first;
      e1 = it->second;
      e2 = another.get_transition(tid);
      if (e1 != e2) return false;
  }
#endif
  
  return true;
}

bool TransitionSet::operator!=(TransitionSet &another)
{
  return !(*this == another);
}


#ifdef NLZ_EVEC
std::string TransitionSet::toString(){
  std::stringstream ss;
  for (iterator it = begin(); it != end(); it++)
      for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); vit++)
	  ss << "            " << vit->toString() << "\n";
  return ss.str();
}
#endif
