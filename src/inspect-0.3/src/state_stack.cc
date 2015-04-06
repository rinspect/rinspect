#include "state_stack.hh"
#include <sstream>
#include <iomanip>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
//   the implementation of StateStack
//
//////////////////////////////////////////////////////////////////////////////


StateStack::StateStack()
  : stack_top(NULL)
{
  stack.clear();
}


StateStack::~StateStack()
{
  vector<State*>::iterator it;
  for (it = stack.begin(); it != stack.end(); it++)
    delete *it;
  stack.clear();
}


void StateStack::push(State * state)
{
  assert(state != NULL);
  state->prev = stack_top;
  state->next = NULL;
  if (stack_top != NULL)
    stack_top->next = state;

  stack.push_back(state);
  stack_top = state;
}


void StateStack::pop()
{
  if (stack_top != NULL){
    stack_top = stack_top->prev;
    stack.pop_back();
  }
}


State * StateStack::operator[](int idx)
{
  assert( idx >= 0 && idx < (int)stack.size());
  return stack[idx];
}


State * StateStack::get_mutex_lock_state(State * cur_state, InspectEvent &event)
{
  State * state;
  bool  found = false;
  
  state = cur_state;
  while (state != NULL  && !found){
    if (state->sel_event.type == MUTEX_LOCK &&
	state->sel_event.thread_id == event.thread_id &&
	state->sel_event.mutex_id == event.mutex_id){
      found = true;
      break;
    }
    state = state->prev;
  }
  
  assert(found);
  return state;
}



string  StateStack::toString()
{
  stringstream ss;
  
  int i, size;
  size = stack.size();
  for (i = 0; i < size; i++) {
    ss << setw(3) << i ;
    ss << " " << stack[i]->toString() << endl;
  }
  return ss.str();
}


bool StateStack::has_backtrack_points()
{
  State * state;
  state = stack_top;
  while (state != NULL){
    if (!state->backtrack.empty()) return true;
    state = state->prev;
  }
  return false;
}


string StateStack::toString2()
{
  stringstream ss;
  
  int i, size;
  size = stack.size();
  for (i = 0; i < size; i++) {
    ss << setw(3) << left << i; 
    ss << " " << stack[i]->toSimpleString() << endl;
  }
  return ss.str();
}


string StateStack::toString3()
{
  stringstream ss;
  State * state;

  int i, size;
  size = stack.size();
  for (i = 0; i < size; i++){
    state = stack[i];
    //    if (state->sel_event.type == OBJ_READ ||
    //        state->sel_event.type == OBJ_WRITE) continue;
    ss << state->sel_event.toString() << endl;
  }

  //ss << stack_top->toString() << endl;
  return ss.str();
}



string StateStack::toString4()
{
  stringstream ss;
  State * state;

  int i, size;
  size = stack.size();
  for (i = 0; i < size; i++){
    state = stack[i];
    if (state->backtrack.empty()) continue;
    ss << state->toString() << endl;
  }

//   ss << stack_top->toString() << endl;
  return ss.str();
}


