/*
 * linchecker.cc
 *
 *  Created on: Dec 8, 2012
 *      Author: jack
 */

#include "lin_checker.hh"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int run_count = 0;
int trace_count = 0;
int quasi_count = 0;

int total_check = 0;
int total_lin = 0;
int total_not_lin = 0;

int verbose = 0;

bool quasi_flag = false;

int quasi;
void set_quasi(int number) {
	quasi = number;
}

lin_checker::lin_checker() {
	// TODO Auto-generated constructor stub

	read_filters();

	if (verbose > 0)
		cout << "create checker" << endl;

}

lin_checker::~lin_checker() {
	// TODO Auto-generated destructor stub
	if (verbose > 0)
		cout << "destroy checker" << endl;
}
//pthread_mutex_t add_lock = PTHREAD_MUTEX_INITIALIZER;
void lin_checker::add_to_trace(InspectEvent &event) {

	if (function_filter.find(event.method_name) == function_filter.end()) {
//		cout << event.method_name << "  IGNORED" << endl;
		return;
	}

//	cout << event.method_name << "  ADDED" << endl;

	int eid = concurr_trace.size() + 1;
//	event.eid = eid;
	concurr_trace[eid] = event;

//	cout<<"concurr_trace.size() = "<<concurr_trace.size()<<endl;

}

void lin_checker::get_bt_info(map<int, InspectEvent> &curr_trace) {

	//map<type of function call, map<eid, quasi distance left>>;
	map<string, map<int, int> > quasi_backtrack;

	function_count.clear();

	int index = curr_trace.size();
//	for (map<int, InspectEvent>::iterator it = curr_trace.begin();
//			it != curr_trace.end(); it++) {
//
//	}

	for (map<int, InspectEvent>::reverse_iterator it = curr_trace.rbegin();
			it != curr_trace.rend(); it++) {

		it->second.eid = index;
		it->second.quasi_cost.clear();
		it->second.enable_done.clear();
		index--;

		if (it->second.type == OBJ_RESP)
			continue; //only consider obj_call

		string call = it->second.method_name;

		function_count[call]++;

//		cout<<function_count[call]<<endl;

		int eid = it->second.eid;

		//update the temp information
		//step 1: add the current eid into quasi_backtrack
		quasi_backtrack[call][eid] = quasi;

		//add the enable_done information

		if (quasi_backtrack.find(call) != quasi_backtrack.end()) {
			for (map<int, int>::iterator it2 = quasi_backtrack[call].begin();
					it2 != quasi_backtrack[call].end(); it2++) {

				it->second.enable_done[it2->first] = true; //eid is enabled
				it->second.quasi_cost[it2->first] = quasi;
//				it->second.quasi_cost[it2->first] = quasi_backtrack[call][eid];

			}
		}

		it->second.enable_done[eid] = false; // self eid in the enable_done if false;

		int remove_eid = 0;
		for (map<int, int>::iterator it2 = quasi_backtrack[call].begin();
				it2 != quasi_backtrack[call].end(); it2++) {
//			cout<<it2->first<<" : "<<it2->second<<endl;
			if (it2->second == 0) {
				remove_eid = it2->first;
			}

			it2->second--;
		}
		if (remove_eid != 0) {
			quasi_backtrack[call].erase(remove_eid);
		}

		//step 2: all in quasi_backtrack distance left -1

//		cout << it->second.toString_quasi() << endl;
	}

}

vector<string> lin_checker::split_string(string input, string split_by) {

	vector < string > str_list;
	if (input.size() < 1)
		return str_list;
	int comma_n = 0;
	do {
		std::string tmp_s = "";
		comma_n = input.find(split_by);
		if (-1 == comma_n) {
			tmp_s = input.substr(0, input.length());
			str_list.push_back(tmp_s);
			break;
		}
		tmp_s = input.substr(0, comma_n);
		input.erase(0, comma_n + split_by.size());
		str_list.push_back(tmp_s);
	} while (true);
	return str_list;
}

string lin_checker::trim(string s) {
	string::iterator new_end = remove_if(s.begin(), s.end(),
			bind2nd(equal_to<char>(), ' '));
	s.erase(new_end, s.end());
	return s;
}

string lin_checker::remove_head_and_tail(string s) {
	int remove_length = 1;
	if ((int) s.length() < (int) (remove_length * 2))
		return s;
	else {
		s = s.substr(1, s.length() - 2);
	}
	return s;

}

