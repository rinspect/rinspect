/*
 * linchecker.hh
 *
 *  Created on: Dec 8, 2012
 *      Author: jack
 */
#include <iostream>
#include <map>
#include "inspect_event.hh"
#include "event_buffer.hh"
#include <sstream>

#ifndef LINCHECKER_HH_
#define LINCHECKER_HH_

using namespace std;

class quasi_state {
public:
//	quasi_state(){
//		selected_eid=0;
//		must_select=0;
//	}
//
//

	map<int,bool> enable_done;
	map<int,int> quasi_cost;
	map<int,bool> new_enable_done;
	int selected_eid;
	int must_select;

	string to_string() {
		stringstream ss;
		ss << "Enable_done: { ";
		for (map<int, bool>::iterator it = enable_done.begin();
				it != enable_done.end(); it++) {

			if (it->second) {
				ss << it->first << ", ";
			} else {
				ss << it->first << ":done, ";
			}

		}
		ss << "} ";

		ss << "  Quasi_cost: { ";
		for (map<int, int>::iterator it = quasi_cost.begin();
				it != quasi_cost.end(); it++) {

			ss << it->first << ":" << it->second << ", ";
		}
		ss << "} ";

		ss<<"  Select event: "<<selected_eid<<"  Must select: "<<must_select;

		return ss.str();
	}

};

class lin_checker {
public:
	lin_checker();

	virtual ~lin_checker();

	void add_to_trace(InspectEvent &event);

	void trace_dump_to_file(map<int, InspectEvent> &curr_trace);

	void trace_dump_to_file(map<int, InspectEvent> &curr_trace, char* path);

	bool quasi_trace_extension(map<int, InspectEvent> &curr_trace,string test_function);

	vector<map<int, int> > get_sub_quasi_traces(map<int, InspectEvent> &curr_trace,string function);

	map<int, InspectEvent> gen_trace_from_file(char* path_file);

	set<string> read_filters();

	vector<string> split_string(string input, string split_by);

	bool check_quasi_trace(map<int, InspectEvent> &curr_trace);

	void print_trace(map<int, InspectEvent> &curr_trace);

	void get_bt_info(map<int, InspectEvent> &curr_trace);

	void split_check_trace();

	bool check_trace_linearizability(map<int, InspectEvent> &curr_trace);

	void print_check_trace();

	void quasi_split_check_trace();

	bool linearizable_check_by_diff();

	void print_trace2(map<int, InspectEvent> &trace);

	void clear();

	vector<map<int, InspectEvent> > check_trace(map<int, InspectEvent> &trace);

	map<int, quasi_state> new_trace_from_state(quasi_state &from_state, int &index,
			map<int, set<int> > &new_enabled);
	bool quasi_check_two_traces_same(map<int, InspectEvent>& trace1, map<int, InspectEvent>& trace2);

	bool quasi_check_with_serial_traces(map<int, InspectEvent>& quazi_trace);

	string trim(string s);

	string remove_head_and_tail(string s);

	set<string> function_filter;

public:

	map<int, InspectEvent> concurr_trace;
//	map<int, InspectEvent> concurr_trace2;

	map<string, int> function_count;

	vector<map<int, InspectEvent> > traces;


};

/* namespace std */
#endif /* LINCHECKER_HH_ */
