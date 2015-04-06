#include "clap_event.hh"

int Event::count = 1;

#define DEF_EVENT_CODE(EV, STR, EV_PERM, CAT)   CAT,

EventCategory events_cat[] = {
#include "clap_event.def"
		EC_ERROR };

#undef DEF_EVENT_CODE

#define DEF_EVENT_CODE(EV, STR, EV_PERM, CAT)   STR, 
const char * eventstr[] = {
#include "clap_event.def"
		"unknown" };
#undef DEF_EVENT_CODE

EventCategory get_event_category(EventType et) {
	int idx;
	idx = (int) et;
	return events_cat[idx];
}

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

Event::Event(EventType typ, int tid, int var, int loc) {
	type = typ;
	thread_id = tid;
	mutex_id = var;
	location_id = loc;
	prev = NULL;
	eid = count++;
	index_of_OBJ_CALL = 0;
}

string Event::toXML() {
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

	case EC_OBJECT:
		ss << " <objId> " << obj_id << " </objId> ";
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

	default:
		break;
	}

	if (location_id >= 0) {
		ss << " <locInfoId> " << location_id << " </locInfoId> ";
	}

	return ss.str();
}

string Event::toJet() {
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
			ss << "read [var \"obj_" << obj_id << " src " << location_id
					<< " ] ] ";
		} else if (type == OBJ_WRITE) {
			eid += 1;
			ss << "event [ eid " << eid << " tid " << thread_id << " ";
			ss << "write [var \"obj_" << obj_id << " src " << location_id
					<< " ] ] ";
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

string Event::prev_to_string() {
	stringstream ss;

	ss << "{ ";

	map<int,int>::iterator it;
	for (it = prev_events.begin(); it != prev_events.end(); it++) {
		if (it != prev_events.begin())
			ss << ", ";
		ss <<it->first;
	}

	ss << " }";

	return ss.str();

}

string Event::toString() {
	stringstream ss;
	EventCategory cat;

	cat = get_event_category(type);

	ss << "(";

	ss << "e=" << setw(4) << eid;
	ss << ", ";

	ss << "t=" << setw(4) << thread_id;
	ss << ", " << event_type_to_string(type) << " ";

	switch (cat) {
	case EC_MUTEX:
		ss << ", m=" << setw(4) << mutex_id;
		break;

	case EC_COND:
		ss << ", c=" << setw(4) << cond_id;
		if (type == COND_WAIT)
			ss << ", m=" << mutex_id;
		break;

	case EC_OBJECT:
		ss << ", o=" << setw(4) << obj_id;
		//    ss <<", obj_val=" << obj_value;
		break;

	case EC_THREAD:
		if (type == THREAD_CREATE)
			ss << ", t=" << setw(4) << child_id;
		else if (type == THREAD_POST_CREATE || type == THREAD_JOIN
				|| type == THREAD_CANCEL)
			ss << ", t=" << setw(4) << child_id;
		else if (type == THREAD_START || type == THREAD_END)
			ss << "        ";
		break;

	default:
		ss << ", t=" << thread_id;
		break;
	}

	if (location_id >= 0) {
		ss << ", loc=" << location_id;
	}

	/*
	 if (lockset.size() != 0) {
	 // ss << ", lkset=" << lockset.toString();
	 }
	 if (varset.size() != 0) {
	 ss << ", varset=" << varset.toString();
	 }
	 if (condset.size() != 0) {
	 ss << ", condset=" << lockset.toString();
	 }
	 */
	if (!class_name.empty())
		ss << "    ,class=" << class_name;
	if (!method_name.empty())
		ss << "    ,function=" << method_name;
	if (index_of_OBJ_CALL > 0)
		ss << "    ,index_of_OBJ_CALL=" << index_of_OBJ_CALL;

	ss << ")";

	return ss.str();
}

