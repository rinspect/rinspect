#include "clap_typest_trace.hh"
#include "clap_typest_check.hh"
#include "clap_typest_predict.hh"
#include "clap_typest_repair.hh"
#include "clap_pthread.hh"
extern pthread_mutex_t _ClapLock_m;
extern map<string, map<int, map<string, int> > >* clap_automaton; //map<object(class) name, map<from_state, map<event, to_state> > >
extern int verbose;
extern ProgramState *program_state;
extern map<int, int>* object_map_repair;
bool mutex = false;
extern map<int, TypestEvent*> spinning_events;
extern map<int, string> object_last_event;
extern int typ1_c;
extern int typ2_c;
//extern map<string, map<string, bool> > valid_functions;
int max_spin_times_1 = 999999;

extern pthread_mutex_t call_lock;

map<int, bool> avoid_nested_function;

int wait_time = 500;
int count_pre = 0;
int count_use = 0;

map<int, int> lock_cond_spin; //thread id, object id
TypestTrace::TypestTrace() {
	safe_curr_locksets();
	safe_curr_events();
	safe_OBJ_CALL_index();
	safe_curr_obj_call();
	safe_child_to_thread_create_ev();
	safe_child_to_thread_end_ev();
	safe_signals();
	safe_broadcasts();
	safe_attemp_times();
	safe_active_threads();
	safe_future_events();
	safe_object_map_repair();

}

TypestTrace::~TypestTrace() {

	(*child_to_thread_create_ev).clear();
	(*child_to_thread_end_ev).clear();
}

bool whether_write = true;
map<int, int>* attemp_times;
void safe_attemp_times() {
	if (attemp_times == NULL)
		attemp_times = new map<int, int>;
}

string split_by = " || ";

map<int, bool>* active_threads;
void safe_active_threads() {
	if (active_threads == NULL)
		active_threads = new map<int, bool>;
}
//safe_active_threads();
//void active_threads_add(int tid, bool status)
//{
//  if (active_threads == NULL)
//    active_threads = new map<int,bool>;
//  (*active_threads)[tid] = status;
//}
//void active_threads_remove(int tid)
//{
//  if (active_threads == NULL)
//    active_threads = new map<int,bool>;
//  (*active_threads).erase(tid);
//}

