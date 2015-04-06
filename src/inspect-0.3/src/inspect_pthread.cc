#include "naling.def"
#ifdef NLZ_FLAG
#include "debug.hpp"
#include <sched.h>
#include "memory_model_enum.hh"
#endif

#include "inspect_pthread.hh"
#include "inspect_event.hh"
#include "inspect_exception.hh"
#include "object_table.hh"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring> 
#include <stdio.h>


using namespace std;

#ifdef RSS_EXTENSION
extern bool skip_clap;     //defined in inspect_clap.cc
extern bool target_trace;  //defined in inspect_clap.cc
extern bool lin_check;     //defined in inspect_clap.cc
extern bool lin_serial;    //defined in inspect_clap.cc
extern ofstream myfile;

#endif

#ifdef NLZ_FLAG
#define MAX_BOUND 1
int g_max_bound=-1;
MemoryModel g_memory_model=SC_MODEL;  // enum type MemoryModel defined in inspect_event.hh
#endif



const int SC_THREAD_ID = 10000;

pthread_cond_t sc_start;
pthread_mutex_t sc_lock;

void inspect_exit(int status) {
	inspect_thread_end();
	exit(status);
}

void inspect_thread_start(const char * func_name) {
	int thread_id;
	Socket * socket;
	EventPermitType permit;

	thread_id = g_thread_index.insert(pthread_self());
	socket = g_socket_index.register_by_tid(thread_id);

	if (socket == NULL) {
		cerr << "Target: cannot connect to Inspect, start a free run!" << endl;
		skip_clap = true;
		return;
	}

	InspectEvent event;
	event.init_thread_start(thread_id);
	(*socket) << event;
	(*socket) >> permit;
	assert( permit == THREAD_START_PERM);


#ifdef NLZ_FLAG
	if (thread_id==0){
             int tmp_int_g_memory_model;
	     (*socket) >> tmp_int_g_memory_model;
	     g_memory_model = (MemoryModel) tmp_int_g_memory_model;
	     switch (g_memory_model){
	     case SC_MODEL:
		 cout<<"\n------>> target runs in SC_MODEL\n"<<endl;
		 break;
	     case TSO_MODEL:
		 cout<<"\n------>> target runs in TSO_MODEL\n"<<endl;
		 break;
	     case PSO_MODEL:
		 cout<<"\n------>> target runs in PSO_MDOEl\n"<<endl;
		 break;
	     default:
		 cout<<"unknown MODEL!!"<<endl;
	     }
	     int tmp_bound=0;
	     (*socket)>> tmp_bound;
	     g_max_bound=tmp_bound;
        }
#endif
	
#ifdef RSS_EXTENSION
	int config;
	(*socket) >> config;
	if (thread_id == 0) {
		// main thread
//		cout<<"config : "<<config<<endl;
		target_trace = (config & 1) != 0;
		lin_check = (config & (1 << 1)) != 0;
		lin_serial = (config & (1 << 2)) != 0;
                
//		lin_serial=false;

		if (lin_check) {

			if (lin_serial == true) {    //open a file to record the trace
				if (myfile.is_open()) {
//				cout << "open" << endl;
				} else {
//				cout << "close" << endl;
					myfile.open("trace", ios::out | ios::app | ios::binary);
					myfile << "{" << endl;
				}
//			cout << "start : thread_id= " << thread_id << endl;
			} else {    //read the trace


			}
		}
	}
#endif//RSS_EXTENSION
}

void inspect_thread_end() {
	int thread_id;
	Socket * socket = NULL;
	EventPermitType permit;

	thread_id = g_thread_index.get_my_thread_id();

	socket = g_socket_index.get_socket(thread_id);
	assert( socket != NULL);
#ifdef NLZ_FLAG
	switch(g_memory_model){
	case TSO_MODEL:
	{  
	    MemoryOpBuffer& buffer = g_tso_buffers[thread_id];
	    while (!buffer.empty()){
		InspectEvent obj_event;
		MemoryOperation& front_mo = g_tso_buffers[thread_id].front();	
		int obj_id = g_object_index.get_obj_id(front_mo.addr);
		obj_event.init_obj_write(thread_id, obj_id);
		obj_event.inst_id = front_mo.inst_id;
		obj_event.i_mult = -1;  //6.10  

		(*socket) << obj_event;
		(*socket) >> permit;
		assert(permit == OBJ_WRITE_PERM);
		*((int*)buffer.front().addr) = buffer.front().value;
		buffer.pop();
	    }
	}
	
	    break;
	case PSO_MODEL:
	{
	    vector< MemoryOperation* > vec_op_front;
	    bool isAtomic=false;
           
	    while(buffer_has_value())
	    {	  
		send_write_vector(isAtomic);
	    
		int per_oid=0;
	    	(*socket) >> permit;
	    	(*socket) >> per_oid;
		
	    
		void* tmp_addr;
		if(permit == OBJ_WRITE_PERM && per_oid!=0){
		    for (hash_map<void*, MemoryOpBuffer>::iterator it=g_pso_buffers[thread_id].begin() ; it!=g_pso_buffers[thread_id].end(); ++it){
			if (it->second.empty()) continue;
			MemoryOperation* front_mo = &(it->second.front());
			int obj_id = g_object_index.get_obj_id(front_mo->addr);
			if(per_oid == obj_id)  {	
			    tmp_addr= front_mo->addr;   
			    *(int*)g_pso_buffers[thread_id][tmp_addr].front().addr = g_pso_buffers[thread_id][tmp_addr].front().value;
			    g_pso_buffers[thread_id][tmp_addr].pop();
			    break;
			}
		    }
		}
		else{
		    //cout<<"permit read"<<endl;
		}
	    }
	}
	break;
	    
	default:
	    break;
	}
		  
	    
#endif	
	InspectEvent event;
	
	event.init_thread_end(thread_id);
	(*socket) << event;
	(*socket) >> permit;
	
	assert( permit == THREAD_END_PERM);	
	g_socket_index.remove(thread_id);
#ifdef RSS_EXTENSION
	if (lin_check) {
		if (thread_id == 0) {

			if (lin_serial == true) {
				myfile << "}" << endl;
				myfile.close();
//			cout << "end : thread_id= " << thread_id << endl;
			}
			else{

			}
		}
	}
#endif//RSS_EXTENSION
}

