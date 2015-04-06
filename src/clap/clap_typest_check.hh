#ifndef __CLAP_TYPEST_CHECKER_HH__
#define __CLAP_TYPEST_CHECKER_HH__

#include "clap_uniquetid.hh"
#include "clap_typest.hh"

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>


bool typest_check_handle_call(char* fname, int object_id);
void add_transaction(string obj_name, int from_state, string event, int to_state);
int check(string obj_name, int from_state, string event);

map<string, map<int, map<string, int> > > get_state_potential_events();


vector<string> split_string(string input);
vector<string> split_string(string input,string split_by);
string current_path();
void compute_PE();
map<string, int> DFS(string class_name, int state);
void input_automaton(string automaton_path);
vector<string> searchDir(char * dir);
vector<string> read_file(string file);
pair<string, string> get_class_and_function(string event,char* fname);
map<string, map<int, map<string, int> > > return_automaton();

static map<int, int> object_map; //map<map <object id, current state>

#endif //#ifndef __CLAP_TYPEST_CHECKER_HH__
