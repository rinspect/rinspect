#include "naling.def"
#include "inspect_event.hh"
#include "inspect_exception.hh"
#include <sstream>
#include <string> 
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <utility>
#include <time.h>

#include "scheduler_setting.hh"

using namespace std;

#define DEF_EVENT_CODE(EV, STR, EV_PERM, CAT)   CAT,

EventCategory events_cat[] = {
#include "inspect_event.def"
		EC_ERROR };

#undef DEF_EVENT_CODE

EventCategory get_event_category(EventType et) {
	int idx;
	idx = (int) et;
	return events_cat[idx];
}

#define DEF_EVENT_CODE(EV, STR, EV_PERM, CAT)   STR, 
const char * eventstr[] = {
#include "inspect_event.def"
		"unknown" };
#undef DEF_EVENT_CODE

string event_type_to_string(EventType et) {
	int idx;
	idx = (int) et;
	return eventstr[idx];
}

EventType string_to_event_type(string str) {
	string unknown_str = "unknown";

	int idx = 0;
	while (1) {
		int len1 = strlen(str.c_str());
		int len2 = strlen(eventstr[idx]);
		int len = (len1 < len2) ? len1 : len2;
		if (!strncmp(eventstr[idx], str.c_str(), len))
			return (EventType) idx;
		if (!strncmp(eventstr[idx], str.c_str(), len))
			return UNKNOWN;
		idx++;
	}
}

EventPermitType permit_type(enum EventType type) {
	EventPermitType permit;
	permit = (EventPermitType) (type);
	return permit;
}

InspectEvent InspectEvent::dummyEvent;

InspectEvent::InspectEvent() {
	this->init();
}

void InspectEvent::init() {
	type = UNKNOWN;
	thread_id = -1;
	mutex_id = -1;
	cond_id = -1;
	location_id = -1;
	local_state_changed_flag = true;
#ifdef NLZ_COMM
	i_mult = -1;
	future = 0;
#endif
	
#ifdef RSS_EXTENSION
	obj_value = -1;
	wakeup_time_sec = 0;
	wakeup_time_nsec = 0;
	may_fail = 0;
	return_status = 0;
	is_recursive_mutex = 0;
	eid = -1;

	class_name = "unknown";
	method_name = "unknown";
	index_of_OBJ_CALL = -1;
	retval = 0;
	return_value = 0;
	inst_id = 0;
#endif

}

void InspectEvent::init_mutex_init(int tid, int mid) {
	type = MUTEX_INIT;
	thread_id = tid;
	mutex_id = mid;
}

void InspectEvent::init_mutex_destroy(int tid, int mid) {
	type = MUTEX_DESTROY;
	thread_id = tid;
	mutex_id = mid;
}

void InspectEvent::init_mutex_lock(int tid, int mid) {
	type = MUTEX_LOCK;
	thread_id = tid;
	mutex_id = mid;
}

void InspectEvent::init_mutex_trylock(int tid, int mid) {
	type = MUTEX_TRYLOCK;
	thread_id = tid;
	mutex_id = mid;
}

void InspectEvent::init_mutex_unlock(int tid, int mid) {
	type = MUTEX_UNLOCK;
	thread_id = tid;
	mutex_id = mid;
}

void InspectEvent::init_cond_init(int tid, int cid) {
	type = COND_INIT;
	thread_id = tid;
	cond_id = cid;
}

void InspectEvent::init_cond_destroy(int tid, int cid) {
	type = COND_DESTROY;
	thread_id = tid;
	cond_id = cid;
}

void InspectEvent::init_cond_wait(int tid, int cid, int mid) {
	type = COND_WAIT;
	thread_id = tid;
	cond_id = cid;
	mutex_id = mid;
}

void InspectEvent::init_cond_signal(int tid, int cid) {
	type = COND_SIGNAL;
	thread_id = tid;
	cond_id = cid;
}

void InspectEvent::init_cond_broadcast(int tid, int cid) {
	type = COND_BROADCAST;
	thread_id = tid;
	cond_id = cid;
}

void InspectEvent::init_cond_timedwait(int tid, int cid) {
	type = COND_WAIT;
	thread_id = tid;
	cond_id = cid;
}

/*
 *  a pthread_cond_wait operation is split into three parts:
 *   
 */