//only check type, function, return value,trace1 is the sequental trace
bool lin_checker::quasi_check_two_traces_same(map<int, InspectEvent>& s_trace1,
		map<int, InspectEvent>& q_trace2) {

	if (s_trace1.size() != q_trace2.size())
		return false; //optional, to ensure they have the same size

	map<int, InspectEvent>::iterator it1 = s_trace1.begin();
	map<int, InspectEvent>::iterator it2 = q_trace2.begin();

	for (; it1 != s_trace1.end();) {

		if (verbose > 2) {
			cout << endl << it1->second.toString_quasi() << endl;
			cout << it2->second.toString_quasi() << endl << endl;
		}

		if (it1->second.type != it2->second.type)
			return false;

		if (it1->second.method_name.compare(trim(it2->second.method_name)) != 0)
			return false;

		if (it1->second.return_value != it2->second.return_value)
			return false;

		if (it1->second.return_value == 1) {
			if (it1->second.retval != it2->second.retval)
				return false;
		}

		it1++;
		it2++;
	}

	return true;
}

bool lin_checker::quasi_check_with_serial_traces(
		map<int, InspectEvent>& quazi_trace) {
	char * dir = "serial_trace/";
	bool ret = false;

	DIR *d;
	struct dirent * entry;

	unsigned char isFile = 0x8;
	d = opendir(dir);
	entry = readdir(d);

	while (entry != NULL) {

		if (entry->d_type == isFile) {
			char * name = entry->d_name;
			//	cout<<name<<endl;
			if (strstr(name, ".log") && !strstr(name, ".xml")) {

				char full_name[64];

				sprintf(full_name, "%s%s", dir, name);

				if (verbose > 1)
					cout << "File: " << full_name << endl;

				map<int, InspectEvent> trace = gen_trace_from_file(full_name);

				if (quasi_check_two_traces_same(trace, quazi_trace)) {
					if (verbose > 1)
						cout << "linearizable" << endl;
					ret = true;
				} else {
					if (verbose > 1)
						cout << "not linearizable" << endl;
				}

			}
		}

		entry = readdir(d);             //Next file in directory
	}
	closedir(d);

	return ret;

}

map<int, InspectEvent> lin_checker::gen_trace_from_file(char* path_file) {

	map<int, InspectEvent> trace;

	vector < string > fields;
	vector < string > elements;
	string item1;
	string item2;

	fstream fin(path_file);
	string line;
	while (getline(fin, line))  //read file by line
	{
		if (line.size() < 1)
			continue;  //senity check

//		cout << line << endl;
		line = trim(line);
		line = remove_head_and_tail(line);
//		cout << line << endl;

		fields = split_string(line, "|");

		if (fields.size() == 0)
			continue; //senity check

		InspectEvent e;
		e.init();

		for (vector<string>::iterator it = fields.begin(); it != fields.end();
				it++) {
//			cout << (*it) << endl;

			elements = split_string((*it), "=");

			item1 = elements[0];
			item2 = elements[1];

			if (item1.compare("t") == 0) {
				e.thread_id = atoi(item2.c_str());

			} else if (item1.compare("type") == 0) {
				if (item2.compare("obj_call") == 0) {
					e.type = OBJ_CALL;

				} else if (item2.compare("obj_resp") == 0) {
					e.type = OBJ_RESP;

				}

			} else if (item1.compare("o") == 0) {
				e.obj_id = atoi(item2.c_str());

			} else if (item1.compare("function") == 0) {
				e.method_name = item2;

			} else if (item1.compare("return") == 0) {
				e.return_value = 1;
				e.retval = atoi(item2.c_str());
			}
		}

		trace[trace.size() + 1] = e;
	}
	fin.close();

//	for (map<int, InspectEvent>::iterator it = trace.begin(); it != trace.end();
//			it++) {
//
//		cout << it->second.toString_quasi() << endl;
//
//	}

	return trace;

}

set<string> lin_checker::read_filters() {
	function_filter.clear();
//	vector<string> ret;
	char* filter_file = "linFilter/filter.txt";
	fstream fin(filter_file);
	string line;
	cout << "Filter: { ";
	while (getline(fin, line))  //read file by line
	{
		cout << line << ", ";
//		ret.push_back(line);
		function_filter.insert(line);

	}
	cout << "}" << endl;
	fin.close();

	return function_filter;

}

