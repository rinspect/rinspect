/*
 * yices_path_computer_singleton.h
 *
 *  Created on: Apr 30, 2012
 *      Author: jack
 */

#ifndef YICES_PATH_COMPUTER_SINGLETON_H_
#define YICES_PATH_COMPUTER_SINGLETON_H_
#include "inspect_ucg_graph.hh"
#include "state.hh"
#include <map>
#include <vector>

class yices_path_computer_singleton {
public:

	yices_path_computer_singleton();

	~yices_path_computer_singleton();
	int result;
	int add_op(int a);
	int minus_op(int a);

	void clean();

	//map<string,string> event_map;



	//encode the trace in to yices expressions, get assignment set
	void compute_new_trace();

	//generate the new trace from the value yices gives, return the new blocking clause
	vector<pair<int, int> > resort_event_order();

	PolyGraph graph;//packaged yices API
	map<int,int> value_map;//assignments from Yices
	map<int,InspectEvent> event_map;//store the original events
	map<int,int> thread_event_count;// the count of threads and their events
	map<int, map<int, InspectEvent> > result_trace;//the new trace to be executed
//	map<int,map<int,map<int, bool> > > dependents;//dependent events: map<obj_id,map<thread_id,map<event_id, whether write> > >

	bool game_mode;

	string get_n_name(int name);
	int max_traces;

	bool has_next_trace;
	bool run_yices_replay;

	bool show_race_detail;

	int verbose;
	int v_2;
	int v_3;




	static yices_path_computer_singleton* m_Instance;
	static yices_path_computer_singleton* getInstance();
	void compute_next_path();


};

#endif /* YICES_PATH_COMPUTER_SINGLETON_H_ */
