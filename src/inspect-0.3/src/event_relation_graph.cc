#include "event_relation_graph.hh"
#include <deque> 

using namespace std;


EventNode::EventNode()
  : visited_flag(false)
{ 
  prevs.clear();
  nexts.clear();
}


EventNode::EventNode(InspectEvent &ev)
  : event(ev), 
    visited_flag(false)
{ 
  prevs.clear();
  nexts.clear();
}


bool EventNode::has_prev(InspectEvent &event)
{
  vector<EventNode*>::iterator it;
  EventNode * node;

  for (it = prevs.begin(); it != prevs.end(); it++){
    node = *it;
    if (node->event == event) return true;
  }

  return false;
}


bool EventNode::has_next(InspectEvent &event)
{
  vector<EventNode*>::iterator it;
  EventNode * node;

  for (it = nexts.begin(); it != nexts.end(); it++){
    node = *it;
    if (node->event == event) return true;
  }

  return false;
}


void EventNode::add_prev(EventNode * nd)
{
  assert(nd != NULL);
  if ( has_prev(nd->event) ) return;  
  prevs.push_back(nd);
  
}


void EventNode::add_next(EventNode *nd)
{
  assert(nd != NULL);
  if ( has_next(nd->event) ) return;
  nexts.push_back(nd);
}


///////////////////////////////////////////////////////////////////////////////
//
//  EventNodeList
//
///////////////////////////////////////////////////////////////////////////////


EventNodeList::EventNodeList(int tid)
  : thread_id(tid)
{  }


EventNodeList::~EventNodeList()
{
  EventNode * node;
  iterator it;

  for (it = nodes.begin(); it != nodes.end(); it++){
    node = *it;
    delete node;
  }
}


bool EventNodeList::has_node(InspectEvent &event)
{
  iterator it;
  EventNode * node;
  
  for (it = nodes.begin(); it != nodes.end(); it++){
    node = *it;
    if (node->event == event) return true;
  }
  return false;
}


EventNode * EventNodeList::get_node(InspectEvent &event)
{
  iterator it;
  EventNode * node;
  
  for (it = nodes.begin(); it != nodes.end(); it++){
    node = *it;
    if (node->event == event) return node;
  }
  
  node = new EventNode(event);
  nodes.push_back(node);
  return node;
}


void EventNodeList::add(InspectEvent &event)
{
  iterator it;
  EventNode * node;
  
  if ( has_node(event) )  return;
  node = new EventNode(event);
  nodes.push_back(node);
}


void EventNodeList::remove(InspectEvent &event)
{
  iterator it;
  EventNode * node;

  for (it = nodes.begin(); it != nodes.end(); it++){
    node = *it;
    if (node->event == event){
      delete node;
      nodes.erase(it);
      return;
    }
  }  
}


void EventNodeList::clear_visited_flag()
{
  iterator it;
  EventNode * node;
  
  for (it = nodes.begin(); it != nodes.end(); it++){
    node = *it;
    node->clear_visited_flag();
  }
}


void EventNodeList::get_following_events(InspectEvent &event, 
					 vector<InspectEvent> &events)
{
  assert(events.size() == 0);

  if (event.type == COND_WAIT) return;

  assert(this->has_node(event));
  
  EventNode *node, *node2;
  deque<EventNode*> queue;
  vector<EventNode*>::iterator  vit;
  
  node = this->get_node(event);
  queue.push_back(node);

  while(! queue.empty()){
    node = queue.front();
    queue.pop_front();
    
    assert(node != NULL);
    for (vit = node->nexts.begin(); vit != node->nexts.end(); vit++){
      node2 = *vit;
      if (node2->visited_flag) continue;
      events.push_back(node2->event);
      queue.push_back(node2);
    }
    
    node->set_visited_flag();
  }
  
}


///////////////////////////////////////////////////////////////////////////////
//
//  the implementation of EventGraph
//
///////////////////////////////////////////////////////////////////////////////


EventGraph::EventGraph()
{  
  threads.clear();
}


EventGraph::~EventGraph()
{
  iterator it;
  EventNodeList * node_list;

  for (it = threads.begin(); it != threads.end(); it++){
    node_list = *it;
    delete node_list;
  }
  threads.clear();
}


void  EventGraph::add_node(InspectEvent &e)
{
  EventNodeList * node_list = NULL;

  if (threads.size() <= e.thread_id){
    threads.resize(e.thread_id + 1, NULL);
    node_list = new EventNodeList(e.thread_id);
    threads[e.thread_id] = node_list;
  }
  
  node_list = threads[e.thread_id];
  if (node_list == NULL){
    node_list = new EventNodeList(e.thread_id);
    threads[e.thread_id] = node_list;
  }

  assert(node_list != NULL);  
  node_list->add(e);
}



EventNode * EventGraph::get_node(InspectEvent &event)
{
  EventNodeList * node_list = NULL;
  EventNode * node = NULL;

  assert(threads.size() > event.thread_id);

  node_list = threads[event.thread_id];
  assert(node_list != NULL);
  
  node = node_list->get_node(event);
  assert(node != NULL);
  return node;
}


void EventGraph::add_edge(InspectEvent &e1, InspectEvent &e2)
{
  EventNodeList * node_list = NULL;
  EventNode * node1 = NULL, * node2 = NULL;

  assert(e1.thread_id == e2.thread_id);
  
  node_list = threads[e1.thread_id]; 
  assert(node_list != NULL);
  
  node1 = node_list->get_node(e1);
  node2 = node_list->get_node(e2);

  node1->add_next(node2);
  node2->add_prev(node1);
}


void EventGraph::clear_visited_flag()
{
  EventNodeList * node_list;
  iterator it;

  for (it = threads.begin(); it != threads.end(); it++){
    node_list = *it;
    if (node_list == NULL) continue; 
    
    assert(node_list != NULL);
    node_list->clear_visited_flag();
  }
  
}


void EventGraph::get_following_events(InspectEvent &event, vector<InspectEvent> &events)
{
  EventNodeList * node_list = NULL;

  this->clear_visited_flag();
  
  node_list = threads[event.thread_id];
  if (node_list == NULL) return;

  node_list->get_following_events(event, events);
}




