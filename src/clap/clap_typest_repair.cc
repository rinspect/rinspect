#include "clap_typest_repair.hh"
int verbose = 0;
extern string split_by;
extern map<int, bool>* active_threads;
map<int, int>* object_map_repair;
extern map<string, map<int, map<string, int> > >* clap_automaton; //map<object(class) name, map<from_state, map<event, to_state> > >

extern map<string, map<string, bool> > valid_functions;

map<string, map<string, vector<string> > >* future_events; //map<class, map<function,vector<function> > >
map<int, bool>::iterator it_active_thread;
int typ1_c = 0;
int typ2_c = 0;
bool violation_2 = true;

void safe_object_map_repair() {
	if (object_map_repair == NULL)
		object_map_repair = new map<int, int>;
}

void safe_future_events() {
	if (future_events == NULL)
		future_events = new map<string, map<string, vector<string> > >;
}

void typest_repair_handle_call(char* fname, int object_id) {
	//1: read automatons
	//2: read the events of each thread
	//3:

	//assert(0 && "NOT YET IMPLEMENTED");
}

//void check_map_int_TypestEvent(map<int, TypestEvent*>* map) {
//	if (map == NULL)
//		()map = new map<int, TypestEvent*>;
//}
//void check_map_int_int(map<int, int>* map) {
//	if (map == NULL)
//		map = new map<int, int>;
//}
//void check_map_int_bool(map<int, bool>* map) {
//	if (map == NULL)
//		map = new map<int, bool>;
//}

string trim(string s) {
	string::iterator new_end = remove_if(s.begin(), s.end(),
			bind2nd(equal_to<char>(), ' '));
	s.erase(new_end, s.end());
	return s;
}

string remove_head_and_tail(string s) {
	int remove_length = 1;
	if ((int) s.length() < (int) (remove_length * 2))
		return s;
	else {
		s = s.substr(1, s.length() - 2);
	}
	return s;

}

void read_events() {
	safe_future_events();

//	static map<string, map<string,vector<string> > > future_events;//map<class, map<function,vector<function> > >
	vector<string> events = read_file("events.txt");
//	cout << events.size() << endl;
	string event;
	vector<string> elements;
	string from_event;
	string to_events;
	vector<string> to_events_split;
	string class_name_from;
	string function_name_from;
	string class_name_to;
	string function_name_to;
	string item;
	for (vector<string>::iterator it_event = events.begin();
			it_event != events.end(); it_event++) {
		event = (string) *it_event;
		if (event.size() < 1)
			continue;
		cout << event << endl;
		elements = split_string(event, "->");
//		for (vector<string>::iterator it_element = elements.begin();
//				it_element != elements.end(); it_element++) {
//			string element=(string)* it_element;
//			cout << element << endl;
//
//		}
		from_event = elements[0];
		to_events = elements[1];
		to_events = remove_head_and_tail(to_events);
//		to_events = trim(to_events);
//		cout << from_event << endl;
//		cout << to_events << endl;
		if (from_event.compare("0") == 0) {
//			cout << "initial" << endl;
			class_name_from = "0";
			function_name_from = "0";
		} else {
			int found = from_event.rfind("::");

//			to_events_split = split_string(from_event, "::");
			assert(found>0);

			class_name_from = from_event.substr(0, found);

			function_name_from = from_event.substr(found + 2,
					from_event.length() - found - 2);

//			class_name_from = to_events_split[0];
//			function_name_from = to_events_split[1];
		}
		to_events_split = split_string(to_events, ",,");
		for (vector<string>::iterator it_to_events = to_events_split.begin();
				it_to_events != to_events_split.end(); it_to_events++) {
			item = (string) *it_to_events;

			int found = item.rfind("::");

			//			to_events_split = split_string(from_event, "::");
			assert(found>0);

			class_name_to = item.substr(0, found);

			function_name_to = item.substr(found + 2,
					item.length() - found - 2);

//
//			class_name_to = split_string(item, "::")[0];
//			function_name_to = split_string(item, "::")[1];
//			cout << "class_name_to: " << class_name_to << endl;
//			cout << "function_name_to: " << function_name_to << endl;
			(*future_events)[class_name_to][function_name_from].push_back(
					function_name_to);
//			cout<<"a"<<endl;
		}

	}

	cout << "events of threads are all read in from events.txt" << endl;
	for (map<string, map<string, vector<string> > >::iterator it1 =
			(*future_events).begin(); it1 != (*future_events).end(); it1++) {
		cout << "class name: " << it1->first << endl;
		for (map<string, vector<string> >::iterator it2 = it1->second.begin();
				it2 != it1->second.end(); it2++) {
			cout << it2->first << " -> { ";
			for (vector<string>::iterator it3 = it2->second.begin();
					it3 != it2->second.end(); it3++) {
				cout << (string) *it3 << " , ";
			}
			cout << " }" << endl;

		}

	}

}

