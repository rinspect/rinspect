#ifndef __INSPECTOR__EVENT_HH__
#define __INSPECTOR__EVENT_HH__

#include "naling.def"
#include <string> 
#include <cassert>
#include <set>
#include <iostream>
#include "inspect_util.hh"
#include <map>
#ifdef NLZ_COMM
#include <queue>
#endif

using std::map;
using std::string;
using std::set;
using std::istream;
using std::ostream;

#define DEF_EVENT_CODE(EV, STR, EV_PERM, CAT)   EV,
enum EventType {
#include "inspect_event.def"
	UNKNOWN
};
#undef DEF_EVENT_CODE

#define DEF_EVENT_CODE(EV, STR, EV_PERM, CAT)   EV_PERM,
enum EventPermitType {
#include "inspect_event.def"
	UNKNOWN_PERM
};
#undef DEF_EVENT_CODE

#ifdef __cplusplus
extern "C" {
#endif

  //extern const int DummyLocation;

#ifdef __cplusplus
}
#endif

string event_type_to_string(EventType);
EventType string_to_event_type(string str);

EventPermitType permit_type(EventType);

enum EventCategory {
	EC_MUTEX,
	EC_COND,
	EC_RWLOCK,
	EC_OBJECT,
	EC_THREAD,
	EC_SEMAPHORE,
	EC_SYMMETRY,
	EC_GLOBAL,
	EC_LOCAL,
	EC_CAS,
	EC_PROPERTY,
	EC_DELAY,
	EC_COMM,
	EC_ERROR = 9999
};

EventCategory get_event_category(EventType et);
string event_type_to_string(EventType et);

Socket& operator <<(Socket& sock, EventCategory ecls);
Socket& operator >>(Socket& sock, EventCategory &ecls);

Socket& operator <<(Socket& sock, EventType type);
Socket& operator >>(Socket& sock, EventType &type);

Socket & operator <<(Socket& sock, EventPermitType perm);
Socket & operator >>(Socket& sock, EventPermitType & perm);

istream & operator >>(istream &is, EventCategory &ecls);
istream & operator >>(istream &is, EventType &etype);

ostream & operator <<(ostream &os, EventCategory ecls);
ostream & operator <<(ostream &os, EventType etype);


/**
 *  InspectEvent encaptures the information of communication events 
 * 
 *  the duplicate method will only duplicate threee fields: 
 *    event_type, event_id, and thread_id, 
 * 
 *  the other fields will be handled according to the context
 * 
 */

class InspectEvent {
public:
//	map<int, int> index_of_thread;
	InspectEvent();

	void init();

	void init_mutex_init(int tid, int mid);
	void init_mutex_destroy(int tid, int mid);
	void init_mutex_lock(int tid, int mid);
	void init_mutex_trylock(int tid, int mid);
	void init_mutex_unlock(int tid, int mid);

	void init_cond_init(int tid, int cid);
	void init_cond_destroy(int tid, int cid);
	void init_cond_wait(int tid, int cid, int mid);
	void init_cond_signal(int tid, int cid);
	void init_cond_broadcast(int tid, int cid);
	void init_cond_timedwait(int tid, int cid);

	void init_cond_wait_lock(int tid, int cid, int mid);
	void init_cond_wait_unlock(int tid, int cid, int mid);

	void init_rwlock_init(int tid, int rwid);
	void init_rwlock_destroy(int tid, int rwlid);
	void init_rwlock_rdlock(int tid, int rwlid);
	void init_rwlock_wrlock(int tid, int rwlid);
	void init_rwlock_unlock(int tid, int rwlid);

	void init_thread_start(int tid);
	void init_thread_end(int tid);
	void init_thread_create(int tid, int cid);
	void init_thread_join(int tid, int cid);
	void init_thread_pre_create(int tid);
	void init_thread_post_create(int tid, int cid);

	void init_state_capturing_thread_start(int tid);
	void init_state_capturing_thread_pre_create(int tid);
	void init_state_capturing_thread_post_create(int tid, int cid);

	void init_obj_register(int tid, int oid);
	void init_obj_read(int tid, int oid);
	void init_obj_write(int tid, int oid);
#ifdef NLZ_PREL
    //  void init_cache_obj_write(int tid, int oid);
    //    void init_pause_obj_read(int tid, int oid);
#endif

	void init_obj_call(int tid, int oid, string fname, int method_id);
	void init_obj_resp(int tid, int oid, string fname, int method_id,
			char* retval, int return_value);
//	void init_obj_resp(int tid, int oid, string fname, int method_id);


