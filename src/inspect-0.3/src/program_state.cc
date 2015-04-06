#include "program_state.hh"
#include "inspect_exception.hh"
#include <cassert>
#include <sstream>
#include <iostream>
#include "inspect_ucg_graph.hh"

#include "yices_path_computer_singleton.hh"

using namespace std;
using namespace __gnu_cxx;

///////////////////////////////////////////////////////////////////////////
//
//    the implementationof ProgramState
//
///////////////////////////////////////////////////////////////////////////

ProgramState::ProgramState() {
//   enabled.clear();
//   disabled.clear();
	mutexes.clear();
//   conds.clear();
	rwlocks.clear();
}

ProgramState::ProgramState(ProgramState& state) {
	enabled = state.enabled;
	disabled = state.disabled;

	mutexes = state.mutexes;
//   conds = state.conds;
	rwlocks = state.rwlocks;
}

ProgramState & ProgramState::operator=(ProgramState &another) {
	enabled = another.enabled;
	disabled = another.disabled;

	mutexes = another.mutexes;
//   conds = state.conds;
	rwlocks = another.rwlocks;
	return *this;
}

bool ProgramState::operator==(ProgramState &another) {
	bool retval = true;

//   cout << "++++++++++ comparing +++++++++++++\n";
//   cout << this->toString();
//   cout << "\n";
//   cout << another.toString();
//   cout << "**********************************\n";

	if (enabled != another.enabled)
		retval = false;
	if (disabled != another.disabled)
		retval = false;
	if (mutexes != another.mutexes)
		retval = false;
//   if (conds != another.conds) return false;
	if (rwlocks != another.rwlocks)
		retval = false;

//   cout << ">>>>>>>>>>>> comparing >>>>>>>>>>>>>>>>>\n";
//   cout << this->toString();
//   cout << "\n";
//   cout << another.toString();
//   cout << "result = " << (retval? "true":"false") << endl;
//   cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";

	return retval;
}

bool ProgramState::operator!=(ProgramState &another) {
	return !(this->operator==(another));
}

size_t ProgramState::hash_number() {
	int retval, counter;
	TransitionSet::iterator it;
	InspectEvent event;

	//assert(false);

	counter = 1;
#ifdef NLZ_EVEC
	for (it = enabled.begin(); it != enabled.end(); it++) {
	    for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); ++vit){
		event = *vit;
		retval += event.location_id * counter;
		counter++;
	    }
	}

	for (it = disabled.begin(); it != disabled.end(); it++) {
	    for (std::vector<InspectEvent>::iterator vit = it->second.begin(); vit != it->second.end(); ++vit){
		event = *vit;
		retval += event.location_id * counter;
		counter++;
	    }
	}
#else
	for (it = enabled.begin(); it != enabled.end(); it++) {
		event = it->second;
		retval += event.location_id * counter;
		counter++;
	}

	for (it = disabled.begin(); it != disabled.end(); it++) {
		event = it->second;
		retval += event.location_id * counter;
		counter++;
	}
#endif
	return retval;
}

/**
 *  move all events which are in enabled set and has been disabled into disabled sets
 * 
 */
void ProgramState::update_enabled_set(InspectEvent &event) {
	TransitionSet::iterator it;
	vector<InspectEvent> tobe_disabled;
	vector<InspectEvent> tobe_removed;
	vector<InspectEvent>::iterator vit;
	InspectEvent tmpev;

	assert( !enabled.has_member(event));
#ifdef NLZ_EVEC
	for (it = enabled.begin(); it != enabled.end(); it++) {
	    for (vit = it->second.begin(); vit != it->second.end(); vit++){
		tmpev = *vit;
		if (event.can_disable(tmpev))
		    tobe_disabled.push_back(tmpev);
		if (event.type == THREAD_CANCEL && event.child_id == tmpev.thread_id)
		    tobe_removed.push_back(tmpev);
	    }
	}
#else
	for (it = enabled.begin(); it != enabled.end(); it++) {
		tmpev = it->second;
		if (event.can_disable(tmpev))
			tobe_disabled.push_back(tmpev);
		if (event.type == THREAD_CANCEL && event.child_id == tmpev.thread_id)
			tobe_removed.push_back(tmpev);
	}
#endif
	for (vit = tobe_disabled.begin(); vit != tobe_disabled.end(); vit++) {
		tmpev = *vit;
		this->enabled.remove(tmpev);
		this->disabled.insert(tmpev);
	}

	for (vit = tobe_removed.begin(); vit != tobe_removed.end(); vit++) {
		tmpev = *vit;
		this->enabled.remove(tmpev);
	}
}