vector<map<int, int> > lin_checker::get_sub_quasi_traces(
		map<int, InspectEvent> &curr_trace, string function) {

	int extension_count = 1;

	vector < map<int, int> > ret;

	map<int, quasi_state> states;
	map<int, set<int> > new_enabled;
	set<int> existing_enabled;

	for (map<int, InspectEvent>::iterator it = curr_trace.begin();
			it != curr_trace.end(); it++) {

//		cout<<it->second.method_name<<endl;
//		cout<<function<<endl;

//		cout<<it->second.toString_quasi()<<endl;

		if (it->second.type == OBJ_RESP)
			continue; //only record obj_call at this moment
		if (it->second.method_name.compare(function) != 0)
			continue;
//
//		states[it->first].enable_done = it->second.enable_done; //copy the information for the first trace
//		states[it->first].quasi_cost = it->second.quasi_cost; //copy the information for the first trace
//		states[it->first].selected_eid = it->first;

//		new_enabled[it->first].clear(); //compute the new_enabled set
		for (map<int, bool>::iterator it2 = it->second.enable_done.begin();
				it2 != it->second.enable_done.end(); it2++) {
			int enabled = it2->first;

			if (existing_enabled.find(enabled) == existing_enabled.end()) {
//				cout<<enabled<<endl;
				new_enabled[it->first].insert(enabled);
				existing_enabled.insert(enabled);
			} else {
				new_enabled[it->first];
			}
		}
	}

	if (new_enabled.size() == 0) {
		return ret;
	}

//	keep for future use
	if (verbose > 1)
		cout << endl << "Print new enabled set" << endl;

	quasi_state init_state;
	init_state.must_select = 0;
	init_state.selected_eid = 0;

	int first_index = new_enabled.begin()->first;

	int cost_temp = 0;

	for (set<int>::iterator it2 = new_enabled.begin()->second.begin();
			it2 != new_enabled.begin()->second.end(); it2++) {
		init_state.enable_done[*it2] = true;
		init_state.quasi_cost[*it2] = quasi + cost_temp;
		cost_temp++;
	}
	init_state.enable_done[first_index] = false;
	init_state.selected_eid = first_index;

	if (verbose > 1) {
		for (map<int, set<int> >::iterator it = new_enabled.begin();
				it != new_enabled.end(); it++) {
//		if (it->second.size() == 0)
//			continue;
			cout << it->first << ": {";
			for (set<int>::iterator it2 = it->second.begin();
					it2 != it->second.end(); it2++) {

				cout << (*it2) << ", ";
			}

			cout << "}" << endl;
		}
	}

//	states[first_index] = init_state;
//	for (map<int, quasi_state>::iterator it = states.begin();
//			it != states.end(); it++) {
//		cout << "Select: " << it->second.selected_eid << ",  Index: "
//				<< it->first << ",  " << states[it->first].to_string() << endl;
//	}

	states = new_trace_from_state(init_state, first_index, new_enabled);

	map<int, int> ret_temp;
	if (verbose > 1)
		cout << endl << "new trace: #" << extension_count++ << endl;

	for (map<int, quasi_state>::iterator it = states.begin();
			it != states.end(); it++) {
		if (verbose > 1)
			cout << "Select: " << it->second.selected_eid << ",  Index: "
					<< it->first << ",  " << states[it->first].to_string()
					<< endl;
		ret_temp[it->first] = it->second.selected_eid;
	}
//	cout << ret_temp.size() << endl;
	ret.push_back(ret_temp);

	while (true) { //while the trace still has backtrack points

		if (verbose > 1)
			cout << endl;

		int up_event = 0;
		int backtrack_state_index = 0;

		for (map<int, quasi_state>::reverse_iterator it = states.rbegin();
				it != states.rend(); it++) {
//			cout << endl << "Select: " << it->second.selected_eid
//					<< ",  index: " << it->first << ",  "
//					<< it->second.to_string() << endl;

			for (map<int, bool>::iterator it2 = it->second.enable_done.begin();
					it2 != it->second.enable_done.end(); it2++) {

				if (it2->second) { //has backtrack information

					if (it->second.must_select > 0) {
						up_event = it->second.must_select;

						for (map<int, bool>::iterator it4 =
								it->second.enable_done.begin();
								it4 != it->second.enable_done.end(); it4++) {
							it4->second = false;
						}
					} else {
						up_event = it2->first;
					}
					backtrack_state_index = it->first;

//						cout << "backtrack: " << up_event << " at state: "
//								<< backtrack_state_index << endl;

					break;//break from iterating enabled_set from the current state
				}
			}

			if (up_event > 0) {
				break; //break from reverse iterating states
			}
		}

		//step 1. mark the selected as done,
		if (up_event > 0) { //has backtrack point
			states[backtrack_state_index].enable_done[up_event] = false;
			states[backtrack_state_index].selected_eid = up_event;

//			cout << "after backtrack" << endl;
//			cout << "Index: " << backtrack_state_index << ",  "
//					<< states[backtrack_state_index].to_string() << endl;

			if (verbose > 1)
				cout << endl << "new trace: #" << extension_count++ << endl;
//			for (map<int, quasi_state>::iterator it = states.begin();
//					it != states.end(); it++) {
//
//				if (it->first == backtrack_state_index)
//					break;
//
//				cout << "Select: " << it->second.selected_eid << ",  Index: "
//						<< it->first << ",  " << it->second.to_string() << endl;
//			}

			//the sub_trace
			map<int, quasi_state> sub_trace = new_trace_from_state(
					states[backtrack_state_index], backtrack_state_index,
					new_enabled);

			for (map<int, quasi_state>::iterator it = sub_trace.begin();
					it != sub_trace.end(); it++) {

				states[it->first] = it->second;

//				cout << "Select: " << it->second.selected_eid << ",  Index: "
//						<< it->first << ",  " << states[it->first].to_string()
//						<< endl;

			}

			ret_temp.clear();
			for (map<int, quasi_state>::iterator it = states.begin();
					it != states.end(); it++) {
				if (verbose > 1)
					cout << "Select: " << it->second.selected_eid
							<< ",  Index: " << it->first << ",  "
							<< states[it->first].to_string() << endl;
				ret_temp[it->first] = it->second.selected_eid;

			}

			ret.push_back(ret_temp);

			continue;

		} else {
			break; //no backtrack point, while loop end
		}
//		break;

	}
	return ret;

}

