#ifndef __INSPECT_RELATION_GRAPH_HH__
#define __INSPECT_RELATION_GRAPH_HH__

#include <ext/hash_map>
#include <vector>
#include <string>
#include "inspect_event.hh"

using std::vector;
using std::string;
using __gnu_cxx::hash_map;


class EventNode
{
public:
  EventNode();
  EventNode(InspectEvent &ev);
  inline void set_visited_flag()   { visited_flag = true;  }
  inline void clear_visited_flag() { visited_flag = false; } 

  bool has_prev(InspectEvent &event);
  bool has_next(InspectEvent &event);

  void add_prev(EventNode * nd);
  void add_next(EventNode * nd);

public:
  InspectEvent event;
  bool visited_flag;

  vector<EventNode *> prevs;
  vector<EventNode *> nexts;
};


// this class stores the events of one thread
//
class EventNodeList
{
public:
  typedef vector<EventNode*>::iterator iterator;

public:
  EventNodeList(int tid); 
  ~EventNodeList();

  bool has_node(InspectEvent &event);
  EventNode * get_node(InspectEvent &event);

  void add(InspectEvent &event);
  void remove(InspectEvent &event);
  
  void clear_visited_flag();

  void get_following_events(InspectEvent &event, vector<InspectEvent> &events);
private:  
  EventNodeList() { }

public:
  int thread_id;
  vector<EventNode *> nodes;
};



class EventGraph
{
public:
  typedef vector<EventNodeList*>::iterator iterator;

public:
  EventGraph();
  ~EventGraph();
  
  void add_node(InspectEvent &e);

  void add_edge(InspectEvent &e1, InspectEvent &e2);

  EventNode * get_node(InspectEvent &event);

  string toString();

  void clear_visited_flag();
  
  void get_following_events(InspectEvent &event, vector<InspectEvent> &events);
  
public:
  vector<EventNodeList*> threads;
};


#endif


