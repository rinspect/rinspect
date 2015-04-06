#ifndef __CLAP_TYPEST_STATE_HH__
#define __CLAP_TYPEST_STATE_HH__

#include "clap_event.hh"
#include "clap_clockvector.hh"

#include <set>
#include <vector>
#include <cstring> 
#include <cassert>
#include <string> 
#include <map>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <set>

using namespace std;

typedef int MethodId;
typedef int ObjectId;
typedef int AutomatonState;
typedef set<AutomatonState> AutomatonStates;

class Automaton {
public:
	Automaton();
	~Automaton();
	void set_name(string n);
	void add_transition(AutomatonState s, MethodId m, AutomatonState t);
	string& get_name();

	AutomatonStates next_states(AutomatonStates s, MethodId m, bool error);
	void dump();

public:
	string name;
	map<pair<AutomatonState, MethodId>, AutomatonState> TR;
};

class ProgramState {
public:
	ProgramState();
	~ProgramState();

	bool isNextState(TypestEvent *e);
	bool isLocked(TypestEvent *e);
	bool updateAutomatons(TypestEvent *e);
	ProgramState* createState(TypestEvent *e);
	void merge_automatons(ProgramState *);






	void dump();

public:
	ClockVector clockvec;


	map<int, LockSet> locksets;
	map<ObjectId, AutomatonStates> states_of_automaton;
	map<string,map<int,map<int,int> > > automaton_states;//map<class name, map<obj id, map<current state, appear times> > >

	//  static map<ObjectId,Automaton> automaton_of_obj;
};

#endif //#ifndef __CLAP_TYPEST_STATE_HH__
