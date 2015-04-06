#include "clap_typest_predict.hh"
#include "clap_typest_trace.hh"
#include "clap_typest_check.hh"

#define MAX_NUM_NEXT_LEVEL_STATES   (2<<30)
#define MAX_NUM_EVENTS_IN_QUEUE     (2<<30)

TypestEventQueue Q;
int level_num = 0;
map<string, ProgramState *> existing_states;

//Implementing the predictive typestate checking algorithm of the ASE2008 paper
void TypestTrace::predict_handle_call(TypestEvent* ev) {
	// a new event of type OBJ_CALL is generated for each method invocation.
	if (ev->type == THREAD_END && ev->thread_id == 1) {
		while (Q.constructLevel())
			;

	} else if (ev->type == OBJ_CALL) {
		Q.enqueue(ev);
	}
	//Q.dump();

//  cout << "------------" << ev->toString() << endl;

//  else if (ev->type==OBJ_CALL)
//  {
//	  cout<<"call"<<endl;
//  }

//  while (Q.constructLevel()) ;
}

bool TypestEventQueue::constructLevel() {

	cout << "**********************************" << "curr level: " << level_num
			<< "  level size: " << CurrLevel.size()
			<< "**********************************" << endl;

	map<int, map<int, TypestEvent*> >::iterator it;
	for (it = events_by_thread.begin(); it != events_by_thread.end(); it++) {
//		cout<<"size: of thread: "<<it->second.size()<<endl;
		set<ProgramState*>::iterator cit;
		int index_of_state = 0;
		for (cit = CurrLevel.begin(); cit != CurrLevel.end(); cit++) {
			index_of_state++;
			ProgramState *Sigma = (*cit);
//			cout << Sigma->clockvec_index.toString()
//												<< "  TID: "<< endl;

			int index = Sigma->clockvec.clocks[it->first]; //in which step of the thread

			if (index == (int) it->second.size())
				continue;

			TypestEvent* ev = it->second[index + 1];

			//cout<<ev->toString()<<endl;
			if (Sigma->isNextState(ev)) {
//			if (true) {
//				cout << "true" << endl;

//				cout << Sigma->clockvec_index.toString()
//						<< "  TID: "<<ev->thread_id<<"  index: "<<ev->index_of_OBJ_CALL << endl;

				cout << "curr level: " << level_num << "  state: "
						<< index_of_state;
				cout << "    Sigma: " << Sigma->clockvec.toString() << "  ->  "
						<< ev->clockvec.toString() << endl;
				cout << ev->toString() << ev->lockset.toString() << endl
						<< endl;

				Sigma->dump();

				if (Sigma->isLocked(ev)) {
					continue;
				}

				ProgramState *Sigma2 = Sigma->createState(ev);

				if (!Sigma2->updateAutomatons(ev)) {
					continue;
				}

				Sigma2->dump();

				cout << endl;
				if (existing_states.find(Sigma2->clockvec.toString())
						== existing_states.end()) {
					NextLevel.insert(Sigma2);
					existing_states[Sigma2->clockvec.toString()] = Sigma2;
					cout << "---------------this is a new state" << endl
							<< endl;
				} else {
					cout << "---------------this is an existing state" << endl
							<< endl;
					existing_states[Sigma2->clockvec.toString()]->merge_automatons(
							Sigma2);

				}
			} else {

//				cout<<"false"<<endl;
			}
		}
	}			//curr_level complete
	cout << "**********************************" << "next level: "
			<< level_num + 1 << "  level size: " << NextLevel.size()
			<< "**********************************" << endl << endl << endl;
	CurrLevel = NextLevel;
	NextLevel.clear();
	level_num++;

//  // for each e \in Q do
//  vector<TypestEvent*>::iterator eit;
//  for (eit = events.begin(); eit != events.end(); eit++) {
//    TypestEvent* e = (*eit);
//    // if \Sigma \in CurrLevel and isNextState(\Sigma,e) then
//    set<ProgramState*>::iterator cit;
//    for (cit = CurrLevel.begin(); cit != CurrLevel.end(); cit++) {
//      ProgramState *Sigma = (*cit);
//      if (Sigma->isNextState(e)) {
//        // NextLevel := NextLevel + createState(\Sigma,e)
//        ProgramState *Sigma2 = Sigma->createState(e);
//        NextLevel.insert(Sigma2);
//        // if isLevelComplete(NextLevel,e,Q) then
//        if (isLevelComplete(e)) {
//          res = true;
//          break;
//        }
//      }
//    }
//    if (res == true) break;
//  }
////
//  // if isLevelComplete(NextLevel,e,Q) then
//  if (res == true) {
//    // Q := removeUselessEvents(CurrLevel,Q)
//    removeUselessEvents();
//    // CurrLevel := NextLevel
//    set<ProgramState*>::iterator cit;
//    for (cit = CurrLevel.begin(); cit != CurrLevel.end(); cit++) {
//      ProgramState *Sigma = (*cit);
//      delete Sigma;
//    }
//    CurrLevel = NextLevel;
//    NextLevel.clear();
//  }

//	cout << "CurrLevel.size(): " << CurrLevel.size() << endl;

	if (CurrLevel.size() > 0)
		return true;
	else
		return false;

}