map<int, quasi_state> lin_checker::new_trace_from_state(quasi_state &from_state,
		int &index, map<int, set<int> > &new_enabled) {

//	cout<<from_state.to_string()<<endl;

	map<int, quasi_state> new_trace;

	quasi_state last_state = from_state;

	int curr_index;

	for (map<int, set<int> >::iterator it2 = new_enabled.find(index);
			it2 != new_enabled.end();) { //generate next states

		curr_index = it2->first;

		new_trace[curr_index] = last_state;

//		cout << "Select: " << new_trace[curr_index].selected_eid << ",   curr: "
//				<< curr_index << ",  " << new_trace[curr_index].to_string()
//				<< endl;

		quasi_state new_state;

		new_state.must_select = 0;
		new_state.selected_eid = 0;

		////////////////////////////////////////////////////////////////
		//copy enabled set and cost to new state
		for (map<int, bool>::iterator it =
				new_trace[curr_index].enable_done.begin();
				it != new_trace[curr_index].enable_done.end(); it++) {

			int enabled_but_not_selected = it->first;

			if (new_trace[curr_index].selected_eid == enabled_but_not_selected)
				continue; //don't copy the selected event to the next state

			new_state.enable_done[enabled_but_not_selected] = true;

			new_state.quasi_cost[enabled_but_not_selected] =
					new_trace[curr_index].quasi_cost[enabled_but_not_selected];

//			cout<<"selected_eid: "<<new_trace[curr_index].selected_eid<<endl;
//
//			cout<<"enabled_but_not_selected: "<<enabled_but_not_selected<<endl;

			if (new_trace[curr_index].selected_eid
					!= enabled_but_not_selected) { //break the partial order

				new_state.quasi_cost[enabled_but_not_selected]--;
				if (new_state.quasi_cost[enabled_but_not_selected] == 0) {
					new_state.must_select = enabled_but_not_selected;
				}
			}
//				else if (new_trace[curr_index].selected_eid
//					< enabled_but_not_selected) {
//				if (new_state.quasi_cost[enabled_but_not_selected] > quasi) {
//					new_state.quasi_cost[enabled_but_not_selected]--;
//				}
//			}

		}
		//copy enabled set and cost to new state

//		cout << " temp: " << new_state.to_string() << endl;

		////////////////////////////////////////////////////////////////

		//add new_enabled into the next state

		it2++;

		if (it2 != new_enabled.end()) {
			for (set<int>::iterator it = it2->second.begin();
					it != it2->second.end(); it++) {

				new_state.enable_done[(*it)] = true;

				new_state.quasi_cost[(*it)] = quasi * 2;
			}
		}
		//add new_enabled into the next state

//		cout <<"Select: "<<new_trace[curr_index].selected_eid <<",   next: " << curr_index << ",  "
//						<< new_trace[curr_index].to_string() << endl;

		////////////////////////////////////////////////////////////////

		//determine the selected event of new_state

		if (new_state.must_select > 0) {
			new_state.selected_eid = new_state.must_select;
//			new_state.must_select = 0;
			for (map<int, bool>::iterator it4 = new_state.enable_done.begin();
					it4 != new_state.enable_done.end(); it4++) {
				it4->second = false;
			}

		} else {
			new_state.selected_eid = new_state.enable_done.begin()->first;
		}

		if (new_state.selected_eid > 0) {
			new_state.enable_done[new_state.selected_eid] = false;
		}

//		cout << "Select: " << new_state.selected_eid << ",   next: "
//				<< curr_index << ",  " << new_state.to_string() << endl;
//		cout << " temp: " << new_state.to_string() << endl;

		//determine the selected event of new_state

		////////////////////////////////////////////////////////////////
//
//		cout << " ????: " << curr_index << ",  " << new_state.to_string()
//				<< endl;

		last_state = new_state;

	}

	return new_trace;

}

void lin_checker::print_trace(map<int, InspectEvent> &curr_trace) {

	for (map<int, InspectEvent>::iterator it = curr_trace.begin();
			it != curr_trace.end(); it++) {
		cout << it->second.toString_quasi() << endl;
	}

}