void InspectEvent::init_cond_wait_lock(int tid, int cid, int mid) {
	type = COND_WAIT_LOCK;
	thread_id = tid;
	cond_id = cid;
	mutex_id = mid;
}

void InspectEvent::init_cond_wait_unlock(int tid, int cid, int mid) {
	type = COND_WAIT_UNLOCK;
	thread_id = tid;
	cond_id = cid;
	mutex_id = mid;
}

void InspectEvent::init_rwlock_init(int tid, int rwid) {
	type = RWLOCK_INIT;
	thread_id = tid;
	rwlock_id = rwid;
}

void InspectEvent::init_rwlock_destroy(int tid, int rwlid) {
	type = RWLOCK_DESTROY;
	thread_id = tid;
	rwlock_id = rwlid;
}

void InspectEvent::init_rwlock_rdlock(int tid, int rwlid) {
	type = RWLOCK_RDLOCK;
	thread_id = tid;
	rwlock_id = rwlid;
}

void InspectEvent::init_rwlock_wrlock(int tid, int rwlid) {
	type = RWLOCK_WRLOCK;
	thread_id = tid;
	rwlock_id = rwlid;
}

void InspectEvent::init_rwlock_unlock(int tid, int rwlid) {
	type = RWLOCK_UNLOCK;
	thread_id = tid;
	rwlock_id = rwlid;
}

void InspectEvent::init_thread_start(int tid) {
	type = THREAD_START;
	thread_id = tid;
}

void InspectEvent::init_thread_end(int tid) {
	type = THREAD_END;
	thread_id = tid;
}

void InspectEvent::init_thread_create(int tid, int cid) {
	type = THREAD_CREATE;
	thread_id = tid;
	child_id = cid;
}

void InspectEvent::init_thread_pre_create(int tid) {
	type = THREAD_PRE_CREATE;
	thread_id = tid;
}

void InspectEvent::init_thread_post_create(int tid, int cid) {
	type = THREAD_POST_CREATE;
	thread_id = tid;
	child_id = cid;
}

void InspectEvent::init_thread_join(int tid, int cid) {
	type = THREAD_JOIN;
	thread_id = tid;
	child_id = cid;
}

void InspectEvent::init_state_capturing_thread_start(int tid) {
	type = STATE_CAPTURING_THREAD_START;
	thread_id = tid;
}

void InspectEvent::init_state_capturing_thread_pre_create(int tid) {
	type = STATE_CAPTURING_THREAD_PRE_CREATE;
	thread_id = tid;
}

void InspectEvent::init_state_capturing_thread_post_create(int tid, int cid) {
	type = STATE_CAPTURING_THREAD_POST_CREATE;
	thread_id = tid;
	child_id = cid;
}

void InspectEvent::init_obj_register(int tid, int oid) {
	type = OBJ_REGISTER;
	thread_id = tid;
	obj_id = oid;
}

void InspectEvent::init_obj_read(int tid, int oid) {
	type = OBJ_READ;
	thread_id = tid;
	obj_id = oid;
}

void InspectEvent::init_obj_write(int tid, int oid) {
	type = OBJ_WRITE;
	thread_id = tid;
	obj_id = oid;
}

void InspectEvent::init_obj_call(int tid, int oid, string fname,
		int method_id) {
	type = OBJ_CALL;
	thread_id = tid;
	obj_id = oid;
	//
	method_name = fname;
	index_of_OBJ_CALL = method_id;

//	if (index_of_thread.find(tid) == index_of_thread.end()) {
//		index_of_thread[tid] = 0;
//	} else {
//		index_of_thread[tid]++;
//	}
}

void InspectEvent::init_obj_resp(int tid, int oid, string fname, int method_id,
		char* ret, int return_v) {

	type = OBJ_RESP;
	thread_id = tid;
	obj_id = oid;
	//
	method_name = fname;
	index_of_OBJ_CALL = method_id;
	retval = ret;
	return_value = return_v;

}

void InspectEvent::init_symm_point(int tid, int ptno) {
	thread_id = tid;
	point_no = ptno;
}

void InspectEvent::init_state_req(int tid) {
	type = STATE_REQ;
	thread_id = tid;
}

void InspectEvent::init_state_ack(int tid) {
	type = STATE_ACK;
	thread_id = tid;
}

void InspectEvent::init_local_info(int tid, int pos, int flag) {
	type = LOCAL_INFO;
	thread_id = tid;
	location_id = pos;
	local_state_changed_flag = flag;
}