void ProgramState::merge_automatons(ProgramState * other) {
	map<string, map<int, map<int, int> > >::iterator it_class;
	map<int, map<int, int> >::iterator it_object;
	string class_name;
	int obj_id;

	for (it_class = other->automaton_states.begin();
			it_class != other->automaton_states.end(); it_class++) {
		class_name = it_class->first;

		for (it_object = it_class->second.begin();
				it_object != it_class->second.begin(); it_object++) {
			obj_id = it_object->first;


			automaton_states[class_name][obj_id].insert(
					it_object->second.begin(), it_object->second.end());
		}
	}
}

bool ProgramState::updateAutomatons(TypestEvent *e) {//ignore means whether to continue after detected one violation
//	map<string,map<int,int> > automaton_states;//map<class name, map<current state, appear times> >

	bool ignore = false;

	string class_name = e->class_name;
	string function_name = e->method_name;
//	cout<<"class_name: "<<class_name<<"       method_name: "<<function_name<<endl;
//	int& initial_state=all_initial_state;

	int check_automaton;
	map<int, int> new_states;			//map<obj id, map<state, frequency> >

	int from_state;

	map<string, map<int, map<int, int> > >::iterator it_class;
	map<int, map<int, int> >::iterator it_object;
	map<int, int>::iterator it_state;

	it_class = automaton_states.find(class_name);
	if (it_class == automaton_states.end()) {//no automatons for the class at all;
		check_automaton = check(class_name, 0, function_name);
		if (check_automaton == -1)			//new violation
				{
			cout << "----------------automaton voilation" << endl;
			cout << "----------------automaton voilation" << endl;
			if (!ignore)
				return false;
		} else if (check_automaton > -1) {
			new_states[check_automaton] = 1;

		}

	} else if (it_class != automaton_states.end()) {
		it_object = it_class->second.find(e->obj_id);

		if (it_object == it_class->second.end()) {//no automatons for the object
			check_automaton = check(class_name, 0, function_name);
			if (check_automaton == -1)			//new violation
					{
				cout << "----------------automaton voilation" << endl;
				cout << "----------------automaton voilation" << endl;
				if (!ignore)
					return false;
			} else if (check_automaton > -1) {
				new_states[check_automaton] = 1;

			}

		}

		else {		//exist the class, exist the object, exist automaton states

			for (it_state = it_object->second.begin();
					it_state != it_object->second.end(); it_state++)//for each states of a class
					{
				from_state = it_state->first;

				check_automaton = check(class_name, from_state, function_name);

				if (check_automaton == -1)	//new violation
						{
					cout << "----------------automaton voilation" << endl;
					cout << "----------------automaton voilation" << endl;
					if (!ignore)
						return false;

				} else if (check_automaton > -1) {
					//				new_states[check_automaton] = it_class->second[from_state];
					new_states[check_automaton] = 1;
				}
			}

		}

	}

//	cout<<automaton_states[class_name].size()<<endl;
//
//	if (it_object == it_class->second.find(e->obj_id))			//no automaton
//			{
//		check_automaton = check(class_name, all_initial_state, function_name);
//		if (check_automaton == -1)			//new violation
//				{
//			cout << "----------------automaton voilation" << endl;
//			cout << "----------------automaton voilation" << endl;
//			if (!ignore)
//				return false;
//		} else if (check_automaton > -1) {
//			new_states[check_automaton] = 1;
//
//		}
//
//	} else {
//		for (it_state = it_object->second.begin();
//				it_state != it_object->second.end(); it_state++)//for each states of a class
//				{
//			from_state = it_state->first;
//
//			check_automaton = check(class_name, from_state, function_name);
//
//			if (check_automaton == -1)	//new violation
//					{
//				cout << "----------------automaton voilation" << endl;
//				cout << "----------------automaton voilation" << endl;
//				if (!ignore)
//					return false;
//
//			} else if (check_automaton > -1) {
////				new_states[check_automaton] = it_class->second[from_state];
//				new_states[check_automaton] = 1;
//			}
//		}
//
//	}

	automaton_states[class_name].erase(e->obj_id);
	automaton_states[class_name][e->obj_id].insert(new_states.begin(),
			new_states.end());
//	cout<<automaton_states[class_name].size()<<endl;

	return true;

}

