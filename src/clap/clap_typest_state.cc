#include "clap_typest_state.hh"

//static map<ObjectId,Automaton> ProgramState::automaton_of_obj;

ProgramState::ProgramState() {

}

ProgramState::~ProgramState() {

}

void ProgramState::dump() {
	cout << "ProgramState = {\n";
	cout << "                clockvec = " << clockvec.toString() << " ,\n";

	cout << "                locksets = ";
	map<int, LockSet>::iterator it_lock;
	for (it_lock = locksets.begin(); it_lock != locksets.end(); it_lock++) {
		if (it_lock->second.size() > 0)
			cout << " TID: " << it_lock->first << " "
					<< it_lock->second.toString();
	}
	cout << " ," << endl;

	map<string, map<int, map<int, int> > >::iterator it_class;
	map<int, map<int, int> >::iterator it_object;
	map<int, int>::iterator it_state;
	for (it_class = automaton_states.begin();
			it_class != automaton_states.end(); it_class++) {
		cout << "                " << it_class->first << ": ";

		for (it_object = it_class->second.begin();
				it_object != it_class->second.end(); it_object++) {
			if (it_object->second.size()<1) continue;
			cout<<"{ "<<it_object->first<<": ";


			for (it_state = it_object->second.begin();
					it_state != it_object->second.end(); it_state++) {
				cout << " " << it_state->first << ",";

			}
			cout<<" } ";
		}
		cout << endl;

	}

	map<ObjectId, AutomatonStates>::iterator it;
	for (it = states_of_automaton.begin(); it != states_of_automaton.end();
			it++) {

		ObjectId obj = it->first;
		AutomatonStates states = it->second;

		cout << "                states_of_A[" << obj << "] = { ";

		AutomatonStates::iterator it2;
		for (it2 = states.begin(); it2 != states.end(); it2++) {
			if (it2 != states.begin())
				cout << " , ";
			AutomatonState s = (*it2);
			cout << s;
		}

		cout << "  }" << endl;
	}
	cout << "               }" << endl;
}

Automaton::Automaton() {

}

Automaton::~Automaton() {

}

void Automaton::set_name(string n) {
	name = n;
}

string& Automaton::get_name() {
	return name;
}

void Automaton::add_transition(AutomatonState curr_s, MethodId m,
		AutomatonState next_s) {
	TR[make_pair(curr_s, m)] = next_s;
}

AutomatonStates Automaton::next_states(AutomatonStates curr_states, MethodId m,
		bool error) {
	AutomatonStates new_states;
	AutomatonStates::iterator it;
	for (it = curr_states.begin(); it != curr_states.end(); it++) {
		AutomatonState curr_s = (*it);
		map<pair<AutomatonState, MethodId>, AutomatonState>::iterator TR_it;
		TR_it = TR.find(make_pair(curr_s, m));
		if (TR_it != TR.end()) {
			AutomatonState new_s = TR[make_pair(curr_s, m)];
			new_states.insert(new_s);
		} else {
			// we reach a BAD automaton state !!!
			error = true;
		}
	}
	return new_states;
}

void Automaton::dump() {
	cout << "Automaton '" << name << "' = {\n";
	map<pair<AutomatonState, MethodId>, AutomatonState>::iterator it;
	for (it = TR.begin(); it != TR.end(); it++) {
		AutomatonState curr_s = it->first.first;
		MethodId m = it->first.second;
		AutomatonState next_s = it->second;
		cout << " [ " << curr_s << " ] ==( " << m << " )==> " << " [ " << next_s
				<< " ]" << endl;
	}
}