bool lin_checker::check_quasi_trace(map<int, InspectEvent> &curr_trace) {

	if (verbose > 0)
		print_trace(curr_trace);

	// get the backtrack information
	get_bt_info(curr_trace);
	if (verbose > 1)
		cout << endl;
//	for (map<int, InspectEvent>::iterator it = curr_trace.begin();
//			it != curr_trace.end(); it++) {
//		if (it->second.type == OBJ_RESP)
//			continue; //only print obj_call
//		cout << it->second.toString_quasi() << endl;
//	}

	bool ret = false;

	for (set<string>::iterator it = function_filter.begin();
			it != function_filter.end(); it++) {

//		cout<<function_count[(*it)]<<endl;

		if (function_count[(*it)] < 2)
			continue;

		if (quasi_trace_extension(curr_trace, (*it))) {
			ret = true;
		}

	}

//	bool ret = quasi_extend_check_trace_by_funtion(curr_trace,"Counter::add()");

//	if (ret) {
//		cout << "Quazi Linearizable" << endl;
//	} else {
//		cout << "Not Quazi Linearizable" << endl;
//	}

	return ret;

}

bool lin_checker::quasi_trace_extension(map<int, InspectEvent> &curr_trace,
		string test_function) {
	bool ret = false;

	if (verbose > 1)
		cout << "For subtraces for function: " << test_function << endl;

	vector < map<int, int> > quasi_traces = get_sub_quasi_traces(curr_trace,
			test_function);

	map<int, InspectEvent> restored_trace;

	for (int i = 0; i < quasi_traces.size(); i++) {

		if (verbose > 1) {
			cout << "Restore trace #" << i + 1 << " : ";
			for (map<int, int>::iterator it2 = quasi_traces[i].begin();
					it2 != quasi_traces[i].end(); it2++) {

				cout << it2->second << " ";
			}

			cout << "    ->    ";
		}

		restored_trace.clear();

		for (map<int, InspectEvent>::iterator it2 = curr_trace.begin();
				it2 != curr_trace.end(); it2++) {

			if (quasi_traces[i].find(it2->first) == quasi_traces[i].end()) {

				if (verbose > 1)
					cout << it2->first << " ";

				restored_trace[restored_trace.size() + 1] =
						curr_trace[it2->first];

				if (verbose > 1)
					cout << it2->first + 1 << " ";
				restored_trace[restored_trace.size() + 1] =
						curr_trace[it2->first + 1];

			} else {

				if (verbose > 1)
					cout << quasi_traces[i][it2->first] << " ";
				restored_trace[restored_trace.size() + 1] =
						curr_trace[quasi_traces[i][it2->first]];

				if (verbose > 1)
					cout << quasi_traces[i][it2->first] + 1 << " ";
				restored_trace[restored_trace.size() + 1] =
						curr_trace[quasi_traces[i][it2->first] + 1];
			}
			it2++;

		}

		if (verbose > 1)
			cout << endl;

		if (verbose > 0) {
			print_trace(restored_trace);
			cout << endl;
		}

		quasi_count++;
		bool quasi_trace_check = quasi_check_with_serial_traces(restored_trace);

		char* temp = "No";

		if (quasi_trace_check) {
			ret = true;
			temp = "Yes";
		}
		//////////////////////////////////////

		if (verbose > 0)
			cout << "run_count: " << run_count << ",    check_count: "
					<< trace_count << endl;

		if (run_count == 1 && trace_count == 1 && quasi_count == 1) {
			system("rm -rf to_check_quasi_trace");
			system("mkdir to_check_quasi_trace");
		}

		char path[64];

		if (trace_count == 1 && quasi_count == 1) {
			sprintf(path, "mkdir to_check_quasi_trace/run%d", run_count);
			system(path);
		}

		//	cout << (string) path << endl;

		sprintf(path, "to_check_quasi_trace/run%d/%d-%d-%s.txt", run_count,
				trace_count, quasi_count, temp);

		trace_dump_to_file(restored_trace, path);

////////////////////////////////////

		if (verbose > 1)
			cout << endl;

	}

	return ret;
}

void lin_checker::trace_dump_to_file(map<int, InspectEvent> &curr_trace) {

	if (verbose > 0)
		cout << "run_count: " << run_count << ",    check_count: "
				<< trace_count << endl;

	if (run_count == 1 && trace_count == 1) {
		system("rm -rf to_check_trace");
		system("mkdir to_check_trace");
	}

	char path[64];
	sprintf(path, "mkdir to_check_trace/run%d", run_count);
	if (trace_count == 1) {
		system(path);
	}

//	cout << (string) path << endl;

	sprintf(path, "to_check_trace/run%d/%d.txt", run_count, trace_count);

	if (verbose > 0)
		cout << string(path) << endl;
	ofstream file_writer(path);
	if (file_writer.is_open()) {

		for (map<int, InspectEvent>::iterator it = curr_trace.begin();
				it != curr_trace.end(); it++) {
			file_writer << it->second.toString_line() << endl;

		}

//		file_writer << "This is a line.\n";
//		file_writer << "This is another line.\n";
		file_writer.close();
	}

}