void ProgramState::update_disabled_set(InspectEvent &event) {
	TransitionSet::iterator it;
	vector<InspectEvent> tobe_enabled;
	vector<InspectEvent> tobe_removed;
	vector<InspectEvent>::iterator vit;
	InspectEvent tmpev;

	assert( !enabled.has_member(event));
	assert( !disabled.has_member(event));
#ifdef NLZ_EVEC
	for (it = disabled.begin(); it != disabled.end(); it++) {
	    for (vit = it->second.begin(); vit != it->second.end(); vit++){
		tmpev = *vit;
		if (event.can_enable(tmpev))
			tobe_enabled.push_back(tmpev);
		// RSS
		if (event.type == THREAD_CANCEL && event.child_id == tmpev.thread_id)
			tobe_removed.push_back(tmpev);
		if (event.type == THREAD_CANCEL && tmpev.type == MUTEX_LOCK) {
			SchedulerMutex* mutex = mutexes.get_mutex(tmpev.mutex_id);
			if (mutex->get_owner() == event.child_id || mutex->is_available()) {
				tobe_enabled.push_back(tmpev);
			}
		}
	    }
	}
#else
	for (it = disabled.begin(); it != disabled.end(); it++) {
		tmpev = it->second;
		if (event.can_enable(tmpev))
			tobe_enabled.push_back(tmpev);
		// RSS
		if (event.type == THREAD_CANCEL && event.child_id == tmpev.thread_id)
			tobe_removed.push_back(tmpev);
		if (event.type == THREAD_CANCEL && tmpev.type == MUTEX_LOCK) {
			SchedulerMutex* mutex = mutexes.get_mutex(tmpev.mutex_id);
			if (mutex->get_owner() == event.child_id || mutex->is_available()) {
				tobe_enabled.push_back(tmpev);
			}
		}
	}
#endif
	for (vit = tobe_enabled.begin(); vit != tobe_enabled.end(); vit++) {
		tmpev = *vit;
		this->disabled.remove(tmpev);
		this->enabled.insert(tmpev);
	}

	for (vit = tobe_removed.begin(); vit != tobe_removed.end(); vit++) {
		tmpev = *vit;
		this->disabled.remove(tmpev);
	}

#ifdef NLZ_EVEC
	if (event.type == COND_SIGNAL) {
		for (it = disabled.begin(); it != disabled.end(); it++) {
		    for (vit = it->second.begin(); vit != it->second.end(); vit++){
			tmpev = *vit;
			if (tmpev.type == COND_WAIT && tmpev.cond_id == event.cond_id) {
				this->disabled.remove(tmpev);
				this->enabled.insert(tmpev);
				break;
			}
		    }
		}
	} else if (event.type == COND_BROADCAST) {
		for (it = disabled.begin(); it != disabled.end(); it++) {
		    for (vit = it->second.begin(); vit != it->second.end(); vit++){
			tmpev = *vit;
			if (tmpev.type == COND_WAIT && tmpev.cond_id == event.cond_id)
				tobe_enabled.push_back(tmpev);
		    }
		}

		for (vit = tobe_enabled.begin(); vit != tobe_enabled.end(); vit++) {
			tmpev = *vit;
			this->disabled.remove(tmpev);
			this->enabled.insert(tmpev);
		}
	} else if (event.type == RWLOCK_UNLOCK) {

		if (disabled.has_rwlock_rdlock(event.rwlock_id)) {
			for (it = disabled.begin(); it != disabled.end(); it++) {
			    for (vit = it->second.begin(); vit != it->second.end(); vit++){
				tmpev = *vit;
				if (tmpev.type == RWLOCK_RDLOCK
						&& tmpev.rwlock_id == event.rwlock_id)
					tobe_enabled.push_back(tmpev);
			    }
			}

			for (vit = tobe_enabled.begin(); vit != tobe_enabled.end(); vit++) {
				tmpev = *vit;
				disabled.remove(tmpev);
				enabled.insert(tmpev);
			}
		} else if (disabled.has_rwlock_wrlock(event.rwlock_id)) {
			for (it = disabled.begin(); it != disabled.end(); it++) {
			    for (vit = it->second.begin(); vit != it->second.end(); vit++){
				tmpev = *vit;
				if (tmpev.type == RWLOCK_WRLOCK
						&& tmpev.rwlock_id == event.rwlock_id)
					break;
			    }
			}
			disabled.remove(tmpev);
			enabled.insert(tmpev);
		}
	}
#else
	if (event.type == COND_SIGNAL) {
		for (it = disabled.begin(); it != disabled.end(); it++) {
			tmpev = it->second;
			if (tmpev.type == COND_WAIT && tmpev.cond_id == event.cond_id) {
				this->disabled.remove(tmpev);
				this->enabled.insert(tmpev);
				break;
			}
		}
	} else if (event.type == COND_BROADCAST) {
		for (it = disabled.begin(); it != disabled.end(); it++) {
			tmpev = it->second;
			if (tmpev.type == COND_WAIT && tmpev.cond_id == event.cond_id)
				tobe_enabled.push_back(tmpev);
		}

		for (vit = tobe_enabled.begin(); vit != tobe_enabled.end(); vit++) {
			tmpev = *vit;
			this->disabled.remove(tmpev);
			this->enabled.insert(tmpev);
		}
	} else if (event.type == RWLOCK_UNLOCK) {

		if (disabled.has_rwlock_rdlock(event.rwlock_id)) {
			for (it = disabled.begin(); it != disabled.end(); it++) {
				tmpev = it->second;
				if (tmpev.type == RWLOCK_RDLOCK
						&& tmpev.rwlock_id == event.rwlock_id)
					tobe_enabled.push_back(tmpev);
			}

			for (vit = tobe_enabled.begin(); vit != tobe_enabled.end(); vit++) {
				tmpev = *vit;
				disabled.remove(tmpev);
				enabled.insert(tmpev);
			}
		} else if (disabled.has_rwlock_wrlock(event.rwlock_id)) {
			for (it = disabled.begin(); it != disabled.end(); it++) {
				tmpev = it->second;
				if (tmpev.type == RWLOCK_WRLOCK
						&& tmpev.rwlock_id == event.rwlock_id)
					break;
			}
			disabled.remove(tmpev);
			enabled.insert(tmpev);
		}
	}
#endif
}