void TypestTrace::add_event(TypestEventType typ, int var, char* fname) {
//	if(!fname) {
//		cout<<"skip NULL"<<endl;
//		return;
//	}
//

//	TYPEST_PRINTs(fname, UOID(var));
////
////
//	cout<<"--------------------------------------- "<<endl;
//	cout<<"Call: "<<(string)fname<<endl;

//	cout<<"pre"<<endl;

//	if (typ == OBJ_CALL) {
//		bool skip_call = true;
//		if (!strncmp("zl", fname, 2)) {
////		TYPEST_PRINTs(fname, ptr);
////		etrace.add_event(OBJ_CALL, UOID(ptr), fname);
//			skip_call = false;
//		}
//
//		char * pch;
////		printf("Looking for the '(' character in \"%s\"...\n", fname);
//		pch = strchr(fname, '(');
////		while (pch != NULL) {
////			printf("found at %d\n", pch - fname + 1);
////			pch = strchr(pch + 1, '(');
////		}
//
//		if (pch != NULL) { //find the first ( in the function name
//			int index_lf = pch - fname + 1;
//			char subbuff[index_lf];
//			memcpy(subbuff, &fname[0], index_lf - 1);
//			subbuff[index_lf-1] = '\0';
//
//			cout << subbuff << endl;
//
//		}
//
//		if (skip_call)
//			return;
//	}

	bool whether_handle = false;

	static char *flag_str = getenv("CLAP_TYPEST_FLAG");
	if (flag_str == NULL || !strcmp(flag_str, "checker")) {
//		stringstream ss;
//		ofstream examplefile("events.txt", std::ios::out | std::ios::app);
//		if (typ == THREAD_START) { //read automaton
//			whether_handle = true;
//			int ThreadId = UTID_self();
//			if (ThreadId == 1) { //main thread
//				input_automaton("");
//				remove("events.txt");
//
//			}
//
//		} else if (typ == OBJ_CALL) {
//			//check the trace with the automatons dynamically
//
//			whether_handle = typest_check_handle_call(fname, var);
//			if (whether_handle == true) {
////				cout << "true" << endl;
//			} else {
////				cout << "false" << endl;
//			}
//		} else if (typ == THREAD_CREATE) {
//
//			whether_handle = true;
//
//		} else if (typ == THREAD_JOIN) {
//
//			whether_handle = true;
//
//		} else if (typ == COND_WAIT) {
//
//			whether_handle = true;
//
//		} else if (typ == COND_BROADCAST) {
//
//			whether_handle = true;
//
//		} else if (typ == COND_SIGNAL) {
//
//			whether_handle = true;
//
//		} else if (typ == MUTEX_LOCK) {
//
//			whether_handle = true;
//
//		} else if (typ == MUTEX_UNLOCK) {
//
//			whether_handle = true;
//
//		}
//
//		else if (typ == THREAD_END) {
//			whether_handle = true;
//			int ThreadId = UTID_self();
//			if (ThreadId == 1) { //main thread
//				//build the lattice and predict potential typestate errors
//
//			}
//
//		}
//		int tid = UTID_self();
//		if (whether_handle) {
//			ss.str("");
//			TypestEvent *ev = new TypestEvent(typ, tid, var);
//			update_clockvector(ev);
//			update_lockset(ev);
//
//			//
//			// predicting type-state violations
//
//			//if (false) {
//			if (typ == OBJ_CALL) {
//				//		if (true) {
//
//				if (fname != NULL) {
//					pair<string, string> class_function =
//							get_class_and_function((string) fname, fname);
//					assert(
//							!class_function.first.empty() && !class_function.second.empty() && "invalid fname");
//					ev->class_name = class_function.first;
//					ev->method_name = class_function.second;
//				}
//
//				if (typ == OBJ_CALL) {
//					if ((*OBJ_CALL_index).find(ev->thread_id)
//							!= (*OBJ_CALL_index).end()) {
//						(*OBJ_CALL_index)[ev->thread_id]++;
//
//					} else {
//						(*OBJ_CALL_index)[ev->thread_id] = 1;
//
//					}
//					ev->index_of_OBJ_CALL = (*OBJ_CALL_index)[ev->thread_id];
//				} else {
//					ev->index_of_OBJ_CALL = 0;
//				}
//				if (typ == OBJ_CALL) {
//					if ((*curr_obj_call).find(ev->thread_id)
//							!= (*curr_obj_call).end())			//exist prev
//							{
//						ev->prev_events[(*curr_obj_call)[ev->thread_id]] = 1;
//					} else {
//						ev->prev_events[0] = 1;
//					}
//					(*curr_obj_call)[ev->thread_id] = ev->eid;
//				}
//
//				ss << "------------" << ev->toString() << endl;
//				ss << ",";
//
//				ss << "clockvec-------------------------------------------"
//						<< ev->clockvec.toString() << endl;
//				cout << ss.str();
//
//				if (whether_write) {
//					if (examplefile.is_open()) {
//
//						examplefile << ev->toString() << split_by;
//						examplefile << ev->clockvec.toString() << split_by;
//						examplefile << ev->lockset.toString() << split_by;
//						examplefile << ev->prev_to_string() << endl;
//
//					}
//				}
//
//				//
//				//			if (ev->lockset.locks.size() > 0) {
//				//				cout << "lockset--------------------------------------------"
//				//						<< ev->lockset.toString() << endl;
//				//			}
//
//				//events.push_back(ev);
//				predict_handle_call(ev);
//
//			} else if (typ == THREAD_END && tid == 1)	//end of the execution
//					{
//				TypestEvent *ev = new TypestEvent(typ, tid, var);
//				//			cout << "------------" << ev->toString() << endl;
//				predict_handle_call(ev);
//			}
//
//			//print_statistics();
//		}
//		examplefile.close();
//		//return;
	}

	/**********************************************************************
	 * **********************************************************************
	 * **********************************************************************
	 * **********************************************************************
	 * **********************************************************************
	 * **********************************************************************
	 * **********************************************************************
	 * **********************************************************************
	 * ******************************repair**********************************
	 * **********************************************************************
	 * **********************************************************************
	 * **********************************************************************
	 * **********************************************************************
	 * **********************************************************************
	 * **********************************************************************
	 * **********************************************************************
	 *********************************************************************/
	else if (flag_str == NULL || !strcmp(flag_str, "repair")) {

		int ThreadId = UTID_self();

		if (typ == THREAD_START) { //read automaton
			whether_handle = true;

			if (verbose >= 2)
				cout << "(start)Thread " << ThreadId << " is active now"
						<< endl;
			if (ThreadId == 1) { //main thread
				input_automaton("");
				read_events();

			}
			(*active_threads)[ThreadId] = true;

		} else if (typ == OBJ_CALL) {

			whether_handle = true;
//			whether_handle = typest_check_handle_call(fname, var);

		} else if (typ == THREAD_CREATE) {

			(*active_threads)[var] = true;

			if (verbose >= 2)
				cout << "(create)Thread " << var << " is active now" << endl;
			whether_handle = true;

		} else if (typ == THREAD_JOIN) {

			(*active_threads).erase(var);

			if (verbose >= 2)
				cout << "(join)Thread " << var << " is not active now" << endl;

			whether_handle = true;

		} else if (typ == MUTEX_LOCK) {

			whether_handle = true;

		} else if (typ == MUTEX_UNLOCK) {

			whether_handle = true;

		} else if (typ == MUTEX_INIT) {

			whether_handle = true;

		} else if (typ == MUTEX_DESTROY) {

			whether_handle = true;
		}

		else if (typ == THREAD_END) {

			whether_handle = true;

			(*active_threads).erase(ThreadId);

			if (verbose >= 2) {
				cout << "(end)Thread " << ThreadId << " is not active now"
						<< endl;

			}
			if (ThreadId == 1) { //main thread
				//build the lattice and predict potential typestate errors
//				if (verbose >= 1)
//					cout << "Congratulations, this is a correct run!" << endl;
				cout << "type 1 violation count: " << typ1_c << endl;
				cout << "type 2 violation count: " << typ2_c << endl;

			}

		}

		TypestEvent *ev;
		pair<string, string> class_function;

		if (whether_handle) {

			ev = new TypestEvent(typ, ThreadId, var);

			ev->index_of_OBJ_CALL = 0;
//
//			if (mutex) {
////				mutex = true;
//				//				cout << "deal with mutex" << endl;
//				if (typ == MUTEX_LOCK) {
//					ev->type = OBJ_CALL;
//					ev->class_name = "pthread_mutex_t";
//					ev->method_name = "mutex_lock";
//
//				} else if (typ == MUTEX_UNLOCK) {
//					ev->type = OBJ_CALL;
//					ev->class_name = "pthread_mutex_t";
//					ev->method_name = "mutex_unlock";
//
//				} else if (typ == MUTEX_INIT) {
//					ev->type = OBJ_CALL;
//					ev->class_name = "pthread_mutex_t";
//					ev->method_name = "mutex_init";
//
//				} else if (typ == MUTEX_DESTROY) {
//					ev->type = OBJ_CALL;
//					ev->class_name = "pthread_mutex_t";
//					ev->method_name = "mutex_destroy";
//
//				}
//
//			}

			if (typ == OBJ_CALL) {
				//		if (true) {

				if (fname != NULL) {
					class_function = get_class_and_function((string) fname,
							fname);
					assert(
							!class_function.first.empty() && !class_function.second.empty() && "invalid fname");

					if (class_function.first.compare("zl_skip_function") == 0//no :: found in the fname
					&& class_function.second.compare("zl_skip_function") == 0)
						return;

					ev->class_name = class_function.first;
					ev->method_name = class_function.second;
				}

			}
		}

		if (ev->type == OBJ_CALL) {


//			avoid_nested_function[ThreadId]=true;

//			cout << (ev->toString()) << "-----------------is trying to execute" << endl;

			//here might need mutual exclusion
//				if(max_spin_times_1<=0) return;
			while ((typ == OBJ_CALL || ev->type == OBJ_CALL) && whether_spin(ev)) {
//					break;

				if (max_spin_times_1 <= 0)
					break;

//					usleep(10000);
//					safe_attemp_times();
				if ((*attemp_times).find(ev->eid) == (*attemp_times).end()) {
					(*attemp_times)[ev->eid] = 1;
				} else {
					(*attemp_times)[ev->eid]++;
				}
				if (verbose >= 1 && (*attemp_times)[ev->eid] % 100000 == 1) {
					cout << (ev->toString()) << (ev->clockvec.toString())
							<< (ev->lockset.toString()) << endl;
					cout << "----need to spin";
					cout << ".  attemp times: " << (*attemp_times)[ev->eid]
							<< endl;
				}

//					assert(should_abort()==false && "should abort");
//					if (typ == MUTEX_DESTROY) {
//						if (verbose >= 1
//								&& (*attemp_times)[ev->eid]
//										>= max_spin_times_1) {
//							cout << (ev->toString())
//									<< (ev->clockvec.toString())
//									<< (ev->lockset.toString()) << endl;
//							cout << ".  attemp times reaches max" << endl;
//							break;
//						}
//					} else {
				if ((*attemp_times)[ev->eid] >= max_spin_times_1) {
					cout << (ev->toString()) << (ev->clockvec.toString())
							<< (ev->lockset.toString()) << endl;
					cout << ".  attemp times reaches max" << endl;
					break;
				}
//					}
//
//					if (typ == MUTEX_LOCK) {
////						cout<<"lock"<<endl;
//
//					}
//				if (should_abort()) {
//					cout << "all threads are spinning now" << endl;
//				} else {
//					cout << "not all threads are spinning now" << endl;
//				}




#if !ATOMIC_CALL
				pthread_mutex_unlock(&_ClapLock_m);
#endif

#if ATOMIC_CALL
	pthread_mutex_unlock(&call_lock);
#endif




//					usleep(wait_time*(rand() % 50 + 1));
//					usleep(wait_time);
//					sleep(1);
				usleep(200);	//sleep for the thread

#if !ATOMIC_CALL
				pthread_mutex_lock(&_ClapLock_m);
#endif

#if ATOMIC_CALL
	pthread_mutex_lock(&call_lock);
#endif


			}
			spinning_events.erase(ThreadId);
			(*active_threads)[ThreadId] = true;
//			if ((*clap_automaton).find("pthread_mutex_t")
//					!= (*clap_automaton).end()) {
//				if (typ == MUTEX_DESTROY) {
//					(*object_map_repair).erase(var);
////						object_last_event.erase(var);
//					//					 cout<< (*object_map_repair).size()<<endl;
//
//				}
//			}
		}

		delete ev;

//		if (verbose >= 3)
//			program_state = program_state->createState(ev);

//			cout << (ev->toString()) << (ev->clockvec.toString())
//								<< (ev->lockset.toString()) <<"-----------------success to execute"<< endl;
//		if (verbose >= 3)
//			cout << endl;

	}
//	usleep(1000);

}

