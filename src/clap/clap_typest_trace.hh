#ifndef __CLAP_TYPEST_TRACE_HH__
#define __CLAP_TYPEST_TRACE_HH__

#include "clap_event.hh"

#include <map>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>

using namespace std;

class TypestTrace {
public:
	TypestTrace();
	~TypestTrace();

	void add_event(TypestEventType typ, int var, char* fname = 0);

//  void add_event_to_trace(TypestEventType typ, int var, char* fname = 0);

	void update_lockset(TypestEvent* ev);
	void update_clockvector(TypestEvent* ev);

	void predict_handle_call(TypestEvent* ev);

	void dump();
	void print_statistics();

public:
	vector<TypestEvent*> events;

	// temporary storage; used in 'update_lockset()'
	map<int, LockSet>* curr_locksets;
	void safe_curr_locksets();

	map<int, TypestEvent*>* curr_events; //any type of event
	void safe_curr_events();

	map<int, int>* OBJ_CALL_index; //map<thread id, number of OBJ_CALL>
	void safe_OBJ_CALL_index();

	map<int, int>* curr_obj_call; //only obj_call, thread_id, eid
	void safe_curr_obj_call();

	// temporary storage; used in 'update_clockvector()'
	map<int, TypestEvent*>* child_to_thread_create_ev;
	void safe_child_to_thread_create_ev();

	map<int, TypestEvent*>* child_to_thread_end_ev;
	void safe_child_to_thread_end_ev();

	map<int, TypestEvent*>* signals; //map<condition id, event>
	void safe_signals();

	map<int, TypestEvent*>* broadcasts; //map<condition id, event>
	void safe_broadcasts();

};

#endif