/**
 *  testing whether an thread is alive
 */
bool ProgramState::alive(int tid) {
	InspectEvent event;

#ifdef NLZ_EVEC
	event = enabled.get_front_transition(tid);
#else
	event = enabled.get_transition(tid);
#endif
	if (event.valid())
		return true;

#ifdef NLZ_EVEC
	event = disabled.get_front_transition(tid);
#else
	event = disabled.get_transition(tid);
#endif
	return event.valid();
}

bool ProgramState::check_race() {
	TransitionSet::iterator it;
	InspectEvent event, event2;
	bool res = false;
#ifdef NLZ_EVEC
	std::vector<InspectEvent> race_events;
	std::vector<InspectEvent>::iterator vit;
	for (it = enabled.begin(); it != enabled.end(); it++) {
	    for (std::vector<InspectEvent>::iterator vit=it->second.begin(); vit != it->second.end(); vit++){
		event = *vit;
//		cout << "  [check]: " << event.toString() << endl;
		if (yices_path_computer_singleton::getInstance()->verbose>=yices_path_computer_singleton::getInstance()->v_3) {
			cout << "  [check]: " << event.toString() << endl;
		}
		race_events = enabled.get_race_events(event);
		for (vit = race_events.begin(); vit!= race_events.end(); vit++){
		    event2 = *vit;
		    if (event2.valid()) {
			if (event.thread_id < event2.thread_id) {
			    cout << "Found a data race between " << event.toString()  << endl
				 << "                      and " << event2.toString() << endl;
			    res = true;   // TODO: need to return the number of races, so that it can reported the corrected number of errors
			}
		    }
		}
	    }
	}
#else
	for (it = enabled.begin(); it != enabled.end(); it++) {
		event = it->second;
//		cout << "  [check]: " << event.toString() << endl;
		if (yices_path_computer_singleton::getInstance()->verbose>=yices_path_computer_singleton::getInstance()->v_3) {
			cout << "  [check]: " << event.toString() << endl;
		}
		event2 = enabled.get_race_event(event);
		if (event2.valid()) {
			if (event.thread_id < event2.thread_id) {
                          cout << "Found a data race between " << event.toString()  << endl
                               << "                      and " << event2.toString() << endl;
                          res = true;
			}
		}
	}
#endif
	return res;
}

