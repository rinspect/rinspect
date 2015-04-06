#include <cassert>
#include <iostream>
#include "clap_typest_state.hh"
#include "clap_typest_predict.hh"
#include "clap_typest_trace.hh"
#include "clap_typest_check.hh"
#include <string>
#include <algorithm>

#include <functional>

//declarations of functions

using namespace std;

static ProgramState *program_state = new ProgramState(); //whole program state;
//
//static map<string, map<string, vector<string> > > future_events; //map<class, map<function,vector<function> > >

//static map<int, int>* object_map_repair;

void read_events_old();
void DFS_events();
void read_events();

string trim(string s);
string remove_head_and_tail(string s);
void typest_repair_handle_call(char* fname, int object_id);

bool thread_should_spin_old(TypestEvent* e); //whether a thread should spin before a event
bool whether_spin(TypestEvent* e);
bool should_abort(); //should the program abort: all the threads are hanging
void update_info(TypestEvent* e); //update the index of each step

ProgramState * update_program_state(ProgramState * ps, TypestEvent* e); //update a program state

TypestEvent* next_event_of_thread(int tid); //return next event of a thread
void safe_active_threads();
void safe_attemp_times();
void safe_object_map_repair();
void safe_future_events();
//void check_map_int_TypestEvent(map<int, TypestEvent*>* map);
//void check_map_int_int(map<int, int>* map);
//void check_map_int_bool(map<int, bool>* map);