void lin_checker::trace_dump_to_file(map<int, InspectEvent> &curr_trace,
		char* path) {

//	cout << string(path) << endl;

	if (verbose > 0)
		cout << string(path) << endl;
	ofstream file_writer(path);
	if (file_writer.is_open()) {

		for (map<int, InspectEvent>::iterator it = curr_trace.begin();
				it != curr_trace.end(); it++) {
			file_writer << it->second.toString() << endl;

		}

//		file_writer << "This is a line.\n";
//		file_writer << "This is another line.\n";
		file_writer.close();
	}

}

bool lin_checker::linearizable_check_by_diff() {

	char serial_trace[64];
	sprintf(serial_trace, "serial_trace/");
	char to_check_trace[64];
	sprintf(to_check_trace, "to_check_trace/run%d", run_count);
	char file_1[64];
	char file_2[64];

	bool retval = false;

	char diff[128];

	DIR *fdir;
	struct dirent *pdir;

	DIR *fdir2;
	struct dirent *pdir2;

//	int i = 0;
	if ((fdir = opendir(to_check_trace)) == NULL) {
//		fprintf(stderr, "打开错误!\n");
		exit(2);
	}

	while ((pdir = readdir(fdir)) != NULL) {
//		i++;
//		printf("第%d个文件是%s\n", i, pdir->d_name);

		sprintf(file_1, "to_check_trace/run%d/%s", run_count, pdir->d_name);

		if (strstr(file_1, ".txt")) {
//			cout << "  " << string(file_1) << endl;
			if ((fdir2 = opendir(serial_trace)) == NULL) {
				//		fprintf(stderr, "打开错误!\n");
				exit(2);
			}
			while ((pdir2 = readdir(fdir2)) != NULL) {

				sprintf(file_2, "serial_trace/%s", pdir2->d_name);

				if (strstr(file_2, ".log") && !strstr(file_2, ".xml")) {
//					cout << "    " << string(file_2) << endl;
					sprintf(diff, "diff -q --brief %s %s", file_1, file_2);
					if (system(diff) == 0) {
//						cout << "same" << endl;
//						closedir(fdir2);
//
//						closedir(fdir);
//						//	delete fdir;
//						delete pdir;
//						//	delete fdir2;
//						delete pdir2;

						retval = true;

					} else {
//						cout << "not same" << endl;
					}
				}

			}
			closedir(fdir2);
		}
	}

	closedir(fdir);
//	delete fdir;
	delete pdir;
//	delete fdir2;
	delete pdir2;

	return retval;

}

void lin_checker::quasi_split_check_trace() {
	bool ret = false;

	traces.push_back(concurr_trace);
//	if (verbose > 1)
//		cout << "trace size: " << traces.size() << endl;
	vector<map<int, InspectEvent> >::iterator it = traces.begin();

	while (it != traces.end()) {
		map<int, InspectEvent> curr_trace = (map<int, InspectEvent> ) * it;

		vector < map<int, InspectEvent> > ret_traces = check_trace(curr_trace);

		if (ret_traces.size() == 0) {
			trace_count++;
			quasi_count = 0;
			if (check_quasi_trace(curr_trace)) {
				ret = true;
			}
		} else {
			assert(ret_traces.size() == 2);
		}

		traces.erase(it);

//		if (verbose > 1)
//			cout << "return traces size: " << ret_traces.size() << endl;

		if (ret_traces.size() != 0) {
			assert(ret_traces.size() == 2);
			for (vector<map<int, InspectEvent> >::iterator it_ret =
					ret_traces.begin(); it_ret != ret_traces.end(); it_ret++) {

				map<int, InspectEvent> tmp_trace = (map<int, InspectEvent> )
						* it_ret;

				traces.push_back(tmp_trace);
			}
		} else {

		}
//		if (verbose > 1)
//			cout << "now traces size: " << traces.size() << endl;

		it = traces.begin();
	}

	total_check++;

	if (ret) {

		total_lin++;

		cout << "Quazi Linearizable" << endl;
	} else {

		total_not_lin++;
		cout << "Not Quazi Linearizable" << endl;
	}
}
bool trace_complete = false;
void lin_checker::print_check_trace() {

	run_count++;
	trace_count = 0;

	if (!trace_complete) {
		cout << "run #" << run_count << " is not complete,skip" << endl;

		return;
	}

//	return;
//	if (config_lin_serial_flag)
//		return;
	map<int, InspectEvent>::iterator it;
	for (it = concurr_trace.begin(); it != concurr_trace.end(); it++) {
		if (verbose > 0)
			cout << it->first << " : " << it->second.toString_line() << endl;

	}

	if (quasi_flag) {

//		traverse_serial_traces();

		quasi_split_check_trace();

	} else {

		split_check_trace();
		bool result = linearizable_check_by_diff();

		total_check++;

		if (result == true) {

			total_lin++;

			cout << "trace is linearizable" << endl;
		} else {

			total_not_lin++;
			cout << "trace is not linearizable" << endl;
		}
	}
	trace_complete = false;
}