void ProgramState::add_transition(InspectEvent &event) {
	int mutex_id;
	SchedulerMutex * mutex;
	SchedulerRwlock * rwlock;

	if (event.type == THREAD_JOIN) {
		if (alive(event.child_id))
			disabled.insert(event);
		else
			enabled.insert(event);
	} else if (event.type == MUTEX_LOCK) {
		mutex_id = event.mutex_id;
		mutex = mutexes.get_mutex(mutex_id);
		assert(mutex != NULL);
		if (mutex->is_available())
			enabled.insert(event);
		else if (mutex->get_owner() == event.thread_id) {
			//recursive lock
			enabled.insert(event);
		} else
			disabled.insert(event);
	} else if (event.type == COND_WAIT) {
		disabled.insert(event);
	} else if (event.type == RWLOCK_RDLOCK) {
		rwlock = rwlocks.get_rwlock(event.rwlock_id);
		assert(rwlock != NULL);
		if (rwlock->status == RWLS_READING || rwlock->status == RWLS_IDLE)
			enabled.insert(event);
		else
			disabled.insert(event);
	} else if (event.type == RWLOCK_WRLOCK) {
		rwlock = rwlocks.get_rwlock(event.rwlock_id);
		assert(rwlock != NULL);
		if (rwlock->status == RWLS_IDLE)
			enabled.insert(event);
		else
			disabled.insert(event);
	} else {
		//RSS: added (begin)
		/*
		 if (event.type == THREAD_END && event.thread_id == 0)
		 disabled.insert(event);
		 else if (event.type == MISC_EXIT)
		 disabled.insert(event);
		 else if (event.type == MISC_SLEEP || event.type == MISC_YIELD || event.type == MISC_BLOCKING)
		 disabled.insert(event);
		 else
		 */

		enabled.insert(event);
	}
}

bool ProgramState::is_enabled(InspectEvent& event) {
	return enabled.has_member(event);
}

bool ProgramState::is_disabled(InspectEvent& event) {
	return disabled.has_member(event);
}