//void TypestTrace::add_event_to_trace(TypestEventType typ, int var,
//		char* fname) {
//	int tid = UTID_self();
//	TypestEvent *ev = new TypestEvent(typ, tid, var);
//	update_clockvector(ev);
//	update_lockset(ev);
//	events.push_back(ev);
//
//	// predicting type-state violations
//	if (fname != NULL) {
//		ev->method_name = fname;
//	}
//	predict_handle_call(ev);
//	print_statistics();
//
//}

void TypestTrace::update_clockvector(TypestEvent* ev) {
	safe_curr_events();
	safe_OBJ_CALL_index();
	safe_child_to_thread_create_ev();
	safe_child_to_thread_end_ev();
	safe_signals();
	safe_broadcasts();
	switch (ev->type) {
	case THREAD_CREATE: { // prepare to update the child's THREAD_START event
		(*child_to_thread_create_ev)[ev->child_id] = ev;
		break;
	}
	case THREAD_START: { // update based on its parent's THREAD_CREATE event

		if ((*child_to_thread_create_ev).find(ev->thread_id)
				!= (*child_to_thread_create_ev).end()) {
			TypestEvent* parent_ev = (*child_to_thread_create_ev)[ev->thread_id];
			ev->clockvec.merge(parent_ev->clockvec);

		} else if (ev->thread_id == 1) {

			assert("main thread doesn't have parent");
		}
		ev->clockvec.clocks[ev->thread_id] = 0;

		(*curr_events)[ev->thread_id] = ev;
		(*OBJ_CALL_index)[ev->thread_id] = 0;

		return;
	}
	case THREAD_END: { // prepare to update the parent's THREAD_JOIN event
		(*child_to_thread_end_ev)[ev->thread_id] = ev;
		ev->clockvec.clocks = (*curr_events)[ev->thread_id]->clockvec.clocks;

		(*curr_events)[ev->thread_id] = ev;
		return;

	}
	case THREAD_JOIN: { // update based on its child's THREAD_END event
		if ((*child_to_thread_end_ev).find(ev->child_id)
				!= (*child_to_thread_end_ev).end()) {
			TypestEvent* child_ev = (*child_to_thread_end_ev)[ev->child_id];
			ev->clockvec.merge(child_ev->clockvec);

//			ev->clockvec.clocks[child_ev->thread_id]++;
		} else {
			assert( 0 && "every join should have a corresponding child thread");
		}
		break;
	}

	case COND_WAIT: {

		//cout << "deal with wait: condition: " << ev->cond_id << endl;
		if ((*broadcasts).find(ev->cond_id) != (*broadcasts).end()) {
			TypestEvent* broadcast = (*broadcasts)[ev->cond_id];
			ev->clockvec.merge(broadcast->clockvec);

//			ev->clockvec.clocks[broadcast->thread_id]++;

//			cout<<"waiting for: "<<ev->cond_id<<" appear in:" <<endl;
//			cout<<ev->toString()<<endl;
//			cout<<"signal: "<<ev->cond_id<<" appear in:" <<endl;
//			cout<<signals[ev->cond_id]->toString()<<endl<<endl;

		}

		else if ((*signals).find(ev->cond_id) != (*signals).end()) {
			TypestEvent* signal = (*signals)[ev->cond_id];
			ev->clockvec.merge(signal->clockvec);

//			ev->clockvec.clocks[signal->thread_id]++;
			(*signals).erase(ev->cond_id);
//			cout<<"waiting for: "<<ev->cond_id<<" appear in:" <<endl;
//			cout<<ev->toString()<<endl;
//			cout<<"signal: "<<ev->cond_id<<" appear in:" <<endl;
//			cout<<signals[ev->cond_id]->toString()<<endl<<endl;

		} else {
			cout << "there is no corresponding signal or broadcasts" << endl;
		}

		break;
	}
	case COND_SIGNAL: {
		//cout << "deal with signal condition: :" << ev->cond_id << endl;

		(*signals)[ev->cond_id] = ev;

		break;
	}

	case COND_BROADCAST: {
		//cout << "deal with signal condition: :" << ev->cond_id << endl;

		(*broadcasts)[ev->cond_id] = ev;

		break;
	}

	case OBJ_CALL: {
		ev->clockvec.merge((*curr_events)[ev->thread_id]->clockvec);
		ev->clockvec.clocks[ev->thread_id]++;

		break;

	}

	default:
		break;
	}
	ev->clockvec.merge((*curr_events)[ev->thread_id]->clockvec);

//	ev->clockvec.clocks[ev->thread_id]++;
	(*curr_events)[ev->thread_id] = ev;

}