void inspect_obj_reg(void * obj_addr) {
	int obj_id;
	bool cflag;

	obj_id = g_object_index.add(obj_addr);
}

void inspect_obj_read(void * obj_addr, int inst_id) {
	int obj_id, thread_id;
	Socket * socket = NULL;

	try {
		if (!g_object_index.is_member(obj_addr))
			obj_id = g_object_index.add(obj_addr);

		assert( g_object_index.is_member(obj_addr));

		obj_id = g_object_index.get_obj_id(obj_addr);
		assert( obj_id > 0);

		thread_id = g_thread_index.get_my_thread_id();
		socket = g_socket_index.get_socket(thread_id);
		assert( socket != NULL);

		InspectEvent obj_event;
		obj_event.init_obj_read(thread_id, obj_id);
                obj_event.inst_id = inst_id;
		(*socket) << obj_event;

		EventPermitType permit;
		(*socket) >> permit;
		assert( permit == OBJ_READ_PERM);

	} catch (NullObjectException &e) {
		cerr << "Error: shared object is null....\n";
	}


}

void inspect_obj_write(void * obj_addr, int inst_id) {
	int obj_id, thread_id;
	Socket * socket = NULL;

	obj_id = g_object_index.get_obj_id(obj_addr);

	if (obj_id == -1) {
		return;
		obj_id = g_object_index.add(obj_addr);
	}
	assert( obj_id > 0);

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert( socket != NULL);

	InspectEvent obj_event;
	obj_event.init_obj_write(thread_id, obj_id);
        obj_event.inst_id = inst_id;
	(*socket) << obj_event;

	EventPermitType permit;
	(*socket) >> permit;
	
	assert(permit == OBJ_WRITE_PERM);
	

}

InspectEvent * inspect_obj_call(char *fname, void * obj_addr) {
	int obj_id, thread_id, method_id;
	Socket * socket = NULL;

	//  assert( g_object_index.is_member(obj_addr) );

	obj_id = g_object_index.get_obj_id(obj_addr);

	assert( obj_id > 0);

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert( socket != NULL);

	// TO-DO: convert 'fname' into 'method_id'
	method_id = 0;

	InspectEvent obj_event;
	obj_event.init_obj_call(thread_id, obj_id, fname, method_id /*NEW*/);
	(*socket) << obj_event;

	EventPermitType permit;
	(*socket) >> permit;
	assert(permit == OBJ_CALL_PERM);

	InspectEvent *ret = new InspectEvent();
	ret->init_obj_call(thread_id, obj_id, fname, method_id /*NEW*/);
//	cout << ret->toString() << endl;
//	cout <<"----"<< obj_event.toString() << endl;
	return ret;

//	cout << obj_event.toString() << endl;
}

InspectEvent * inspect_obj_resp(char *fname, void * obj_addr, char* retval,
		int return_value) {

	int obj_id, thread_id, method_id;
	Socket * socket = NULL;

	//  assert( g_object_index.is_member(obj_addr) );

	obj_id = g_object_index.get_obj_id(obj_addr);

	assert( obj_id > 0);

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert( socket != NULL);

	// TO-DO: convert 'fname' into 'method_id'
	method_id = 0;

	InspectEvent obj_event;

	obj_event.init_obj_resp(thread_id, obj_id, fname, method_id, retval,
			return_value/*NEW*/);

	(*socket) << obj_event;

	EventPermitType permit;
	(*socket) >> permit;
	assert(permit == OBJ_RESP_PERM);

	InspectEvent *ret = new InspectEvent();
	ret->init_obj_resp(thread_id, obj_id, fname, method_id, retval,
			return_value/*NEW*/);
//	ret->retval = "1";
//	cout << ret->toString() << endl;


//	cout <<"----"<< obj_event.toString() << endl;
//	printf("return value: %d\n", obj_event.retval);
	return ret;
}