void InspectEvent::init_local_state_begin(int tid) {
	type = LOCAL_STATE_BEGIN;
	thread_id = tid;
}

void InspectEvent::init_local_state_end(int tid) {
	type = LOCAL_STATE_END;
	thread_id = tid;
}

void InspectEvent::init_local_int(int tid) {
	type = LOCAL_INT;
	thread_id = tid;
}

void InspectEvent::init_local_double(int tid) {
	type = LOCAL_DOUBLE;
	thread_id = tid;
}

void InspectEvent::init_local_binary(int tid) {
	type = LOCAL_BINARY;
	thread_id = tid;
}

void InspectEvent::init_cas_instr(int tid, int oid) {
	type = CAS_INSTR;
	thread_id = tid;
	obj_id = oid;
}

void InspectEvent::init_cas2_instr(int tid, int oid) {
	type = CAS2_INSTR;
	thread_id = tid;
	obj_id = oid;
}

#ifdef RSS_EXTENSION

void InspectEvent::init_blocking(int tid) {
	type = MISC_BLOCKING;
	thread_id = tid;
}

void InspectEvent::init_unblocking(int tid) {
	type = MISC_UNBLOCKING;
	thread_id = tid;
}

void InspectEvent::init_exit(int tid) {
	type = MISC_EXIT;
	thread_id = tid;
}

string InspectEvent::toXML() {
	stringstream ss;
	EventCategory cat;

	cat = get_event_category(type);

	ss << " <threadId> " << thread_id << " </threadId> " << " <eventType> "
			<< event_type_to_string(type) << " </eventType> ";

	switch (cat) {
	case EC_MUTEX:
		ss << " <mutexId> " << mutex_id << " </mutexId> ";
		if (cond_id != -1)
			ss << " <condId> " << cond_id << " </condId> ";
		break;

	case EC_COND:
		ss << " <condId> " << cond_id << " </condId> ";
		if (type == COND_WAIT)
			ss << " <mutexId> " << mutex_id << " </mutexId> ";
		break;

	case EC_RWLOCK:
		ss << " <rwlockId> " << rwlock_id << " </rwlockId> ";
		break;

	case EC_OBJECT:
		ss << " <objId> " << obj_id << " </objId> ";
		ss << " <objVal> " << obj_value << " </objVal> ";
		break;

	case EC_THREAD:
		if (type == THREAD_CREATE)
			ss << " <childThreadId> " << child_id << " </childThreadId> ";
		else if (type == THREAD_POST_CREATE || type == THREAD_JOIN)
			ss << " <childThreadId> " << child_id << " </childThreadId> ";
		else if (type == THREAD_START)
			// ss <<", "<< thread_nm;
			;
		break;

	case EC_SEMAPHORE:
		ss << " <semId> " << sem_id << " </semId> ";
		break;

	default:
		break;
	}

	if (location_id >= 0) {
		ss << " <locInfoId> " << location_id << " </locInfoId> ";
	}

	if (may_fail && return_status != 0) {
		ss << " <returnStat> " << return_status << " </returnStat> ";
	}

	return ss.str();
}

string InspectEvent::toJet() {
	stringstream ss;
	EventCategory cat;
	static int eid = 0;
	cat = get_event_category(type);

	switch (cat) {
	case EC_MUTEX:
		if (type == MUTEX_LOCK) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "lock [var \"mutex_" << mutex_id << "\" ";
			if (cond_id != -1)
				ss << " cond " << cond_id;
			ss << " src " << location_id << " ] ] ";
		} else if (type == MUTEX_UNLOCK) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "unlock [var \"mutex_" << mutex_id << "\" ";
			if (cond_id != -1)
				ss << " cond " << cond_id;
			ss << " src " << location_id << " ] ] ";
		}
		break;
	case EC_COND:
		if (type == COND_SIGNAL) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "notify [var \"cond_" << cond_id << "\"" << " src "
					<< location_id << " ] ] ";
		} else if (type == COND_BROADCAST) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "notifyAll [var \"cond_" << cond_id << "\"" << " src "
					<< location_id << " ] ] ";
		} else if (type == COND_WAIT) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "wait [var \"mutex_" << mutex_id << "\"" << " src "
					<< location_id << " ] ] ";
		}
		break;

	case EC_OBJECT:
		if (type == OBJ_READ) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "read  [var \"obj_" << obj_id << "\" int " << obj_value
					<< " src " << location_id << " ] ] ";
		} else if (type == OBJ_WRITE) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "write [var \"obj_" << obj_id << "\" int " << obj_value
					<< " src " << location_id << " ] ] ";
		} else if (type == OBJ_CALL) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "call  [var \"obj_" << obj_id << "\" int " << obj_value
					<< " src " << location_id << " ] ] ";
		} else if (type == OBJ_RESP) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "resp [var \"obj_" << obj_id << "\" int " << obj_value
					<< " src " << location_id << " ] ] ";
		}
		break;
	case EC_THREAD:
		if (type == THREAD_POST_CREATE) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "fork [var \"id\" int " << child_id << " src " << location_id
					<< " ] ] ";
		} else if (type == THREAD_JOIN) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "terminate [var \"id\"  int " << child_id << " src "
					<< location_id << " ] ] ";
		}
		break;
	default:
		break;
	}
	return ss.str();
}