void lin_checker::print_trace2(map<int, InspectEvent> &trace) {
	map<int, InspectEvent>::iterator it;
	for (it = trace.begin(); it != trace.end(); it++) {
		if (verbose > 0)
			cout << it->first << " : " << it->second.toString_line() << endl;

	}

}

void lin_checker::clear() {
	concurr_trace.clear();
	traces.clear();
}

vector<map<int, InspectEvent> > lin_checker::check_trace(
		map<int, InspectEvent> &curr_trace) {
	vector < map<int, InspectEvent> > ret;
	bool whether_split = false;
	map<int, int> pending_call; //map<thread id, event id>

//	cout<<"curr_trace size: "<<curr_trace.size()<<endl;

	int this_call = 0;
	int this_resp = 0;
	int this_tid = 0;
	int that_call = 0;
	int that_resp = 0;
	int that_tid = 0;
	map<int, InspectEvent>::iterator it_trace;

	for (it_trace = curr_trace.begin(); it_trace != curr_trace.end();
			it_trace++) { //each call in the current trace
		if (it_trace->second.type == OBJ_CALL) { //if call, add to pending calls
			pending_call[it_trace->second.thread_id] = it_trace->first;
//			cout << "id: " << it_trace->first << ", call: "
//					<< it_trace->second.toString_line() << endl;
		} else if (it_trace->second.type == OBJ_RESP) { //if response
//			cout << "id: " << it_trace->first << ", resp: "
//					<< it_trace->second.toString_line() << endl;
			assert(pending_call.size() > 0);
			if (pending_call.size() == 1) { //if only one call, means no interleaving
				pending_call.erase(it_trace->second.thread_id);
//				cout << "normal" << endl;

			} else if (pending_call.size() > 1) { //if more that one pending calls, means there is interleaving

				this_resp = it_trace->first;
				this_tid = it_trace->second.thread_id;
				whether_split = true;
//				if (verbose > 0)
//					cout << "interleaving!" << endl;
				map<int, int>::iterator it_pending_call;
				for (it_pending_call = pending_call.begin();
						//each pending call
						it_pending_call != pending_call.end();
						it_pending_call++) {
//					cout << it_pending_call->first << " : "
//							<< curr_trace[it_pending_call->second].toString_line()
//							<< endl;

					if (it_pending_call->first == this_tid) { //if same thread id, pair call
						this_call = it_pending_call->second;
					} else { //not the same thread id, pick one call
						if (that_call == 0) {
							that_call = it_pending_call->second;
						}
					}
				}

//				if (verbose > 0)
//					cout << "this_call" << " : " << this_call
//							<< curr_trace[this_call].toString_line() << endl;
//				if (verbose > 0)
//					cout << "this_resp" << " : " << this_resp
//							<< curr_trace[this_resp].toString_line() << endl;
//				if (verbose > 0)
//					cout << "that_call" << " : " << that_call
//							<< curr_trace[that_call].toString_line() << endl;
//				cout << "that_resp" << " : " << that_resp << endl;

				that_tid = curr_trace[that_call].thread_id;

				map<int, InspectEvent>::iterator it_rest_trace = it_trace;
				it_rest_trace++;
				for (; it_rest_trace != curr_trace.end(); it_rest_trace++) {

//					cout << "id: " << it_rest_trace->first << ", ?: "
//							<< it_rest_trace->second.toString_line() << endl;
					if (it_rest_trace->second.type == OBJ_RESP) {
						if (it_rest_trace->second.thread_id == that_tid) {

							that_resp = it_rest_trace->first;
							break;

						}
					}

				}
//				cout << "this_call" << " : " << this_call << endl;
//				cout << "this_resp" << " : " << this_resp << endl;
//				cout << "that_call" << " : " << that_call << endl;
//				if (verbose > 0)
//					cout << "that_resp" << " : " << that_resp
//							<< curr_trace[that_resp].toString_line() << endl;
//				if (verbose > 0)
//					cout << "this_tid" << " : " << this_tid << endl;
//				if (verbose > 0)
//					cout << "that_tid" << " : " << that_tid << endl;

				break;

			}

		}

	}

	if (whether_split) {
		if (verbose > 0)
			cout << "should split into 2 traces" << endl;
		if (verbose > 0)
			cout << "trace 1 " << endl;
		//build the trace 1 this_call->this_resp->that_call->that_resp
		map<int, InspectEvent> trace_1;
		map<int, InspectEvent> that_temp;
		for (it_trace = curr_trace.begin(); it_trace != curr_trace.end();
				it_trace++) {

//			cout << "id: " << it_trace->first << ", "
//					<< it_trace->second.toString_line() << endl;
			if (it_trace->first == that_call) { //only store that_call, because that_resp has not appeared yet
				that_temp[that_temp.size() + 1] = it_trace->second; //store in a temp map
				continue;
			}

			if (it_trace->first == this_resp) { //met the this_resp
				trace_1[trace_1.size() + 1] = it_trace->second;
				for (map<int, InspectEvent>::iterator it_that_temp =
						that_temp.begin(); it_that_temp != that_temp.end();
						it_that_temp++) {
					trace_1[trace_1.size() + 1] = it_that_temp->second;

				}
				continue;

			}

			trace_1[trace_1.size() + 1] = it_trace->second;

		}
		map<int, InspectEvent>::iterator it_trace_1;
		for (it_trace_1 = trace_1.begin(); it_trace_1 != trace_1.end();
				it_trace_1++) {
			if (verbose > 0)
				cout << "id: " << it_trace_1->first << ", "
						<< it_trace_1->second.toString_line() << endl;

		}

//		ret.push_back(trace_1);

		//build the trace 2 that_call->that_resp->this_call->this_resp
		if (verbose > 0)
			cout << "trace 2 " << endl;
		map<int, InspectEvent> trace_2;
		that_temp.clear();
		bool that_resp_not_reached = true;
		for (it_trace = curr_trace.begin(); it_trace != curr_trace.end();
				it_trace++) {

			//			cout << "id: " << it_trace->first << ", "
			//					<< it_trace->second.toString_line() << endl;
			if (it_trace->first >= this_call
					&& this_tid == it_trace->second.thread_id
					&& that_resp_not_reached) { //store everything in this_tid from this_call until reached that_resp
				that_temp[that_temp.size() + 1] = it_trace->second; //store in a temp map
				continue;
			}

			if (it_trace->first == that_resp) { //met the this_resp
				that_resp_not_reached = false;
				trace_2[trace_2.size() + 1] = it_trace->second;
				for (map<int, InspectEvent>::iterator it_that_temp =
						that_temp.begin(); it_that_temp != that_temp.end();
						it_that_temp++) {
					trace_2[trace_2.size() + 1] = it_that_temp->second;

				}
				continue;

			}

			trace_2[trace_2.size() + 1] = it_trace->second;

		}
		map<int, InspectEvent>::iterator it_trace_2;
		for (it_trace_2 = trace_2.begin(); it_trace_2 != trace_2.end();
				it_trace_2++) {
			if (verbose > 0)
				cout << "id: " << it_trace_2->first << ", "
						<< it_trace_2->second.toString_line() << endl;

		}
		ret.push_back(trace_1);
		ret.push_back(trace_2);

	}
//	else {
//		if (verbose > 0)
//			cout << "no interleaving ,just check" << endl;
//	}

//	cout << "ret size: " << ret.size() << endl;

	return ret;

}