void inspect_symmetry_point(int point_no) {
	int thread_id;
	Socket * socket = NULL;

	assert(point_no >= 0);

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert(socket != NULL);

	InspectEvent symm_event;
	symm_event.init_symm_point(thread_id, point_no);
	(*socket) << symm_event;

	EventPermitType permit;
	(*socket) >> permit;
	assert(permit == SYMM_POINT_PERM);
}


void inspect_assert() 
{
  int thread_id;
  Socket * socket = NULL;
  
  thread_id = g_thread_index.get_my_thread_id();
  socket = g_socket_index.get_socket(thread_id);
  assert(socket != NULL);
  
  InspectEvent assert_fail_event;
  assert_fail_event.type = PROPERTY_ASSERT;
  (*socket) << assert_fail_event;

  EventPermitType permit;
  (*socket) >> permit;
  assert(permit == PROPERTY_ASSERT_PERM);
}

int inspect_get_thread_id() {
	return g_thread_index.get_my_thread_id();
}

void inspect_local_info(int position, enum LOCAL_STATE_FLAG flag) {//what is local_info, special event type
	int thread_id;
	Socket * socket = NULL;
	InspectEvent event;

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert(socket != NULL);

	event.init_local_info(thread_id, position, flag);
	(*socket) << event;

	EventPermitType permit;
	(*socket) >> permit;
	assert(permit == LOCAL_INFO_PERM);

}

void inspect_local_snapshot_begin() {
	int thread_id;
	Socket * socket = NULL;

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert(socket != NULL);

	InspectEvent event;

	event.init_local_state_begin(thread_id);
	(*socket) << event;

	EventPermitType permit;
	(*socket) >> permit;
	assert(permit == LOCAL_STATE_BEGIN_PERM);
}

void inspect_local_snapshot_end() {
	int thread_id;
	Socket * socket = NULL;
	InspectEvent event;

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert(socket != NULL);

	event.init_local_state_end(thread_id);
	(*socket) << event;

	EventPermitType permit;
	(*socket) >> permit;
	assert(permit == LOCAL_STATE_END_PERM);
}

void inspect_local_int(int val) {
	int thread_id;
	Socket * socket = NULL;
	InspectEvent event;
	EventPermitType permit;

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert(socket != NULL);

	event.init_local_int(thread_id);
	event.obj_id = val;

	(*socket) << event;

	(*socket) >> permit;
	assert(permit == LOCAL_INT_PERM);
}

void inspect_local_double(double val) {
	int thread_id;
	Socket * socket = NULL;
	InspectEvent event;
	EventPermitType permit;

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert(socket != NULL);

	event.init_local_double(thread_id);

	char *ptr = (char*) &val;

	memcpy(&event.mutex_id, ptr, 4);
	memcpy(&event.cond_id, ptr + 4, 4);

	(*socket) << event;

	(*socket) >> permit;
	assert(permit == LOCAL_DOUBLE_PERM);
}

void inspect_local_binary(int sz, void * addr) {
	int thread_id;
	Socket * socket = NULL;
	InspectEvent event;
	EventPermitType permit;

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert(socket != NULL);

	event.init_local_binary(thread_id);
	(*socket) << event;

	assert(sz >= 0);
	socket->send_binary(addr, sz);

	(*socket) >> permit;
	assert(permit == LOCAL_BINARY_PERM);
}

/**
 *   this is the wrapper functions for the pthread libraries
 * 
 */

int inspect_thread_create(pthread_t * thread, const pthread_attr_t * attr,
		void *(*start_routine)(void*), void * arg) {
	int retval, myself, child;
	Socket * socket = NULL;
	EventPermitType permit;
	InspectEvent event0, event;

	myself = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(myself);
	assert( socket != NULL);

	event0.init_thread_pre_create(myself);
	(*socket) << event0;

	(*socket) >> permit;
	assert(permit == THREAD_PRE_CREATE_PERM);

	retval = pthread_create(thread, attr, start_routine, arg);
	g_thread_index.insert(*thread);

	child = g_thread_index.get_thread_id(*thread);

	event.init_thread_post_create(myself, child);
	(*socket) << event;

	(*socket) >> permit;
	assert(permit == THREAD_POST_CREATE_PERM);

	return retval;
}

void inspect_thread_exit(void *value_ptr) {
	inspect_thread_end();
	pthread_exit(value_ptr);
}

void inspect_thread_cancel(pthread_t thread, int location_id) {
	inspect_thread_end();
	pthread_cancel(thread);
}

int inspect_thread_join(pthread_t thread, void **value_ptr) {
	int myself, child, retval;
	Socket * socket;
	EventPermitType permit;

	myself = g_thread_index.get_my_thread_id();
	child = g_thread_index.get_thread_id(thread);

	InspectEvent event;
	event.init_thread_join(myself, child);

	socket = g_socket_index.get_socket(myself);
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;

	if (permit != THREAD_JOIN_PERM) {
	    //cout << "actual received permit is : " << permit << endl;
		assert(permit == THREAD_JOIN_PERM);
	}

	retval = pthread_join(thread, value_ptr);
	g_thread_index.remove_by_thread_id(child);
	return retval;
}