bool InspectEvent::is_blocking() {
	return (type == MISC_BLOCKING);
}

bool InspectEvent::is_unblocking() {
	return (type == MISC_UNBLOCKING);
}

#endif // RSS_EXTENSION
string InspectEvent::toString() {
	stringstream ss;
	EventCategory cat;

	cat = get_event_category(type);

	ss << "(";

	ss << "e=" << setw(3) << eid;
	ss << ", ";

	ss << "t=" << thread_id << ", type= " << event_type_to_string(type) << " ";

	switch (cat) {
	case EC_MUTEX:
		ss << ", m=" << mutex_id;
		if (cond_id != -1)
			ss << ", c[" << cond_id << "]";
		break;

	case EC_COND:
		ss << ", c=" << cond_id;
		if (type == COND_WAIT)
			ss << ", m=" << mutex_id;
		break;

	case EC_RWLOCK:
		ss << ", rwlock_id=" << rwlock_id;
		break;

	case EC_OBJECT:
		ss << ", o=" << obj_id;
		//    ss <<", obj_val=" << obj_value;
		break;

	case EC_THREAD:
		if (type == THREAD_CREATE)
			ss << ", t=" << child_id;
		else if (type == THREAD_POST_CREATE || type == THREAD_JOIN
				|| type == THREAD_CANCEL)
			ss << ", t=" << child_id;
		else if (type == THREAD_START || type == THREAD_END)
			ss << ", t=" << thread_id;
		;
		break;

	case EC_SEMAPHORE:
		ss << ", s=" << sem_id;
		break;

	case EC_SYMMETRY:
		ss << ", o=" << obj_id;
		break;

	default:
		ss << ", t=" << thread_id;
		break;
	}

	if (location_id >= 0) {
		ss << ", loc=" << location_id;
	}

	if (may_fail && return_status != 0) {
		ss << ", ret=" << return_status;
	}

	if (type == OBJ_CALL || type == OBJ_RESP) {
		//ss << "    ,class=" << class_name;
		ss << "    ,function=" << method_name;
//		ss << "    ,index_of_OBJ_CALL=" << index_of_OBJ_CALL;

//		if (retval!=-1) {
//			cout<<retval<<endl;
		if (return_value == 1) {
//		ss << "    ,return ? = " << (int) return_value;
			ss << "    ,return= " << (int) retval;
		}
//		}

	}
	if (type == OBJ_READ || type == OBJ_WRITE || type == CACHE_OBJ_WRITE || type == PAUSE_OBJ_READ) {
		ss << ", inst= " << inst_id;
#ifdef NLZ_COMM
		ss <<", future= " << future;
		ss <<", i_mult= " << i_mult;
#endif
	}
	ss << ")   ";

	return ss.str();
}

