#ifndef __STATE_STACK_H__
#define __STATE_STACK_H__

#include "state.hh"
#include <vector>

using std::vector;

class StateStack
{
public:
  StateStack();
  ~StateStack();
  
  void push(State * state);
  void pop();
  inline State * top(){ return stack_top; } 
  inline bool empty() { return stack.empty(); }  
  inline int  depth() { return stack.size();  } 
  
  bool has_backtrack_points();

  State * operator[](int idx); 
  string toString();
  string toString2();
  string toString3();
  string toString4();

  State * get_mutex_lock_state(State * cur_state, InspectEvent &event);
  
public:  
  State * stack_top;
  vector<State*>  stack;
};

#endif