int inspect_mutex_init(pthread_mutex_t * mutex,
		const pthread_mutexattr_t * attr) {
	int retval, mutex_id, thread_id;
	Socket * socket;
	EventPermitType permit;

	mutex_id = g_mutex_index.add(mutex);
	assert(mutex_id > 0);

	thread_id = g_thread_index.get_my_thread_id();
	assert(thread_id >= 0);

	retval = pthread_mutex_init(mutex, attr);

	InspectEvent event;
	event.init_mutex_init(thread_id, mutex_id);

	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == MUTEX_INIT_PERM);

	return retval;
}

int inspect_mutex_destroy(pthread_mutex_t * mutex) {
	int retval, mutex_id, thread_id;
	Socket * socket;
	EventPermitType permit;
	InspectEvent event;

	thread_id = g_thread_index.get_my_thread_id();
	mutex_id = g_mutex_index.get_mutex_id((void*) mutex);
	assert( mutex_id > 0);
	g_mutex_index.remove((void *) mutex);

	retval = pthread_mutex_destroy(mutex);

	event.init_mutex_destroy(thread_id, mutex_id);
	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == MUTEX_DESTROY_PERM);

	return retval;
}

int inspect_mutex_lock(pthread_mutex_t *mutex) {
	Socket * socket = NULL;
	int mutex_id, thread_id;
	EventPermitType permit;
	InspectEvent event;

	thread_id = g_thread_index.get_my_thread_id();
	mutex_id = g_mutex_index.get_mutex_id((void*) mutex);
	assert( mutex_id > 0);
	assert( thread_id >= 0);

	event.init_mutex_lock(thread_id, mutex_id);

	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == MUTEX_LOCK_PERM);
	return 0;
}

int inspect_mutex_unlock(pthread_mutex_t *mutex) {
	Socket * socket = NULL;
	int mutex_id, thread_id;
	EventPermitType permit;
	InspectEvent event;

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_my_socket();
	mutex_id = g_mutex_index.get_mutex_id((void*) mutex);

	assert( thread_id >= 0);
	assert( mutex_id > 0);
	assert( socket != NULL);

	event.init_mutex_unlock(thread_id, mutex_id);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == MUTEX_UNLOCK_PERM);
	return 0;
}

int inspect_mutex_trylock(pthread_mutex_t *mutex) {
	cerr << "have not implemented yet!! \n";
	assert(false);
	return 0;
}

/**
 *  initialize a conditinal variable
 */
int inspect_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr) {
	int retval, cond_id, thread_id;
	Socket * socket;
	EventPermitType permit;
	InspectEvent event;

	cond_id = g_cond_index.add(cond);
	thread_id = g_thread_index.get_my_thread_id();
	retval = pthread_cond_init(cond, attr);

	event.init_cond_init(thread_id, cond_id);
	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == COND_INIT_PERM);
	return retval;
}

int inspect_cond_destroy(pthread_cond_t * cond) {
	int ret_val, cond_id, thread_id;
	Socket * socket;
	EventPermitType permit;
	InspectEvent event;

	thread_id = g_thread_index.get_my_thread_id();
	cond_id = g_cond_index.get_cond_id(cond);
	assert( cond_id > 0);
	g_cond_index.remove(cond);  //chao: added on 1/10/2013

	ret_val = pthread_cond_destroy(cond);

	event.init_cond_destroy(thread_id, cond_id);
	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == COND_DESTROY_PERM);

	return ret_val;
}

int inspect_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex) {
	int cond_id, thread_id, mutex_id;
	Socket * socket;
	EventPermitType permit;
	InspectEvent pre_wait, wait_event, post_wait;

	cond_id = g_cond_index.get_cond_id(cond);
	thread_id = g_thread_index.get_my_thread_id();
	mutex_id = g_mutex_index.get_mutex_id(mutex);

	assert( cond_id > 0);

	pre_wait.init_mutex_unlock(thread_id, mutex_id);
	wait_event.init_cond_wait(thread_id, cond_id, mutex_id);
	post_wait.init_mutex_lock(thread_id, mutex_id);

//   pre_wait.init_cond_wait_unlock(thread_id, cond_id, mutex_id);
//   wait_event.init_cond_wait(thread_id, cond_id, mutex_id); 
//   post_wait.init_cond_wait_lock(thread_id, cond_id, mutex_id);

	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << pre_wait;
	(*socket) >> permit;
	assert(permit == MUTEX_UNLOCK_PERM);
//   assert(permit == COND_WAIT_UNLOCK_PERM);

	(*socket) << wait_event;
	(*socket) >> permit;
	assert(permit == COND_WAIT_PERM);

	(*socket) << post_wait;
	(*socket) >> permit;
	assert(permit == MUTEX_LOCK_PERM);
//   assert(permit == COND_WAIT_LOCK_PERM);

	return 0;
}

int inspect_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex,
		const struct timespec * abstime) {
	assert(false);
	return 0;
}