string InspectEvent::toString_quasi() {
	stringstream ss;
	EventCategory cat;

	cat = get_event_category(type);

	ss << "(";

	ss << "e=" << setw(3) << eid;
	ss << ", ";

	ss << "t=" << thread_id << ", type= " << event_type_to_string(type) << " ";

	switch (cat) {
	case EC_MUTEX:
		ss << ", m=" << mutex_id;
		if (cond_id != -1)
			ss << ", c[" << cond_id << "]";
		break;

	case EC_COND:
		ss << ", c=" << cond_id;
		if (type == COND_WAIT)
			ss << ", m=" << mutex_id;
		break;

	case EC_RWLOCK:
		ss << ", rwlock_id=" << rwlock_id;
		break;

	case EC_OBJECT:
//		ss << ", o=" << obj_id;
		//    ss <<", obj_val=" << obj_value;
		break;

	case EC_THREAD:
		if (type == THREAD_CREATE)
			ss << ", t=" << child_id;
		else if (type == THREAD_POST_CREATE || type == THREAD_JOIN
				|| type == THREAD_CANCEL)
			ss << ", t=" << child_id;
		else if (type == THREAD_START || type == THREAD_END)
			ss << ", t=" << thread_id;
		;
		break;

	case EC_SEMAPHORE:
		ss << ", s=" << sem_id;
		break;

	case EC_SYMMETRY:
		ss << ", o=" << obj_id;
		break;

	default:
		ss << ", t=" << thread_id;
		break;
	}

	if (location_id >= 0) {
		ss << ", loc=" << location_id;
	}

	if (may_fail && return_status != 0) {
		ss << ", ret=" << return_status;
	}

	if (type == OBJ_CALL || type == OBJ_RESP) {
		//ss << "    ,class=" << class_name;
		ss << ",function=" << method_name;
//		ss << "    ,index_of_OBJ_CALL=" << index_of_OBJ_CALL;

//		if (retval!=-1) {
//			cout<<retval<<endl;
		if (return_value == 1) {
//		ss << "    ,return ? = " << (int) return_value;
			ss << "    ,return= " << (int) retval;
		}
//		}

	}
	ss << ") ";

	ss << "{ ";
	for (map<int, bool>::iterator it = enable_done.begin();
			it != enable_done.end(); it++) {

		if (it->second) {
			ss << it->first << ", ";
		} else {
			ss << it->first << ":done, ";
		}

	}
	ss << "} ";

	ss << " { ";
	for (map<int, int>::iterator it = quasi_cost.begin();
			it != quasi_cost.end(); it++) {

		ss << it->first << ":" << it->second << ", ";
	}
	ss << "} ";

	return ss.str();
}

string InspectEvent::toString_line() {
	stringstream ss;
	EventCategory cat;

	cat = get_event_category(type);

	ss << "(";

//	ss << "e=" << setw(3) << eid;
//	ss << ", ";

	ss << "t=" << thread_id << "| type= " << event_type_to_string(type) << " ";

	switch (cat) {
	case EC_MUTEX:
		ss << ", m=" << mutex_id;
		if (cond_id != -1)
			ss << ", c[" << cond_id << "]";
		break;

	case EC_COND:
		ss << ", c=" << cond_id;
		if (type == COND_WAIT)
			ss << ", m=" << mutex_id;
		break;

	case EC_RWLOCK:
		ss << ", rwlock_id=" << rwlock_id;
		break;

	case EC_OBJECT:
//		ss << ", o=" << obj_id;
		//    ss <<", obj_val=" << obj_value;
		break;

	case EC_THREAD:
		if (type == THREAD_CREATE)
			ss << ", t=" << child_id;
		else if (type == THREAD_POST_CREATE || type == THREAD_JOIN
				|| type == THREAD_CANCEL)
			ss << ", t=" << child_id;
		else if (type == THREAD_START || type == THREAD_END)
			ss << ", t=" << thread_id;
		;
		break;

	case EC_SEMAPHORE:
		ss << ", s=" << sem_id;
		break;

	case EC_SYMMETRY:
		ss << ", o=" << obj_id;
		break;

	default:
		ss << ", t=" << thread_id;
		break;
	}

	if (location_id >= 0) {
		ss << ", loc=" << location_id;
	}

	if (may_fail && return_status != 0) {
		ss << ", ret=" << return_status;
	}

	if (type == OBJ_CALL || type == OBJ_RESP) {
		//ss << "    ,class=" << class_name;
		ss << "|function=" << method_name;
//		ss << "    ,index_of_OBJ_CALL=" << index_of_OBJ_CALL;

//		if (retval!=-1) {
//			cout<<retval<<endl;
		if (return_value == 1) {
//		ss << "    ,return ? = " << (int) return_value;
			ss << "    |return= " << (int) retval;
		}
//		}

	}
	ss << ")   ";

	return ss.str();
}