void ProgramState::execute_transition(InspectEvent &event) {
	SchedulerMutex * mutex = NULL;
	SchedulerRwlock *rwlock = NULL;

	switch (event.type) {

	case MUTEX_INIT:
		mutexes.init(event.mutex_id, event.is_recursive_mutex);
		break;

	case MUTEX_DESTROY:
		mutexes.remove(event.mutex_id);
		break;

	case MUTEX_LOCK:
		mutex = mutexes.get_mutex(event.mutex_id);
		assert(mutex != NULL);

#ifdef RSS_EXTENSION
		if (!mutex->is_available()
				&& (!mutex->is_recursive
						|| mutex->get_owner() != event.thread_id)) {
			cout << "Found an illegal lock!";
			cout << " (mutex->owner = " << mutex->get_owner();
			cout << ", event.thread_id = " << event.thread_id;
			cout << endl;
			throw IllegalLockException("");
		}
		if (mutex->is_recursive) {
			cout << endl << "recursive lock Event: " << event.toString()
					<< " count = " << mutex->count << endl;
		}
#endif//RSS_EXTENSION
		mutex->acquire_by(event.thread_id);
		break;

	case MUTEX_UNLOCK:
		mutex = mutexes.get_mutex(event.mutex_id);
		assert(mutex != NULL);

#ifdef RSS_EXTENSION
		if (mutex->get_owner() != event.thread_id) {
			cout << "Found an illegal unlock!";
			cout << " (mutex->owner = " << mutex->get_owner();
			cout << ", event.thread_id = " << event.thread_id;
			cout << endl;
			throw IllegalLockException("");
		}
		if (mutex->is_recursive) {
			cout << endl << "recursive lock Event: " << event.toString()
					<< " count = " << mutex->count << endl;
		}
#endif//RSS_EXTENSION
		mutex->release();
		break;

	case THREAD_CANCEL:
		mutexes.reset_mutexes_heldby_thread(event.child_id);
		break;

	case RWLOCK_INIT:
		rwlocks.init(event.rwlock_id);
		break;

	case RWLOCK_DESTROY:
		rwlocks.destroy(event.rwlock_id);
		break;

	case RWLOCK_RDLOCK:
		rwlock = rwlocks.get_rwlock(event.rwlock_id);
		assert(rwlock != NULL);
		rwlock->reader_acquire(event.thread_id);
		break;

	case RWLOCK_WRLOCK:
		rwlock = rwlocks.get_rwlock(event.rwlock_id);
		assert(rwlock != NULL);
		rwlock->writer_acquire(event.thread_id);
		break;

	case RWLOCK_UNLOCK:
		rwlock = rwlocks.get_rwlock(event.rwlock_id);
		assert(rwlock != NULL);
		rwlock->release(event.thread_id);
		break;

	default:
		break;
	}

}

string ProgramState::toString() {
	stringstream ss;
	InspectEvent event;
	TransitionSet::iterator it;
	int tid = 0;

	ss << "+--------------------------------------------- \n";
#ifdef NLZ_EVEC
	ss << "| enabled: \n";
	for (it = enabled.begin(); it != enabled.end(); it++) {
	    for (std::vector<InspectEvent>::iterator vit=it->second.begin(); vit != it->second.end(); vit++){
		event = *vit;
		ss << "|   " << event.toString() << endl;
	    }
	}

	ss << "| disabled: \n";
	for (it = disabled.begin(); it != disabled.end(); it++) {
	    for (std::vector<InspectEvent>::iterator vit=it->second.begin(); vit != it->second.end(); vit++){
		event = *vit;
		ss << "|   " << event.toString() << endl;
	    }
	}
#else
	ss << "| enabled: \n";
	for (it = enabled.begin(); it != enabled.end(); it++) {
		event = it->second;
		ss << "|   " << event.toString() << endl;
	}

	ss << "| disabled: \n";
	for (it = disabled.begin(); it != disabled.end(); it++) {
		event = it->second;
		ss << "|   " << event.toString() << endl;
	}
#endif
	ss << "+--------------------------------------------- \n";
	return ss.str();
}

///////////////////////////////////////////////////////////////////////////
//
//   ProgramStateTable
//
///////////////////////////////////////////////////////////////////////////

ProgramStateTable::ProgramStateTable() {
	states.clear();
}

ProgramStateTable::~ProgramStateTable() {
	iterator it;
	ProgramState * state;

	for (it = states.begin(); it != states.end(); it++) {
		state = *it;
		if (state != NULL) {
			delete state;
		}
	}
}

void ProgramStateTable::insert(ProgramState * state) {
	assert(! has_member(state));
	//states.insert(state);
	states.push_back(state);
}

bool ProgramStateTable::has_member(ProgramState * state) {
	iterator it;
	ProgramState * another;

	for (it = states.begin(); it != states.end(); it++) {
		another = *it;
		if (*another == *state)
			return true;
	}

	return false;
//   it = states.find(state);
//   return (it != states.end());

}

string ProgramStateTable::toString() {
	stringstream ss;
	ProgramState * state;
	iterator it;

	ss << "========== Program State Table Begin ====== \n";
	for (it = states.begin(); it != states.end(); it++) {
		state = *it;
		ss << state->toString();
	}
	ss << "========== Program State Table End   ====== \n";

	return ss.str();
}