int inspect_cond_broadcast(pthread_cond_t *cond) {
	int cond_id, thread_id;
	Socket * socket;
	EventPermitType permit;
	InspectEvent event;

	cond_id = g_cond_index.get_cond_id(cond);
	thread_id = g_thread_index.get_my_thread_id();

	event.init_cond_broadcast(thread_id, cond_id);
	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == COND_BROADCAST_PERM);
	return 0;
}

int inspect_cond_signal(pthread_cond_t *cond) {
	int cond_id, thread_id;
	Socket * socket;
	EventPermitType permit;
	InspectEvent event;

	cond_id = g_cond_index.get_cond_id(cond);
	thread_id = g_thread_index.get_my_thread_id();

	assert( cond_id > 0);
	event.init_cond_signal(thread_id, cond_id);
	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == COND_SIGNAL_PERM);
	return 0;
}

int inspect_rwlock_init(pthread_rwlock_t * rwlock,
		const pthread_rwlockattr_t * attr) {
	int rwlock_id, thread_id;
	Socket * socket;
	EventPermitType permit;

	rwlock_id = g_object_index.add(rwlock);
	thread_id = g_thread_index.get_my_thread_id();

	assert( thread_id >= 0);
	assert( rwlock_id > 0);

	InspectEvent event;
	event.init_rwlock_init(thread_id, rwlock_id);
	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == RWLOCK_INIT_PERM);
	return 0;
}

int inspect_rwlock_destroy(pthread_rwlock_t * rwlock) {
	int rwlock_id, thread_id;
	Socket * socket;
	EventPermitType permit;
	InspectEvent event;

	rwlock_id = g_object_index.get_obj_id(rwlock);
	thread_id = g_thread_index.get_my_thread_id();

	assert( thread_id >= 0);
	assert( rwlock_id > 0);

	event.init_rwlock_destroy(thread_id, rwlock_id);
	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == RWLOCK_DESTROY_PERM);
	return 0;
}

int inspect_rwlock_rdlock(pthread_rwlock_t * rwlock) {
	int rwlock_id, thread_id;
	Socket * socket;
	EventPermitType permit;
	InspectEvent event;

	rwlock_id = g_object_index.get_obj_id(rwlock);
	thread_id = g_thread_index.get_my_thread_id();

	assert( thread_id >= 0);
	assert( rwlock_id > 0);

	event.init_rwlock_rdlock(thread_id, rwlock_id);
	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == RWLOCK_RDLOCK_PERM);
	return 0;
}

int inspect_rwlock_tryrdlock(pthread_rwlock_t * rwlock) {
	cerr << "Error: this wrapper has not been implemented yet!\n";
	assert(rwlock != NULL);
	assert(false);
	return -1;
}

int inspect_rwlock_wrlock(pthread_rwlock_t * rwlock) {
	int rwlock_id, thread_id;
	Socket * socket;
	EventPermitType permit;
	InspectEvent event;

	rwlock_id = g_object_index.get_obj_id(rwlock);
	thread_id = g_thread_index.get_my_thread_id();

	assert( thread_id >= 0);
	assert( rwlock_id > 0);

	event.init_rwlock_wrlock(thread_id, rwlock_id);
	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == RWLOCK_WRLOCK_PERM);
	return 0;
}

int inspect_rwlock_trywrlock(pthread_rwlock_t * rwlock) {
	cerr << "this wrapper have not been implemented yet!\n";
	assert( rwlock != NULL);
	assert(false);
	return -1;
}

int inspect_rwlock_unlock(pthread_rwlock_t * rwlock) {
	int rwlock_id, thread_id;
	Socket * socket = NULL;
	EventPermitType permit;
	InspectEvent event;

	rwlock_id = g_object_index.get_obj_id(rwlock);
	thread_id = g_thread_index.get_my_thread_id();

	assert( thread_id >= 0);
	assert( rwlock_id > 0);

	event.init_rwlock_unlock(thread_id, rwlock_id);
	socket = g_socket_index.get_my_socket();
	assert( socket != NULL);

	(*socket) << event;
	(*socket) >> permit;
	assert(permit == RWLOCK_UNLOCK_PERM);
	return 0;
}

int inspect_thread_attr_init(pthread_attr_t *attr) {
	return pthread_attr_init(attr);
}

int inspect_thread_attr_destroy(pthread_attr_t *attr) {
	return pthread_attr_destroy(attr);
}

int inspect_mutexattr_destroy(pthread_mutexattr_t *attr) {
	return pthread_mutexattr_destroy(attr);
}

int inspect_mutexattr_init(pthread_mutexattr_t *attr) {
	return pthread_mutexattr_init(attr);
}

/* test whether the stateful search is enabled or not
 */
int is_stateful_search() {
	char * flag;
	flag = getenv("INSPECT_STATEFUL_FLAG");
	if (flag == NULL)
		return false;

	return ::strcmp(flag, "1") == 0;
}


#ifdef NLZ_COMM

