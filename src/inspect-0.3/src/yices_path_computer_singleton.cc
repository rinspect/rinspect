/*
 * yices_path_computer_singleton.cpp
 *
 *  Created on: Apr 30, 2012
 *      Author: jack
 */
#include <iostream>
#include <hash_map>
#include "yices_path_computer_singleton.hh"
#include "inspect_ucg_graph.hh"
#include <sstream>
#include <iomanip>
#include <locale>
#include <string>
using namespace std;

yices_path_computer_singleton::yices_path_computer_singleton() {
	// TODO Auto-generated constructor stub
	result = 0;
	run_yices_replay = false;
	show_race_detail = false;
	v_2 = 2;
	v_3 = 3;
}

yices_path_computer_singleton::~yices_path_computer_singleton() {
	// TODO Auto-generated destructor stub
}

void yices_path_computer_singleton::compute_new_trace() {

	has_next_trace = false;
	vector<pair<int, int> > block_edges; //block the whole trace
	result_trace.clear();
	map<int, vector<pair<int, int> > > lock_events; //structure:

	if (verbose >= v_3) {
		cout << "event_map size:" << event_map.size() << endl;
		cout << "block size: " << block_edges.size() << endl;
	}
	map<int, InspectEvent>::iterator it;

	int last_event = 0;
	for (it = event_map.begin(); it != event_map.end(); it++) {

		if (last_event == 0) {

		}

		if (verbose >= v_3) {

			cout << it->first << ": " << it->second.toString()
					<< "                  event type:" << it->second.type
					<< endl;
		}

		//value_map[it->first]=-1;

		bool should_block = true;
		if (verbose >= v_3) {
			cout << "event id:" << it->first << endl;
		}

		thread_event_count[it->second.thread_id]++; //count the threads and the number of each thread's events

		if (last_event != 0) { //record the change of threads(total order)
			if (verbose >= v_3) {
				cout << "order:" << last_event << "  to  " << it->first << endl;
			}

			int head = last_event;
			int tail = it->first;
//			if (event_map[last_event].thread_id != it->second.thread_id
//					&& should_block) {
			if (should_block&& event_map[head].thread_id!=event_map[tail].thread_id) {


				block_edges.push_back(pair<int, int>(head, tail));

				if (verbose >= v_3) {
					cout << "add into the block clause:" << head << "  to  "
							<< tail << endl;
					cout << "block size" << block_edges.size() << endl;
				}

			}
		}
		last_event = it->first;

//		/////////////////////////////
//		////record dependent events///
//		////////////////////////////
//		/////dependent events: map<obj_id,map<thread_id,map<event_id, whether write> > >
//		//////obj_read: 31    obj_write:32
//		if (it->second.type == 31) {
//			if (verbose >= v_3) {
//				cout << "~~~obj read:" << it->second.obj_id << "    thread id:"
//						<< it->second.thread_id << "     event id:" << it->first
//						<< endl;
//
//			}
//			dependents[it->second.obj_id][it->second.thread_id][it->first] =
//					false;
//		} else if (it->second.type == 32) {
//			if (verbose >= v_3) {
//				cout << "~~~obj write:" << it->second.obj_id << "    thread id:"
//						<< it->second.thread_id << "     event id:" << it->first
//						<< endl;
//
//			}
//
//			dependents[it->second.obj_id][it->second.thread_id][it->first] =
//					true;
//		}
//		/////////////////////////////

	}

//	graph.block_trace(block_edges, false);
//	graph.check();

	if (verbose >= v_3) {
		cout << "block size" << block_edges.size() << endl;
		cout << "_________________________________________" << endl;

		cout << "thread_event_count size:   " << thread_event_count.size()
				<< endl;
	}
	map<int, int>::iterator it2;

	//for each thread, get all events
	map<int, int> thread_create;
	map<int, int> thread_join;
	for (it2 = thread_event_count.begin(); it2 != thread_event_count.end();
			it2++) { //traverse all the threads
		if (verbose >= v_3) {
			cout << endl << "thread:" << it2->first << "   count:"
					<< it2->second << endl << endl;
		}

//		it2->second = 0; //recount the number of events of each thread

		if (verbose >= v_3) {
			cout << endl << "for thread: " << it2->first << endl;
		}

		last_event = 0; //to record the last event, in order to make edges
		//get the events and only keep the events for this thread

		map<int, int> lock_set;
		map<int, int> wait_set;

		for (it = event_map.begin(); it != event_map.end(); it++) { //traverse all the events of a thread
			if (it->second.thread_id != it2->first) {
				continue;
			}
			if (verbose >= v_3) {
				cout << it->first << "  :  " << it->second.toString() << endl;
			}

			if (it->second.type == 24) { //thread_postcreate
				thread_create[it->second.child_id] = it->first;
				if (verbose >= v_3) {
					cout << "____find a thread creation from   event"
							<< it->first << "   :" << it->second.thread_id
							<< "   to   " << it->second.child_id << endl;
				}

			} else if (it->second.type == 25) { //join
				thread_join[it->second.child_id] = it->first;
				if (verbose >= v_3) {
					cout << "____find a thread join from   event" << it->first
							<< "   :" << it->second.thread_id << "   to   "
							<< it->second.child_id << endl;
				}
			}

			if (it->second.type == 2) { //lock
				lock_set[it->second.mutex_id] = it->first;
				if (verbose >= v_3) {
					cout << "____find a lock from   event" << it->first
							<< "   :thread" << it->second.thread_id
							<< "   lock   " << it->second.mutex_id << endl;
				}
			}

			else if (it->second.type == 3) { //unlock

				if (lock_set[it->second.mutex_id]
						&& lock_set[it->second.mutex_id] > 0) {
					lock_events[it->second.mutex_id].push_back(
							pair<int, int>(lock_set[it->second.mutex_id],
									it->first));
					if (verbose >= v_3) {
						cout << "____find a unlock from   event" << it->first
								<< "   :thread" << it->second.thread_id
								<< "   unlock   " << it->second.mutex_id
								<< endl;

						cout << "make pair, lock object=" << it->second.mutex_id
								<< "    from " << lock_set[it->second.mutex_id]
								<< "     to    " << it->first << endl;
					}

					lock_set[it->second.mutex_id] = -1;

				}

			}

			if (last_event != 0) { //add edges for each threads

				graph.addEdge(last_event, it->first, false);
				//graph.check();
				if (verbose >= v_3) {
					cout << "make edge between" << last_event << " and "
							<< it->first << endl;
				}

			}

			if (last_event == 0) {
				if (thread_create[it2->first] > 0) {
//					cout << endl << "first event of a thread" << endl;

					graph.addEdge(thread_create[it->second.thread_id],
							it->first, false); // edge: thread_create->first event of this thread
					if (verbose >= v_3) {
						cout << "first event:   make edge between"
								<< thread_create[it->second.thread_id]
								<< " and " << it->first << endl;
					}
				}

			}
			last_event = it->first;

			string event_info = it->second.toString();
//			cout << "event id:" << it->first << ":  " << event_info << endl;

		}

		if (thread_join[it2->first] > 0 && last_event != 0) {
//			cout << endl << "last event of a thread" << endl << endl;
			graph.addEdge(last_event,
					thread_join[event_map[last_event].thread_id], false);
			if (verbose >= v_3) {
				cout << "last event:    make edge between" << last_event
						<< " and "
						<< thread_join[event_map[last_event].thread_id] << endl; // edge: thread_create->first event of this thread
			}
		}

	}
	if (verbose >= v_3) {
		cout << "lock events size: " << lock_events.size() << endl;
	}

	map<int, vector<pair<int, int> > >::iterator it_lock;

	for (it_lock = lock_events.begin(); it_lock != lock_events.end();
			it_lock++) {
		vector<pair<int, int> >::iterator it_pair;
		vector<pair<int, int> >::iterator it_pair2;
		for (it_pair = it_lock->second.begin();
				it_pair != it_lock->second.end(); it_pair++) {
			if (verbose >= v_3) {
				cout << "lock-unlock on mutex: " << it_lock->first
						<< "   from  " << it_pair->first << "  to  "
						<< it_pair->second << "   in thread"
						<< event_map[it_pair->first].thread_id << endl;
			}
			for (it_pair2 = it_pair; it_pair2 != it_lock->second.end();
					it_pair2++) {
				if (event_map[it_pair->first].thread_id
						!= event_map[it_pair2->first].thread_id) { //not in the same thread
					graph.addPolyEdge(it_pair->second, it_pair2->first,
							it_pair2->second, it_pair->first, true);
					if (verbose >= v_3) {
						cout << "add polyEdge: " << it_pair->second << "<"
								<< it_pair2->first << "  xor  "
								<< it_pair2->second << "<" << it_pair->first
								<< endl;
					}

				}

			}

		}

	}
	if (verbose >= v_3) {
		cout << "_________________________________________" << endl;

		cout << "block size=" << block_edges.size() << endl;
	}
	graph.block_trace(block_edges, false);
	int trace_count = 0;
	max_traces = 99999;

//	///map<int,map<int,map<int, bool> > > dependents;
//	//dependent events: map<obj_id,map<thread_id,map<event_id, whether write> > >
//	if (verbose >= v_3) {
//		cout << "There are  " << dependents.size() << "  shared obj" << endl;
//	}
//	for (map<int, map<int, map<int, bool> > >::iterator obj_it =
//			dependents.begin(); obj_it != dependents.end(); obj_it++) {
//		if (verbose >= v_2) {
//			cout << "There are  " << obj_it->second.size()
//					<< "  threads have shared obj:" << obj_it->first << endl;
//		}
//		//this level is for each shared object
//		if (obj_it->second.size() <= 1) {
//			if (verbose >= v_3) {
//				cout << "skip this obj because it only apperaed in one thread"
//						<< endl;
//			}
//			continue;//if a shared obj only appeared in one thread, then it's no need to care about this obj
//		}
//
//		for (map<int, map<int, bool> >::iterator thread_it_A =
//				obj_it->second.begin(); thread_it_A != obj_it->second.end();
//				thread_it_A++) {
//			//this level is for each thread that contains the current shared object
//			if (verbose >= v_3) {
//				cout << "There are  " << thread_it_A->second.size()
//						<< "  events of thread:  " << thread_it_A->first
//						<< "   at has obj: " << obj_it->first << endl;
//			}
//
//			for (map<int, bool>::iterator event_it_A =
//					thread_it_A->second.begin();
//					event_it_A != thread_it_A->second.end(); event_it_A++) {
//				//this level is for each event of the thread of the shared object
//
//				InspectEvent event_A = event_map[event_it_A->first];
//				if (verbose >= v_3) {
//
//					cout << "A:  " << event_A.toString() << endl;
//				}
//				/////////////////////B////////////////////////////
//				map<int, map<int, bool> >::iterator thread_it_B = thread_it_A;
//				for (thread_it_B++; thread_it_B != obj_it->second.end();
//						thread_it_B++) {
//					if (thread_it_B->first == thread_it_A->first) {
//						continue;
//					}
//
//					for (map<int, bool>::iterator event_it_B =
//							thread_it_B->second.begin();
//							event_it_B != thread_it_B->second.end();
//							event_it_B++) {
//						InspectEvent event_B = event_map[event_it_B->first];
//						if (!event_it_B->second && !event_it_A->second) {
//							continue;	//both read, skip
//						}
//						if (verbose >= v_2) {
//
//							cout << "A:  " << event_A.toString()
//									<< "        B:  " << event_B.toString()
//									<< endl;
//						}
//
//						int bigger, smaller;
//						if (event_it_A->first < event_it_B->first)//add edge according to the first run order
//								{
//							bigger = event_it_B->first;
//							smaller = event_it_A->first;
//
//						} else {
//							bigger = event_it_A->first;
//							smaller = event_it_B->first;
//
//						}
//
//////////if you want to get the equivlent trace of the first free run... then enable these code//////
////						while (trace_count < max_traces	//
////						&& graph.check_and_getValue()) {
////
////							cout << "check result:" << has_next_trace << endl;
////							vector<pair<int, int> > new_block_edges =
////									resort_event_order(obj_it->first);
////							if (verbose >= v_3) {
////								cout << "new_block_edges size:  "
////										<< new_block_edges.size() << endl;
////							}
////							graph.block_trace(new_block_edges, false);
////
////							cout << "number of traces: " << result_trace.size()
////									<< endl;
////							trace_count++;
////							value_map.clear();
////						}
//////////if you want to get the equivlent trace of the first free run... then enable these code//////
//
//
//						graph.addEdge(bigger, smaller, true);
//
//						if (trace_count < max_traces	//change to while to explore all partial order traces
//						&& graph.check_and_getValue()) {
//
//							cout << "check result:" << has_next_trace << endl;
//							vector<pair<int, int> > new_block_edges =
//									resort_event_order(obj_it->first);
//							if (verbose >= v_3) {
//								cout << "new_block_edges size:  "
//										<< new_block_edges.size() << endl;
//							}
//							graph.block_trace(new_block_edges, false);
//
//							cout << "number of traces: " << result_trace.size()
//									<< endl;
//							trace_count++;
//							value_map.clear();
//						}
//						graph.removeEdge(bigger, smaller);
//
//					}
//
//				}
//
//				////////////////////B//////////////////////////////
//
//			}
//
//		}
//
//	}

//	while (trace_count < max_traces && graph.check_and_getValue()) {
//
//		cout << "check result:" << has_next_trace << endl;
//		vector<pair<int, int> > new_block_edges = resort_event_order();
//		cout << "new_block_edges size:  " << new_block_edges.size() << endl;
//		graph.block_trace(new_block_edges, false);
//
//		cout << "number of traces: " << result_trace.size() << endl;
//		trace_count++;
//		value_map.clear();
//	}

//run_yices_replay = false;

	map<int, InspectEvent>::iterator it_A;
	map<int, InspectEvent>::iterator it_B;
	for (it_A = event_map.begin(); it_A != event_map.end(); it_A++) {
		InspectEvent event_A = it_A->second;
		it_B = it_A;
		it_B++;
		for (; it_B != event_map.end(); it_B++) {
			InspectEvent event_B = it_B->second;
			if (!event_A.dependent(event_B)
					|| event_A.thread_id == event_B.thread_id) {
				continue;
			}

			graph.addEdge(it_B->first, it_A->first, true);

			if (trace_count < max_traces //change to while to explore all partial order traces
			&& graph.check_and_getValue()) {
				cout << event_A.toString() << "      VS       "
						<< event_B.toString() << endl;

				//cout << "check result:" << has_next_trace << endl;
				vector<pair<int, int> > new_block_edges = resort_event_order();
				if (verbose >= v_3) {
					cout << "new_block_edges size:  " << new_block_edges.size()
							<< endl;
				}
				graph.block_trace(new_block_edges, false);

				cout << "number of traces: " << result_trace.size() << endl;
				trace_count++;
				value_map.clear();
			}
			graph.removeEdge(it_B->first, it_A->first);

		}

	}

	return;

}