	void init_symm_point(int tid, int ptno);
	void init_state_req(int tid);
	void init_state_ack(int tid);

	void init_local_info(int tid, int pos, int flag);
	void init_local_state_begin(int tid);
	void init_local_state_end(int tid);
	void init_local_int(int tid);
	void init_local_double(int tid);
	void init_local_binary(int tid);

	void init_cas_instr(int tid, int oid);
	void init_cas2_instr(int tid, int oid);

	bool may_have_side_effect();
	bool must_happen_before(InspectEvent * another);
	bool is_concurrent_with(InspectEvent * another);

	EventCategory event_category() {
		return get_event_category(type);
	}

	string toString();
	string toString_line();
	string toString_quasi();
	string toXML(); //added, 4/7/2012
	string toJet(); //added, 4/7/2012

	void serialize(ostream & os);
	void deserialize(istream & is);

	bool dependent(InspectEvent &event);
	bool communicative(InspectEvent &event);
	bool is_modification_by_const();

	bool operator ==(InspectEvent & event);
	bool operator !=(InspectEvent & event);
	bool operator <(const InspectEvent event);

	InspectEvent & operator =(InspectEvent ev2);

	inline bool valid() {
		return (type != UNKNOWN && thread_id >= 0);
	}
	inline bool invalid() {
		return (type == UNKNOWN || thread_id < 0);
	}
	inline void clear() {
		this->init();
	}

	bool can_disable(InspectEvent &event);
	bool can_enable(InspectEvent &event);

	bool semantic_equal(InspectEvent &event);

#ifdef RSS_EXTENSION
	void init_blocking(int tid);    //added on 4/7/2012
	void init_unblocking(int tid);  //added on 4/7/2012
	void init_exit(int tid);        //added on 4/7/2012
	bool is_blocking();    //added on 4/7/2012
	bool is_unblocking();  //added on 4/7/2012
	bool time_to_wakeup(); //added on 4/7/2012
#endif//RSS_EXTENSION
public:
	EventType type;     //  0. type
	int thread_id;      //  1. the thread that initiate the event

//   string thread_nm;   //  () name of the thread routine

	union {
		int mutex_id;       //  mutex-related
		int rwlock_id;      //  rwlocks
		int obj_id;         //  ordinary shared variables
		int sem_id;         //  semaphores
		void * thread_arg;  //  thread_argument
		int point_no;       //  piont number of the symmetry point
	};

	union {
		int cond_id;        //  condition var related
		int child_id;       //  create/join thread
		int old_value;
	};

	map<int,bool> enable_done;//enable_done set, key means eid enabled, value means whether it's done, false means it's done
	map<int,int> quasi_cost;

	int location_id;    //  the location in the program
						//  it is equivalent to the program counter
	bool local_state_changed_flag; // . whether the local state changed after executing the
								   //     last global transition
#ifdef NLZ_COMM
public:
    int future;  // whether it is a future event due to relax memory model
    int i_mult;   // the index of a event, when it is sent in a stream vector form, -1 means the last event.
#endif
    
    
public:
	static InspectEvent dummyEvent;

    
#ifdef RSS_EXTENSION
public:
	int obj_value;
	int wakeup_time_sec;
	int wakeup_time_nsec;
	int may_fail;
	int return_status;
	int is_recursive_mutex;
	int eid;

	string thread_function_name; //the function name of the thread(each thread_function has a CFG for the thread)
	string method_name;
	string class_name;
	int index_of_OBJ_CALL;
	char* retval;
	int return_value;

  int inst_id;       // unique ID of the LLVM instruction in .bc file

#endif//RSS_EXTENSION
};

Socket& operator <<(Socket& sock, InspectEvent &event);
Socket& operator >>(Socket& sock, InspectEvent &event);

#endif



#ifdef NLZ_EVEC
ostream& operator <<(ostream& os, const std::vector<InspectEvent>& ev_vec);
ostream& operator <<(ostream& os, std::queue<InspectEvent> ev_queue);
#endif




//
//#ifdef RSS_EXTENSION
//class lin_Checker {
//public:
//	lin_Checker();
//	virtual ~lin_Checker();
//
//	void build_trace_dictionary();
//
//	void read_lin_traces_txt(string fileName);
//
//	bool check_trace();
//
//	bool linearized_traces(/*trace*/);
//
//
//public:
//
//
//};
//
//#endif