void TypestTrace::update_lockset(TypestEvent* ev) {
	safe_curr_locksets();
	if ((*curr_locksets).find(ev->thread_id) == (*curr_locksets).end()) {
		LockSet emptyls;
		(*curr_locksets)[ev->thread_id] = emptyls;
	}

	LockSet& curr_lockset = (*curr_locksets)[ev->thread_id];

	ev->lockset = curr_lockset;
	switch (ev->type) {
	case MUTEX_LOCK:
		curr_lockset.insert(ev->mutex_id);
		break;
	case MUTEX_UNLOCK:
		curr_lockset.erase(ev->mutex_id);
		break;
	default:
		break;
	}

}

void TypestTrace::dump() {
	string default_console = "\033[0m";

	cout << "--------------------TypestTrace::dump()-------------------\n";
	{
		vector<TypestEvent*>::iterator it;
		for (it = events.begin(); it != events.end(); it++) {
			TypestEvent* ev = (*it);

			string color = "\033[0;";
			switch (ev->type) {
			case OBJ_WRITE:
				color = "\033[1;";
				break;
			case OBJ_READ:
				color = "\033[1;";
				break;
			case OBJ_CALL:
				color = "\033[1;";
				break;
			case MUTEX_LOCK:
				color = "\033[1;";
				break;
			case MUTEX_UNLOCK:
				color = "\033[1;";
				break;
			default:
				color = "\033[0;";
				break;
			}

			switch (ev->thread_id) {
			case 101:
				color += "32m";
				break;
			case 201:
				color += "33m";
				break;
			case 301:
				color += "34m";
				break;
			case 401:
				color += "35m";
				break;
			case 501:
				color += "36m";
				break;
			case 601:
				color += "37m";
				break;
			case 701:
				color += "38m";
				break;
			case 801:
				color += "39m";
				break;
			default:
				color += "37m";
				break;
			}

			cout << color << ev->toString() << endl;

		}
		cout << default_console << endl;
	}

	cout << "--------------------------------------------------------\n";
	print_statistics();
}

