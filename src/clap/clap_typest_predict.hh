#ifndef __CLAP_TYPEST_PREDICT_HH__
#define __CLAP_TYPEST_PREDICT_HH__

#include "clap_event.hh"
#include "clap_typest_state.hh"

#include <cstring> 
#include <cassert>
#include <string> 
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <queue>



class TypestEventQueue {
public:
  TypestEventQueue();
  ~TypestEventQueue();
  void enqueue(TypestEvent* ev);

  bool constructLevel();
  bool isLevelComplete(TypestEvent *e);
  void removeUselessEvents();

  void dump();

public: 
  map<int,map<int,TypestEvent*> > events_by_thread;
  vector<TypestEvent*> events;       // Q
  set<ProgramState*> CurrLevel;
  set<ProgramState*> NextLevel;
  bool started;
};

#endif // #ifndef __CLAP_TYPEST_PREDICT_HH__