#include <ext/hash_map>
using __gnu_cxx::hash_map;
hash_map<int, MemoryOpBuffer*> p_buffers_commit;  // initialized to be NULL
hash_map<void*, int>p_BufferPop;
void inspect_commit_obj_write(){
    int thread_id = g_thread_index.get_my_thread_id();
    MemoryOpBuffer* p_buffer = p_buffers_commit[thread_id];
    if (p_buffer == NULL) return;
    *((int*)p_buffer->front().addr) = p_buffer->front().value;
    p_BufferPop[p_buffer->front().addr]=p_buffer->front().value;//6.25, only store one var at each addr
    p_buffer-> pop();  // p_buffer always at least has one MemoryOp
    p_buffers_commit[thread_id] = NULL;
}

//6.25 if the read addr is from buffer, restore addr
int inspect_check_real_addr(void* addr){    
    if(p_BufferPop.find(addr)!= p_BufferPop.end())
	return p_BufferPop[addr];
    else return -1000;
}

void inspect_obj_write_rinspect(void* obj_addr, int value, int inst_id){
	int obj_id, thread_id;
	Socket * socket = NULL;
	EventPermitType permit;
	obj_id = g_object_index.get_obj_id(obj_addr);

	if (obj_id == -1) {
		return;
		obj_id = g_object_index.add(obj_addr);
	}
	assert( obj_id > 0);

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert( socket != NULL);

	InspectEvent obj_event;
	obj_event.init_obj_write(thread_id, obj_id);
        obj_event.inst_id = inst_id;

	switch (g_memory_model){
	case SC_MODEL:
	    inspect_obj_write( obj_addr, inst_id);
	    break;
	case TSO_MODEL:
	{
	    g_tso_buffers[thread_id].push(MemoryOperation(obj_addr,value, inst_id, 0)); 
	    MemoryOperation& front_mo = g_tso_buffers[thread_id].front(); 
	    obj_id = g_object_index.get_obj_id(front_mo.addr);
	    obj_event.init_obj_write(thread_id, obj_id);
	    obj_event.inst_id = front_mo.inst_id;
         
	    bool bLoop=false;	
	    if(g_max_bound > 0){
	       if(g_tso_buffers[thread_id].size()>g_max_bound){ 
	           bLoop=true; 
		}  
	    }
          	 
	    (*socket) << obj_event;
	
	    (*socket) >> permit;

	    switch (permit){
	case OBJ_WRITE_PERM:

	    p_buffers_commit[thread_id] = &g_tso_buffers[thread_id];
	    bLoop=false;// for bounded buffer 
	    break;
	case OBJ_READ_PERM: 
	    break;
	default:
	    assert(0==1 && "unrecongnized permit");
	    break;
	}
               

	} 
	break;

	case PSO_MODEL:
	{
	    bool isAtomic=false;
	    g_pso_buffers[thread_id][obj_addr].push(MemoryOperation(obj_addr,value, inst_id, 0));//
	    if(g_max_bound > 0 && g_pso_buffers[thread_id][obj_addr].size()>g_max_bound){ 
		// for bounded, just send the write op to schedule, the priority is highest.  	  
		 MemoryOperation& front_mo=g_pso_buffers[thread_id][obj_addr].front();
		 obj_id = g_object_index.get_obj_id(front_mo.addr);
		 int per_oid=0; //make sure permit obj_id
	
		 send_write_vector(isAtomic);

		 (*socket) >> permit;
		 (*socket) >> per_oid;
		 if(per_oid!=obj_id) {
		     break;// don't send bounding again
		 }else{
		     assert(permit == OBJ_WRITE_PERM);
		     p_buffers_commit[thread_id] = &g_pso_buffers[thread_id][obj_addr];
		 }
	    }
	    else{	
		    int tmp_oid=0;	
		    int per_oid=0; //make sure permit obj_id	 
	
		    send_write_vector(isAtomic);
	    
		    (*socket) >> permit;
		    (*socket) >> per_oid;// used to make sure which addr should be permitted.

		    switch (permit){
		    case OBJ_WRITE_PERM:
			if(per_oid == 0) break;//future write
			void* tmp_addr; 

			for (hash_map<void*, MemoryOpBuffer>::iterator it=g_pso_buffers[thread_id].begin() ; it!=g_pso_buffers[thread_id].end(); ++it){
			    if (it->second.empty()) continue;
			    MemoryOperation* front_mo = &(it->second.front());
			    int tmp_oid = g_object_index.get_obj_id(front_mo->addr);
			    if(per_oid == tmp_oid)  {	
				tmp_addr= front_mo->addr;  
				p_buffers_commit[thread_id] = &g_pso_buffers[thread_id][tmp_addr];
				break;
			    }
			}
			break;
		    case OBJ_READ_PERM: 
#ifdef NLZ_DEBUG
			//cout<<"\n"<<thread_id<<": OBJ_READ_PERM received in inspect_write()"<<endl; 
#endif
			break;
		    default:
			assert(0==1 && "unrecongnized permit");
			break;
		    }
	    }
	}
	break;
        }
	
}