void TypestTrace::print_statistics() {
	int n_threads = 0;
	int n_locks = 0;
	int n_conds = 0;
	int n_objs = 0;
	int n_evs = events.size();
	int n_lock_ev = 0;
	int n_unlock_ev = 0;
	int n_signal_ev = 0;
	int n_wait_ev = 0;
	int n_read_ev = 0;
	int n_write_ev = 0;
	int n_call_ev = 0;

	for (vector<TypestEvent*>::iterator it = events.begin(); it != events.end();
			it++) {
		TypestEvent* ev = (*it);
		switch (ev->type) {
		case THREAD_START:
			n_threads++;
		case MUTEX_INIT:
			n_locks++;
		case COND_INIT:
			n_conds++;
		case OBJ_REGISTER:
			n_objs++;
		case MUTEX_LOCK:
			n_lock_ev++;
			break;
		case MUTEX_UNLOCK:
			n_unlock_ev++;
			break;
		case COND_SIGNAL:
			n_signal_ev++;
			break;
		case COND_WAIT:
			n_wait_ev++;
			break;
		case OBJ_READ:
			n_read_ev++;
			break;
		case OBJ_WRITE:
			n_write_ev++;
			break;
		case OBJ_CALL:
			n_call_ev++;
			break;
		default:
			break;
		}
	}

	cout << " @@ " << " threads= " << n_threads << " locks= " << n_locks
			<< " conds= " << n_conds << " objs= " << n_objs << " evs= " << n_evs
			<< " lock_evs= " << (n_lock_ev + n_unlock_ev) << " cond_evs= "
			<< (n_signal_ev + n_wait_ev) << " obj_evs = "
			<< (n_read_ev + n_write_ev) << " read_evs= " << n_read_ev
			<< " write_evs= " << n_write_ev << " call_evs= " << n_write_ev
			<< endl;
}
//map<int, LockSet> curr_locksets;
void TypestTrace::safe_curr_locksets() {
	if (curr_locksets == NULL) {
		curr_locksets = new map<int, LockSet>;
	}
}