bool InspectEvent::communicative(InspectEvent & event) {
	EventCategory my_cat, cat;
	bool retval = false;

	my_cat = get_event_category(type);
	cat = get_event_category(event.type);

	if (this->invalid() || event.invalid())
		return false;
	if ((my_cat != cat)
			&& !((my_cat == EC_MUTEX && cat == EC_COND)
					|| (my_cat == EC_COND && cat == EC_MUTEX)))
		return false;


	return retval;
}

bool InspectEvent::dependent(InspectEvent & event) {
	EventCategory my_cat, cat;
	my_cat = get_event_category(type);
	cat = get_event_category(event.type);

	if (this->invalid() || event.invalid())
		return false;
	if (this->thread_id == event.thread_id)
		return false; //skip if they are from the same thread

	if (event.type == MISC_EXIT)
		return true;

	if (!(my_cat == cat || (my_cat == EC_MUTEX && cat == EC_COND)
			|| (my_cat == EC_COND && cat == EC_MUTEX)))
		return false;

	switch (my_cat) {
	case EC_MUTEX:
	case EC_COND:
		//chao: begin:  added on 9/17/2013
		if ((event.type == COND_SIGNAL && type == MUTEX_UNLOCK) ||
		    (event.type == MUTEX_UNLOCK && type == COND_SIGNAL))
		  return true;
		//chao: end

		if (event.mutex_id != this->mutex_id)
			return false;
		if ((event.type == MUTEX_LOCK || event.type == COND_WAIT_LOCK)
				&& (type == MUTEX_LOCK || type == COND_WAIT_LOCK))
			return true;

		break;

	case EC_RWLOCK:
		if (event.rwlock_id != this->rwlock_id)
			return false;
		if (event.type == RWLOCK_UNLOCK || this->type == RWLOCK_UNLOCK)
			return false;
		if (event.type == RWLOCK_WRLOCK || this->type == RWLOCK_WRLOCK)
			return true;
		break;

	case EC_OBJECT:
		if (event.obj_id != this->obj_id)
			return false;
		if (event.type == OBJ_WRITE && this->type == OBJ_WRITE)
			return true;
		else if (event.type == OBJ_WRITE && this->type == OBJ_READ)
			return true;
		else if (event.type == OBJ_READ && this->type == OBJ_WRITE)
			return true;

		break;

	case EC_THREAD:
		break;

	case EC_SEMAPHORE:
		assert(false);
		break;

	case EC_SYMMETRY:
		break;

	default:
		assert(false);
	}

	return false;
}

bool InspectEvent::can_disable(InspectEvent &event) {
	bool retval = false;

	if (thread_id == event.thread_id)
		return false;

	switch (event.type) {
	case MUTEX_LOCK:
		if (type == MUTEX_LOCK && mutex_id == event.mutex_id)
			retval = true;
		break;

	case RWLOCK_RDLOCK:
		if (type == RWLOCK_WRLOCK && rwlock_id == event.rwlock_id)
			retval = true;
		break;

	case RWLOCK_WRLOCK:
		if ((type == RWLOCK_RDLOCK || type == RWLOCK_WRLOCK)
				&& rwlock_id == event.rwlock_id)
			retval = true;
		break;

	default:
		break;
	}

	return retval;
}

bool InspectEvent::can_enable(InspectEvent &event) {
	bool retval = false;

	if (thread_id == event.thread_id)
		return false;

	switch (type) {
	case MUTEX_UNLOCK:
		if (event.type == MUTEX_LOCK && mutex_id == event.mutex_id)
			retval = true;
		break;

	case THREAD_END:
		if (event.type == THREAD_JOIN && event.child_id == thread_id)
			retval = true;

	default:
		break;
	}

	return retval;
}

bool InspectEvent::operator ==(InspectEvent & event) {
	if (type != event.type)
		return false;
	if (thread_id != event.thread_id)
		return false;
	if (location_id != event.location_id)//this would change?
		return false;
	if (local_state_changed_flag != event.local_state_changed_flag)
		return false;
	return this->semantic_equal(event);
}

bool InspectEvent::operator <(const InspectEvent event) {

	return (eid < event.eid);
}

bool InspectEvent::operator !=(InspectEvent & event) {
	return !(*this == event);
}