bool lin_checker::check_trace_linearizability(
		map<int, InspectEvent> &curr_trace) {

	return true;

}

void lin_checker::split_check_trace() {
	traces.push_back(concurr_trace);
//	if (verbose > 0)
//		cout << "trace size: " << traces.size() << endl;
	vector<map<int, InspectEvent> >::iterator it = traces.begin();

	while (it != traces.end()) {
		map<int, InspectEvent> curr_trace = (map<int, InspectEvent> ) * it;
//		print_trace2(curr_trace);
		vector < map<int, InspectEvent> > ret_traces = check_trace(curr_trace);

		if (ret_traces.size() == 0) {
			trace_count++;
			trace_dump_to_file(curr_trace);
		}

		traces.erase(it);
//		cout << "traces size: " << traces.size() << endl;
//		if (verbose > 0)
//			cout << "return traces size: " << ret_traces.size() << endl;

		if (ret_traces.size() != 0) {
			assert(ret_traces.size() == 2);
			for (vector<map<int, InspectEvent> >::iterator it_ret =
					ret_traces.begin(); it_ret != ret_traces.end(); it_ret++) {

				map<int, InspectEvent> tmp_trace = (map<int, InspectEvent> )
						* it_ret;
//				cout << endl;
//				for (map<int, InspectEvent>::iterator it_tmp_trace =
//						tmp_trace.begin(); it_tmp_trace != tmp_trace.end();
//						it_tmp_trace++) {
//					cout << "id: " << it_tmp_trace->first << ", call: "
//							<< it_tmp_trace->second.toString_line() << endl;
//				}
				traces.push_back(tmp_trace);
			}
		} else {

		}
//		if (verbose > 0)
//			cout << "now traces size: " << traces.size() << endl;
//		traces.push_back(curr_trace);
		it = traces.begin();
	}

}

/* namespace std */