void inspect_obj_read_rinspect(void* obj_addr, int inst_id){

    int obj_read_id, thread_id;
    Socket * socket = NULL;
    EventPermitType permit;
    try {

	if (!g_object_index.is_member(obj_addr))
	    obj_read_id = g_object_index.add(obj_addr);

	assert( g_object_index.is_member(obj_addr));

	obj_read_id = g_object_index.get_obj_id(obj_addr);
	assert( obj_read_id > 0);

	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert( socket != NULL);

	InspectEvent obj_read_event;
	obj_read_event.init_obj_read(thread_id, obj_read_id);
	obj_read_event.inst_id = inst_id;

	if( TSO_MODEL == g_memory_model){
	     MemoryOpBuffer& buffer = g_tso_buffers[thread_id];
	     do{
		int obj_write_id;
		InspectEvent obj_write_event;
		if (!buffer.empty()){
		    obj_read_event.i_mult = 0;
		    
		    (*socket) << obj_read_event;
	      
		    MemoryOperation& front_mo = buffer.front();
		    obj_write_id = g_object_index.get_obj_id(front_mo.addr);
		    obj_write_event.init_obj_write(thread_id, obj_write_id);
		    obj_write_event.inst_id = front_mo.inst_id;
		    obj_write_event.i_mult = -1;
		    (*socket) << obj_write_event;	

		(*socket) >> permit;
		switch (permit){
	        case OBJ_WRITE_PERM:
		    *((int*)buffer.front().addr) = buffer.front().value;
		    buffer.pop();
		    break;
	        case OBJ_READ_PERM:
		    break;
	        default:
		    assert(0==1 && "unrecognized permit");
		}
	    }else{
		obj_read_event.i_mult = -1;
		(*socket) << obj_read_event;

		(*socket) >> permit;
		assert(OBJ_READ_PERM == permit);
		}
	     }while(permit == OBJ_WRITE_PERM);
             // TODO: read from memory buffer-- it is not right. obj_addr is changed
	     MemoryOpBuffer::reverse_iterator rit = buffer.find_from_back(obj_addr);
	     if ( rit != buffer.rend()){  // if in buffer, redirect to read from buffer
		 //cout<<"redirect to read from buffer  &&&&&&&"<<endl;  //
		 //obj_addr = &(rit->value);//there is a bug
		 *((int*)obj_addr)=rit->value;
	     }
	     
	} else if (PSO_MODEL == g_memory_model){
	    hash_map<void*,MemoryOpBuffer>& buffer = g_pso_buffers[thread_id];//
	    do{
		int obj_write_id = 0;
		int per_oid = 0; //make sure permit obj_id
		int tmp_oid=0;
		InspectEvent obj_write_event;
		bool isAtomic=false;
		
		if (buffer_has_value()){
		    obj_read_event.i_mult = 0;
		    (*socket) << obj_read_event;
		    send_write_vector(isAtomic); //send out write vector
			
		    (*socket) >> permit;
		    (*socket) >> per_oid;// used to make sure which addr should be permitted.
			
		    switch (permit){
		    case OBJ_WRITE_PERM:
			assert(per_oid != 0);// it means write is future event, read should be buffered.
			void* tmp_addr; 
			
			for (hash_map<void*, MemoryOpBuffer>::iterator it=g_pso_buffers[thread_id].begin() ; it!=g_pso_buffers[thread_id].end(); ++it){
			    if (it->second.empty()) continue;
			    MemoryOperation* front_mo = &(it->second.front());
			    int tmp_oid = g_object_index.get_obj_id(front_mo->addr);
			    if(per_oid == tmp_oid)  {	
				tmp_addr= front_mo->addr;   
				*(int*)g_pso_buffers[thread_id][tmp_addr].front().addr = g_pso_buffers[thread_id][tmp_addr].front().value;
				g_pso_buffers[thread_id][tmp_addr].pop();
				break;
			    }
			}
		
			break;
		    case OBJ_READ_PERM:
			//cout<<"\n"<<thread_id<<": OBJ_READ_PERM received1"<<endl; 
			break;
		    default:
			assert(0==1 && "unrecognized permit");
		    }
	        	    
		}else{
		    //cout<<thread_id<<" :Send OBJ_READ in read op \n";
		    obj_read_event.i_mult = -1;
		    (*socket) << obj_read_event;

		    (*socket) >> permit;
		    (*socket) >> per_oid;

		    assert(OBJ_READ_PERM == permit);
		}
	     }while( OBJ_WRITE_PERM == permit );
	    MemoryOpBuffer::reverse_iterator rit = buffer[obj_addr].find_from_back(obj_addr);
	    if ( rit != buffer[obj_addr].rend()){  // if in buffer, redirect to read from buffer
		*((int*)obj_addr) =rit->value;
	     }
	}
	else{
	    inspect_obj_read( obj_addr, inst_id);
	    //break;//3.13.2015
	}
    } catch (NullObjectException &e) {
	cerr << "Error: shared object is null....\n";
    }
}
#endif