InspectEvent& InspectEvent::operator =(InspectEvent ev2) {
	type = ev2.type;

	thread_id = ev2.thread_id;
	location_id = ev2.location_id;
	thread_arg = ev2.thread_arg;

	mutex_id = ev2.mutex_id;
	cond_id = ev2.cond_id;
	obj_id = ev2.obj_id;
	rwlock_id = ev2.rwlock_id;
	sem_id = ev2.sem_id;
	child_id = ev2.child_id;
	retval = ev2.retval;
	return_value = ev2.return_value;

	local_state_changed_flag = ev2.local_state_changed_flag;

#ifdef NLZ_COMM
	future = ev2.future;
	i_mult = ev2.i_mult;
#endif

	
#ifdef RSS_EXTENSION
	obj_value = ev2.obj_value;
	wakeup_time_sec = ev2.wakeup_time_sec;
	wakeup_time_nsec = ev2.wakeup_time_nsec;
	may_fail = ev2.may_fail;
	return_status = ev2.return_status;
	is_recursive_mutex = ev2.is_recursive_mutex;
	eid = ev2.eid;

	class_name = ev2.class_name;
	method_name = ev2.method_name;
	index_of_OBJ_CALL = ev2.index_of_OBJ_CALL;
	inst_id = ev2.inst_id;
#endif//RSS_EXTENSION
	return *this;
}

/**
 *  test whether two events are equal when the thread id is ignored.
 */
bool InspectEvent::semantic_equal(InspectEvent &event) {
	EventCategory ecat;
	bool retval = false;

	ecat = get_event_category(type);
	switch (ecat) {
	case EC_MUTEX:
		retval = mutex_id == event.mutex_id;
		break;
	case EC_COND:
		retval = (mutex_id == event.mutex_id) && (cond_id == event.cond_id);
		break;
	case EC_RWLOCK:
		retval = (rwlock_id == event.rwlock_id);
		break;
	case EC_OBJECT:
	    //retval = obj_id == event.obj_id;
	    retval=inst_id== event.inst_id;// 6.23 for mix031 crash
		break;
	case EC_THREAD:
		retval = child_id == event.child_id;
		break;
	case EC_SEMAPHORE:
		retval = sem_id == event.sem_id;
		break;
	case EC_SYMMETRY:
		retval = (obj_id == event.obj_id);
		break;
	default:
		cout << "unknown event! " << event.toString() << endl;
		break; //assert(false);
	}

	return retval;
}

istream & operator >>(istream &is, EventType &etype) {
	int val;
	is >> val;
	etype = static_cast<EventType>(val);
	return is;
}

ostream & operator <<(ostream &os, EventType etype) {
	int val;
	val = static_cast<int>(etype);
	os << val;
	return os;
}

Socket& operator <<(Socket& sock, EventType etype) {
	int val;
	val = static_cast<int>(etype);
	sock << val;
	return sock;
}

Socket & operator >>(Socket& sock, EventType & type) {
	int val;
	sock >> val;
	type = static_cast<EventType>(val);
	return sock;
}

Socket & operator <<(Socket &sock, EventPermitType perm) {
	int val;
	val = static_cast<int>(perm);
	sock << val;

	return sock;
}

Socket & operator >>(Socket& sock, EventPermitType & perm) {
	int val;
	sock >> val;
	perm = static_cast<EventPermitType>(val);
	return sock;
}

// Target (program-under-test) sends an event to Scheduler
Socket& operator <<(Socket& sock, InspectEvent &event) {
   
	int data[128];
	data[0] = (int) event.type;
	data[1] = (int) event.thread_id;

	data[2] = (int) event.mutex_id;
	data[3] = (int) event.cond_id;

	data[4] = (int) event.location_id;
	data[5] = (int) event.local_state_changed_flag;

	data[6] = (int) event.obj_value;

	data[7] = (int) event.wakeup_time_sec;
	data[8] = (int) event.wakeup_time_nsec;
	data[9] = (int) event.return_status;
	data[10] = (int) event.may_fail;

	data[11] = (int) event.is_recursive_mutex;
	data[12] = (int) event.index_of_OBJ_CALL;
	data[13] = 0;
	data[13] = (int) event.retval;
	data[14] = (int) event.return_value;
	data[15] = (int) event.inst_id;

#ifdef NLZ_COMM
	data[16] = (int) event.i_mult;
	data[17] = (int) event.future;
	char *ptr = (char*) (data + 18);
#else
	char *ptr = (char*) (data + 16);
#endif
	strncpy(ptr, event.method_name.c_str(), 64);

	sock.send_binary(data, sizeof(data));
	return sock;
}