//map<int, TypestEvent*> curr_events; //any type of event
void TypestTrace::safe_curr_events() {
	if (curr_events == NULL) {
		curr_events = new map<int, TypestEvent*>;
	}
}

//map<int, int> OBJ_CALL_index; //map<thread id, number of OBJ_CALL>
void TypestTrace::safe_OBJ_CALL_index() {
	if (OBJ_CALL_index == NULL) {
		OBJ_CALL_index = new map<int, int>;
	}
}

//map<int, int> curr_obj_call; //only obj_call, thread_id, eid
void TypestTrace::safe_curr_obj_call() {
	if (curr_obj_call == NULL) {
		curr_obj_call = new map<int, int>;
	}
}

// temporary storage; used in 'update_clockvector()'
//map<int, TypestEvent*> child_to_thread_create_ev;
void TypestTrace::safe_child_to_thread_create_ev() {
	if (child_to_thread_create_ev == NULL) {
		child_to_thread_create_ev = new map<int, TypestEvent*>;
	}
}

//map<int, TypestEvent*> child_to_thread_end_ev;
void TypestTrace::safe_child_to_thread_end_ev() {
	if (child_to_thread_end_ev == NULL) {
		child_to_thread_end_ev = new map<int, TypestEvent*>;
	}
}

//map<int, TypestEvent*> signals; //map<condition id, event>
void TypestTrace::safe_signals() {
	if (signals == NULL) {
		signals = new map<int, TypestEvent*>;
	}
}

//map<int, TypestEvent*> broadcasts; //map<condition id, event>
void TypestTrace::safe_broadcasts() {
	if (broadcasts == NULL) {
		broadcasts = new map<int, TypestEvent*>;
	}
}