bool ProgramState::isLocked(TypestEvent *e) {

	map<int, LockSet>::iterator it_lock;

	for (it_lock = locksets.begin(); it_lock != locksets.end(); it_lock++)//not tested yet
			{
		if (!it_lock->second.intersectIsEmpty(e->lockset)) {

			cout << "------------------------lock conflict" << endl;
			return true;

		}

	}
	return false;
}

bool ProgramState::isNextState(TypestEvent *e) {
	//test case about the map.insert().......
//	map<int,int> a;
//	a[1]=1;
//	a[2]=2;
//	map<int,int> b;
//	b[2]=22;
//	b[3]=33;
//	b.insert(a.begin(),a.end());
//	a.insert(b.begin(),b.end());
//	map<int,int>::iterator ita;
//	for(ita=b.begin();ita!=b.end();ita++)
//	{
//		cout<<"index: "<<ita->first<<"      value: "<<ita->second<<endl;
//
//	}
//	for(ita=a.begin();ita!=a.end();ita++)
//	{
//		cout<<"index: "<<ita->first<<"      value: "<<ita->second<<endl;
//
//	}

	bool res = false;

	// i := threadId(e)z
	int tid = e->thread_id;
	// if ( VC(\Sigma)[i]+1 = VC(e)[i] )

	if (clockvec.clocks[tid]==0 || clockvec.clocks[tid] + 1 == e->index_of_OBJ_CALL) { //whether the next step in this thread is e
		// if (\forall j != i : VC(\Sigma)[j] >= VC(e)[j] ) then
		res = true;
//		cout << "state clockvec_index:" << clockvec_index.toString() << endl;
//		cout << "state clockvec:" << clockvec.toString() << endl;
//		cout << e->toString() << e->clockvec.toString() << endl;
		if (!clockvec.must_happen_before_except(e->clockvec, tid)) {
//			cout<<"false"<<endl;
			res = false;
		}

	}

//	 cout<<"true"<<endl;
	return res;
}

ProgramState* ProgramState::createState(TypestEvent *e) {
	// \Sigma' := new copy of \Sigma
	ProgramState *Sigma2 = new ProgramState();
	int j = e->thread_id;

	Sigma2->clockvec = clockvec;
	Sigma2->clockvec.merge(e->clockvec);

	Sigma2->locksets = locksets;
	Sigma2->locksets[j].clear();
	Sigma2->locksets[j] = e->lockset;

	Sigma2->automaton_states = automaton_states;

	// automaton_states(\Sigma') := NEXT_STATES( automaton_states(\Sigma), methodId(e))
	// if b \in NEXT_STATES( automaton_states(\Sigma, methodId(e)) ) then
	//    print "typestate error observed"
	// endif

	//assert(0 && "to be implemented");
//	cout << "ERROR: " << __FUNCTION__ << " not yet fully implemented !" << endl;

	// return \Sigma'

//	map<string,map<int,int> > automaton_states;//map<class name, map<current state, appear times> >

	return Sigma2;
}

bool TypestEventQueue::isLevelComplete(TypestEvent* e) {
	// if size(NextLevel) >= w then
	//    return true
	if (NextLevel.size() >= (unsigned) MAX_NUM_NEXT_LEVEL_STATES)
		return true;
	// else if e is the last event in Q and size(Q) >= l then
	//    return true
	vector<TypestEvent*>::reverse_iterator rit = events.rbegin();
	if (rit != events.rend() && (*rit) == e) {
		if (events.size() >= (unsigned) MAX_NUM_EVENTS_IN_QUEUE) {
			return true;
		}
	}
	// else
	//    return false
	return false;
}

void TypestEventQueue::removeUselessEvents() {
	assert(0 && "not yet implemented");
}

TypestEventQueue::TypestEventQueue() {
	ProgramState* Sigma00 = new ProgramState;
	CurrLevel.insert(Sigma00);
}

TypestEventQueue::~TypestEventQueue() {
	set<ProgramState*>::iterator it;
	for (it = CurrLevel.begin(); it != CurrLevel.end(); it++) {
		ProgramState* s = (*it);
		delete s;
	}
	for (it = NextLevel.begin(); it != NextLevel.end(); it++) {
		ProgramState* s = (*it);
		delete s;
	}
}

void TypestEventQueue::enqueue(TypestEvent* ev) {
//	events.push_back(ev);
	events_by_thread[ev->thread_id][ev->index_of_OBJ_CALL] = ev;

//  cout<<"---------thread:"<<ev->thread_id<<"  size: "<<events_by_thread[ev->thread_id].size()<<endl;
	//cout<<"current size of events is :"<<events.size()<<endl;
}

void TypestEventQueue::dump() {
	string default_console = "\033[0m";

	cout << "TypestEventQueue = {\n";
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
		cout << default_console;
	}
	cout << "                 }" << endl;
}