//map<string,bool> a;
//void DFS_events(string root, string start_point)
//{
//
//}

extern map<string, map<int, map<string, int> > > state_potential_events;
extern map<int, int>* attemp_times;

string initial = "0";
map<int, TypestEvent*> spinning_events;
map<int, map<int, string> > object_last_event;
bool whether_spin(TypestEvent* e) {	//true means the thread should hang up
//return false;
	if (verbose >= 2)
		cout
				<< "--------------------------------------------------------------------------------------------------------------------------------"
				<< endl;

	if (verbose >= 2)
		cout << (e->toString()) << (e->clockvec.toString())
				<< (e->lockset.toString()) << endl << "----is trying to execute"
				<< endl;

//	if (verbose >= 3)
//		program_state->dump();
//	safe_future_events();
//	if ((*future_events).find(e->class_name) == (*future_events).end())
//		return false;//if the class of the event is not considered,return false;

	if (valid_functions.find(e->class_name) == valid_functions.end()
			|| valid_functions[e->class_name].find(e->method_name)
					== valid_functions[e->class_name].end())
		return false;

//	if (!program_state->isNextState(e))//if illegal transition(might happen after program state is changed)
//	{
//		if(e->class_name!="pthread_mutex_t" && !program_state->isLocked(e))
//		return true;
//	}
		int curr_state = 0;
	int next_state = -1;
	int obj_id = e->obj_id;
//	safe_object_map_repair();
	if ((*object_map_repair).find(obj_id) == (*object_map_repair).end()) {
		(*object_map_repair)[obj_id] = 0;
	}
	curr_state = (*object_map_repair)[obj_id];

	if (verbose >= 2)
		cout << "function call: " << e->method_name << "  curr state : "
				<< obj_id << "  is " << curr_state;

	next_state = check(e->class_name, curr_state, e->method_name);

	if (verbose >= 2)
		cout << "   next state : " << obj_id << "  is " << next_state << endl;

	if (next_state == -1) {
		typ1_c++;
		if (verbose >= 2)
			cout << "             type1: ~~automaton violation" << endl;
		(*active_threads)[e->thread_id] = false;
		spinning_events[e->thread_id] = e;
		return true;
	}

	assert(next_state!=-1 && "type_state violation");

	if (violation_2) {

		string last_event = "0";
		if (object_last_event.find(obj_id) != object_last_event.end()) {
			if (object_last_event[obj_id].find(e->thread_id)
					!= object_last_event[obj_id].end())
				last_event = object_last_event[obj_id][e->thread_id];
		}
		if (verbose >= 2)
			cout << "last event of object: " << obj_id << " is: " << last_event
					<< endl;
//	cout<<active_threads.size()<<thread_not_spinning.size()<<endl;

		for (it_active_thread = (*active_threads).begin();
				it_active_thread != (*active_threads).end();
				it_active_thread++) {

			if (e->thread_id == it_active_thread->first) {	//self, count++
				continue;
				if (verbose >= 2)
					cout << "it_active_thread->first: "
							<< it_active_thread->first << endl;
			} else {
//			return false;
//			if (_output)
//				cout << "other thread id: " << it_active_thread->first << endl;
//			if (thread_not_spinning.find(it_active_thread->first)
//					!= thread_not_spinning.end()) {
//				cout << "true" << endl;
//
//			} else
//				cout << "false" << endl;

				if ((*active_threads)[it_active_thread->first] == true)	//not spinning, need to deal with all possible events
						{
//				return false;
//				continue;
					if (verbose >= 2)
						cout << "other thread id: " << it_active_thread->first
								<< " is not spinning" << endl;
					int violation = false;
					string last_event_2 = "0";
					if (object_last_event.find(obj_id)
							!= object_last_event.end()) {

						if (object_last_event[obj_id].find(
								it_active_thread->first)
								!= object_last_event[obj_id].end())
							last_event_2 =
									object_last_event[obj_id][it_active_thread->first];
					}

					if (verbose >= 2) {
						cout << "last event: " << last_event_2 << endl;
					}
					for (vector<string>::iterator it_future_events =
							(*future_events)[e->class_name][last_event_2].begin();
							it_future_events
									!= (*future_events)[e->class_name][last_event_2].end();
							it_future_events++) {
						string future_event = (string) *it_future_events;
						if (verbose >= 2)
							cout << "future event: " << future_event << endl;

						if (state_potential_events[e->class_name][next_state].find(
								future_event)
								== state_potential_events[e->class_name][next_state].end()) {
//						cout<<state_potential_events[e->class_name][next_state].size()<<endl;
//						if (_output)
							if (verbose >= 2)
								cout << "             type2: ~~violation"
										<< endl;
							(*active_threads)[e->thread_id] = false;
							spinning_events[e->thread_id] = e;
							violation = true;
//						return true;
						}

					}
					if (violation == true) {
						typ2_c++;
						return true;
					}
				} else	//spinning, deal with the already-spinning event
				{
//				continue;
//				return false;
					if (verbose >= 2)
						cout << "other thread id: " << it_active_thread->first
								<< " is spinning" << endl;

					TypestEvent* other =
							spinning_events[it_active_thread->first];

					if (verbose >= 2)
//					cout << "other: " << other->toString()
//							<< other->clockvec.toString()
//							<< other->lockset.toString() << " " << endl;
						cout << "other: " << other->toString() << endl;

					string other_classname = other->class_name;
					string other_function = other->method_name;

					if (other->obj_id != e->obj_id
							|| other_classname.compare(e->class_name) != 0) {
						if (verbose >= 3)
							cout << "they are not working on the same object"
									<< endl;
						continue;//if not on the same object or not the same class
					}
					//			if (!e->lockset.intersectIsEmpty(other->lockset)) {
					//
					if (state_potential_events[e->class_name][next_state].find(
							other_function)
							== state_potential_events[e->class_name][next_state].end()) {//other's event is not in the PE of the next state
						spinning_events[e->thread_id] = e;
						(*active_threads)[e->thread_id] = false;
//					if (_output)
						if (verbose >= 2)
							cout << "-----------------------type3 :is blocked"
									<< endl;
						typ2_c++;
						return true;

					} else {
						if (verbose >= 2)
							cout << "-----------------------:is not blocked"
									<< endl;
					}

				}

			}
		}
	}
//	return false;
//	(*active_threads)[e->thread_id] = true;
	if (verbose >= 3)
		update_info(e);
	object_last_event[obj_id][e->thread_id] = e->method_name;
//	return false;
	(*object_map_repair)[obj_id] = next_state;

//	cout<<(*object_map_repair).size()<<"   "<<object_last_event.size()<<endl;
//	return false;
	//	cout << e->eid << endl;
	if (verbose >= 2)
		cout << (e->toString()) << (e->clockvec.toString())
				<< (e->lockset.toString()) << endl;
	if (verbose >= 2)
		cout << "----success to execute";
//	safe_attemp_times();
	if ((*attemp_times).find(e->eid) == (*attemp_times).end()) {
		(*attemp_times)[e->eid] = 1;
	} else {
		(*attemp_times)[e->eid]++;
	}

	if (verbose >= 2)
		cout << ".  attemp times: " << (*attemp_times)[e->eid] << endl;

	return false;
}

void update_info(TypestEvent* e) {
	if (e->index_of_OBJ_CALL > 0) {
		if (verbose >= 3)
			program_state->clockvec.clocks[e->thread_id] = e->index_of_OBJ_CALL;
		if (verbose >= 3)
			cout << "thread: " << e->thread_id << " reach step: "
					<< e->index_of_OBJ_CALL << endl;
//		if (thread_not_spinning.find(e->thread_id)
//				== thread_not_spinning.end()) {
//			thread_not_spinning[e->thread_id] = true;
//		}
	}

}

bool should_abort() {//whether the program should abort: no correct interleavings from now on
//	static map<int,bool> thread_status;//whether a thread is hanging
//	safe_active_threads();
	for (map<int, bool>::iterator it_active_thread = (*active_threads).begin();
			it_active_thread != (*active_threads).end(); it_active_thread++) {
		if (it_active_thread->second == true) {
			return false;
		}

	}

	return true;

}

ProgramState * update_program_state(ProgramState * ps, TypestEvent* e) {

//not implemented yet
	if (ps->isNextState(e)) {

	}

	return ps;
}