string yices_path_computer_singleton::get_n_name(int name) {
	ostringstream ss;
	ss << "n" << name;
	return ss.str();

}

vector<pair<int, int> > yices_path_computer_singleton::resort_event_order() {
	vector<pair<int, int> > block_edges;

	cout
			<< "_______________yices_path_computer_singleton::resort_event_order()_________________"
			<< endl;

	map<int, InspectEvent> new_trace;

	cout << "a new trace:" << endl;

	map<int, int>::iterator it2;

	new_trace.clear();

	if (verbose >= v_3) {
		cout << "value_map size:  " << value_map.size() << endl;
		cout << "event_map size:  " << event_map.size() << endl;
		cout << "thread_event_count size:  " << thread_event_count.size()
				<< endl;
	}

	map<int, int>::iterator it3;
	map<int, int> last_events;

	int last_event = 0;

	for (it2 = value_map.begin(); it2 != value_map.end(); it2++) {
		if (verbose >= v_3) {
			cout << it2->first << "    " << it2->second << endl;
		}
	}

	for (it2 = value_map.begin(); it2 != value_map.end(); it2++) { //get a new trace in smt result's order and add precreate, thread_start,thread_end

		if (verbose >= v_3) {
			cout << "Raw event:" << it2->first << ":" << it2->second << "    "
					<< event_map[it2->second].toString() << endl;
		}

		if (last_event != 0 && event_map[last_event].thread_id!=event_map[it2->second].thread_id) {
			block_edges.push_back(pair<int, int>(last_event, it2->second));
			if (verbose >= v_3) {
				cout << "=====new block clause:" << last_event << "  to  "
						<< it2->second << endl;

				cout << "=====block size" << block_edges.size() << endl;
			}
		}

		if (event_map[it2->second].type == 24) { //thread_postcreate
			InspectEvent pre_create;
			pre_create.init();
			pre_create.thread_id = event_map[it2->second].thread_id;
			pre_create.type = string_to_event_type("thread_precreate");

			new_trace[new_trace.size() + 1] = pre_create;
			if (verbose >= v_3) {
				cout << endl << it2->first << ":" << it2->second << "    "
						<< pre_create.toString() << endl;

				cout << it2->first << ":" << it2->second << "    "
						<< event_map[it2->second].toString() << endl;
			}
			new_trace[new_trace.size() + 1] = event_map[it2->second];

			InspectEvent child_start;
			child_start.init();
			child_start.thread_id = event_map[it2->second].child_id;
			child_start.type = string_to_event_type("thread_start");
			if (verbose >= v_3) {
				cout << it2->first << ":" << it2->second << "    "
						<< child_start.toString() << endl << endl;
			}
			new_trace[new_trace.size() + 1] = child_start;

		} else if (event_map[it2->second].type == 25) { //meet thread join, add thread end before it
			InspectEvent thread_end; //declare an event
			thread_end.init(); //intialize the event
			thread_end.thread_id = event_map[it2->second].child_id; //define the thread id
			thread_end.type = string_to_event_type("thread_end"); //define the child id
			if (verbose >= v_3) {
				cout << endl << endl << it2->first << ":" << it2->second
						<< "    " << thread_end.toString() << endl;
			}
			new_trace[new_trace.size() + 1] = thread_end;
			if (verbose >= v_3) {
				cout << it2->first << ":" << it2->second << "    "
						<< event_map[it2->second].toString() << endl << endl;
			}
			new_trace[new_trace.size() + 1] = event_map[it2->second];

		} else {
			if (verbose >= v_3) {
				cout << it2->first << ":" << it2->second << "    "
						<< event_map[it2->second].toString() << endl;
			}
			new_trace[new_trace.size() + 1] = event_map[it2->second];
		}
		last_event = it2->second;

	}
	if (verbose >= v_2) {
		cout << "new_trace size=" << new_trace.size() << endl;
		cout << "trace to be replayed:  " << endl;
	}

	map<int, InspectEvent>::iterator it4;
	if (verbose >= v_2) {
		for (it4 = new_trace.begin(); it4 != new_trace.end(); it4++) {

//			if ((it4->second.type == 31 || it4->second.type == 32)
//					&& it4->second.obj_id == obj_id) {
//
//				cout << "---------------------------------------------"
//						<< it4->first << "  :  " << it4->second.toString()
//						<< endl;
//
//			} else {
			cout << it4->first << "  :  " << it4->second.toString() << endl;
//			}

		}
	}
	result_trace[result_trace.size() + 1] = new_trace;
	return block_edges;
}

//int result=0;
int yices_path_computer_singleton::add_op(int a) {
	result = result + a;
	cout << result << endl;
	return result;
}

int yices_path_computer_singleton::minus_op(int a) {
	result = result - a;
	cout << result << endl;
	return result;
}

void yices_path_computer_singleton::clean() {
	value_map.clear();
	event_map.clear();
	thread_event_count.clear();
	result_trace.clear();
}

yices_path_computer_singleton* yices_path_computer_singleton::m_Instance = NULL;

yices_path_computer_singleton* yices_path_computer_singleton::getInstance() {
	if (m_Instance) {
		return m_Instance;
	}
	m_Instance = new yices_path_computer_singleton;
	return m_Instance;
}