#ifdef NLZ_ATOMIC
//atomic function.
void inspect_obj_membar_rinspect(void* obj_addr, int inst_id){
	int obj_id, thread_id;
	Socket * socket = NULL;
	int isFuture=-1;//used as the past event in buffer, should be flush when atomic
	
	obj_id = g_object_index.get_obj_id(obj_addr);

	if (obj_id == -1) {
	    return;
	}
	assert( obj_id > 0);
	thread_id = g_thread_index.get_my_thread_id();
	socket = g_socket_index.get_socket(thread_id);
	assert( socket != NULL);

	InspectEvent obj_event;
 
	obj_event.init_obj_write(thread_id, obj_id);
	obj_event.inst_id = inst_id;
	obj_event.future=isFuture;

	switch (g_memory_model){
	case TSO_MODEL:
	{
	    int num=(g_tso_buffers[thread_id].size());
	    MemoryOpBuffer& buffer = g_tso_buffers[thread_id];
	
	    while(num-- >0){
		MemoryOperation& front_mo = g_tso_buffers[thread_id].front();
		obj_id = g_object_index.get_obj_id(front_mo.addr);
		obj_event.init_obj_write(thread_id, obj_id);
		obj_event.inst_id = front_mo.inst_id;
		obj_event.future=isFuture;
		(*socket) << obj_event;
		EventPermitType permit;
		(*socket) >> permit;
		assert(permit == OBJ_WRITE_PERM);    
		*((int*)buffer.front().addr) = buffer.front().value; //push from buffer to memory
		buffer.pop();
	    }
	}
	break;
	case PSO_MODEL:
	{
	    EventPermitType permit;
	    int per_oid=0;
	    bool isAtomic=true;

	    while(buffer_has_value()){
		send_write_vector(isAtomic);
	 	(*socket) >> permit;
		(*socket) >> per_oid;
		assert(permit == OBJ_WRITE_PERM && "permit is NO OBJ_WRITE"); 
		assert(per_oid != 0 && "permit obj_id is not in buffer");// it means write is future event, read should be buffered.
	 	void* tmp_addr; 
		for (hash_map<void*, MemoryOpBuffer>::iterator it=g_pso_buffers[thread_id].begin() ; it!=g_pso_buffers[thread_id].end(); ++it){
		    if (it->second.empty()) continue;
		    MemoryOperation* front_mo = &(it->second.front());
		    int tmp_oid = g_object_index.get_obj_id(front_mo->addr);
		    if(per_oid == tmp_oid)  {	
			tmp_addr= front_mo->addr; 
			*(int*)g_pso_buffers[thread_id][tmp_addr].front().addr = g_pso_buffers[thread_id][tmp_addr].front().value;
			g_pso_buffers[thread_id][tmp_addr].pop();
			//break;
		    }
		}
	    }
	 	
	}
	break;
	default: 
	    break;
	}
/*---------------------------------------------------------------------------------------------------------------*/
	//at last, if the two value is the same, write new to addr, else do nothing, no need to push into buffer.
	obj_id = g_object_index.get_obj_id(obj_addr);  
	assert( obj_id > 0);

	obj_event.init_obj_write(thread_id, obj_id);
	obj_event.inst_id = inst_id;
	obj_event.future=isFuture;
	(*socket) << obj_event;

	EventPermitType permit;
	int per_oid=0;
	(*socket) >> permit;
	if(g_memory_model == PSO_MODEL) (*socket)>> per_oid;//take care input or output
	assert(permit == OBJ_WRITE_PERM);
}
#endif

#ifdef NLZ_PSO
bool buffer_has_value(){
    bool bNotEmpty =false;
    int thread_id = g_thread_index.get_my_thread_id();
    if(PSO_MODEL == g_memory_model ){
	for (hash_map<void*, MemoryOpBuffer>::iterator it=g_pso_buffers[thread_id].begin() ; it!=g_pso_buffers[thread_id].end(); ++it){
	    if (it->second.empty()) continue;
	    bNotEmpty=true;
	    return bNotEmpty;			
	}
	return bNotEmpty;
    }
    else return bNotEmpty;
}
void send_write_vector(bool IsAtomic){
    Socket * socket = NULL;
    int thread_id = g_thread_index.get_my_thread_id();
    socket = g_socket_index.get_socket(thread_id);
    assert( socket != NULL);

    vector< MemoryOperation* > vec_op_front;
    for (hash_map<void*, MemoryOpBuffer>::iterator it=g_pso_buffers[thread_id].begin() ; it!=g_pso_buffers[thread_id].end(); ++it){
	if (it->second.empty()) continue;
	vec_op_front.push_back(&(it->second.front()));// & is needed
    }
    InspectEvent obj_event;
    if(IsAtomic) obj_event.future=-1;
    for(int i=0;i<vec_op_front.size()-1;++i)
    {	  
	MemoryOperation* front_mo = vec_op_front[i];
      
	int obj_id = g_object_index.get_obj_id(front_mo->addr);
	obj_event.init_obj_write(thread_id, obj_id);
	obj_event.inst_id = front_mo->inst_id;
	obj_event.i_mult = i;  
	(*socket) << obj_event;
    }	
    MemoryOperation* front_mo = vec_op_front[i];
    int obj_id = g_object_index.get_obj_id(front_mo->addr);
    obj_event.init_obj_write(thread_id, obj_id);
    obj_event.inst_id = front_mo->inst_id;
    obj_event.i_mult = -1;    	   

    (*socket) << obj_event;
}
#endif