//Scheduler receives an event from Target (program-under-test)
Socket& operator >>(Socket& sock, InspectEvent &event) {
	int data[128];

	sock.recv_binary(data);

	event.type = (EventType) data[0];
	event.thread_id = data[1];
	event.mutex_id = data[2];
	event.cond_id = data[3];
	event.location_id = data[4];
	event.local_state_changed_flag = (bool) data[5];

	event.obj_value = data[6];

	event.wakeup_time_sec = data[7];
	event.wakeup_time_nsec = data[8];
	event.return_status = data[9];
	event.may_fail = data[10];

	event.is_recursive_mutex = data[11];
	event.index_of_OBJ_CALL = data[12];
	event.retval = (int) data[13];
	event.return_value = data[14];
	event.inst_id = data[15];

#ifdef NLZ_COMM
	event.i_mult = data[16];
	event.future = data[17];
	const char *ptr = (char*) (data + 18);
#else
	const char *ptr = (char*) (data + 16);
#endif
	event.method_name = "";
	event.method_name += ptr;

#ifdef RSS_EXTENSION

	static int eid = 1;
	if (event.type == THREAD_START && event.thread_id == 0) {
		eid = 1;
	}
	event.eid = eid++;

	if (data[0] < 0 || data[0] > (int) MANUAL_REST) {
		throw SocketException("corrupted event.type after receive binary");
	} else if (data[1] < -1 || data[1] > 1000000) {
		throw SocketException("corrupted event.thread_id after receive binary");
	} else if (data[2] < -1 || data[2] > 1000000) {
		throw SocketException("corrupted event.mutex_id after receive binary");
	} else if (data[3] < -1 || data[3] > 1000000) {
		if (get_event_category(event.type) == EC_COND) {
			throw SocketException(
					"corrupted event.cond_id after receive binary");
		}
	}

	if (event.type == THREAD_CREATE || event.type == THREAD_POST_CREATE
			|| event.type == THREAD_JOIN
			|| event.type == STATE_CAPTURING_THREAD_POST_CREATE) {
		if (event.child_id < 0) {
			//child has ended already!
			event.child_id = (-1000000 - event.child_id);
			assert(event.child_id >= 0);
		}
	}

	// if the "time-to-wakeup" field is valid, calculate the wakeup time for
	// CLOCK_REALTIME
	if (event.wakeup_time_sec != 0 || event.wakeup_time_nsec != 0) {
		struct timespec ts;
		if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
			event.wakeup_time_sec += ts.tv_sec;
			event.wakeup_time_nsec += ts.tv_nsec;
		}
		cout << endl << "RECEIVED event: " << event.toString() << endl
				<< "         wakeup_time = { " << event.wakeup_time_sec << ", "
				<< event.wakeup_time_nsec << " }" << endl
				<< "         curr_time   = { " << ts.tv_sec << ", "
				<< ts.tv_nsec << " } " << endl << "         wait_time   = "
				<< data[7] << "." << data[8] << endl;
	}

	if (event.type == PROPERTY_ASSERT) {
		//target asertion about to failed
		EventPermitType permit;
		permit = permit_type(event.type);
		sock << static_cast<int>(permit);

		throw AssertException();
	}
#endif //RSS_EXTENSION
	return sock;
}

bool InspectEvent::time_to_wakeup() {
	bool res = true;
	if (wakeup_time_sec != 0 || wakeup_time_nsec != 0) {
		struct timespec ts;
		if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
			long sec = ts.tv_sec - wakeup_time_sec;
			long nsec = (ts.tv_nsec - wakeup_time_nsec) / 1000000;
			long useconds = sec * 1000 + nsec;
			res = (useconds >= 0);
		}
	}
	return res;
}




#ifdef NLZ_EVEC
ostream& operator <<(ostream& os, const std::vector<InspectEvent>& ev_vec){
    for(typename std::vector<InspectEvent>::const_iterator it=ev_vec.begin(); it!=ev_vec.end()-1; ++it){
	os<<it->toString()<<"\n";
    }
    os<<(ev_vec.end()-1)->toString();
    return os;
}

ostream& operator <<(ostream& os, std::queue<InspectEvent> ev_queue){
    while(ev_queue.empty()==false){
	os<<ev_queue.front().toString()<<"\n";
	ev_queue.pop();
    }
    return os;
}
#endif
