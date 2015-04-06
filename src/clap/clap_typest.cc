#include "clap_typest.hh"
#include "clap_typest_trace.hh"
#include "string.h"

static TypestTrace etrace;
bool whether_print = false;





//extern map<string, map<string, bool> > valid_functions;

void _typest_thread_start() {
	//TYPEST_PRINT();
	etrace.add_event(THREAD_START, 0);
}

void _typest_thread_end() {
	//TYPEST_PRINT();
	etrace.add_event(THREAD_END, 0);
}

void _typest_thread_create(pthread_t * thread, const pthread_attr_t * attr,
		void *(*start_routine)(void*), void * arg) {
	//TYPEST_PRINTt(*thread);
	etrace.add_event(THREAD_CREATE, UTID(*thread));
}

void _typest_thread_join(pthread_t thread, void **value_ptr) {
	//TYPEST_PRINTt(thread);
	etrace.add_event(THREAD_JOIN, UTID(thread));
}

void _typest_mutex_init(pthread_mutex_t * mutex,
		const pthread_mutexattr_t * attr) {
	//TYPEST_PRINT1(mutex);
	etrace.add_event(MUTEX_INIT, UOID(mutex));
}

void _typest_mutex_destroy(pthread_mutex_t *mutex) {
	//TYPEST_PRINT1(mutex);
	etrace.add_event(MUTEX_DESTROY, UOID(mutex));
}

void _typest_mutex_lock(pthread_mutex_t *mutex) {
	//TYPEST_PRINT1(mutex);
	etrace.add_event(MUTEX_LOCK, UOID(mutex));
}

void _typest_mutex_trylock(pthread_mutex_t *mutex) {
	//TYPEST_PRINT1(mutex);
	assert(0 && " not implemented");
}

void _typest_mutex_timedlock(pthread_mutex_t *mutex,
		const struct timespec *abstime) {
	//TYPEST_PRINT1(mutex);
	assert(0 && " not implemented");
}

void _typest_mutex_unlock(pthread_mutex_t *mutex) {
	//TYPEST_PRINT1(mutex);
	etrace.add_event(MUTEX_UNLOCK, UOID(mutex));
}

void _typest_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr) {
	//TYPEST_PRINT1(cond);
	etrace.add_event(COND_INIT, UOID(cond));
}

void _typest_cond_destroy(pthread_cond_t *cond) {
	//TYPEST_PRINT1(cond);
	etrace.add_event(COND_DESTROY, UOID(cond));
}

void _typest_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex) {
	//TYPEST_PRINT2(cond, mutex);
	etrace.add_event(COND_WAIT, UOID(cond));
}

void _typest_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex,
		const struct timespec * abstime) {
	//TYPEST_PRINT2(cond, mutex);
	assert(0 && " not implemented");
}

void _typest_cond_broadcast(pthread_cond_t *cond) {
	//TYPEST_PRINT1(cond);
//  assert(0 && " not implemented");
	etrace.add_event(COND_BROADCAST, UOID(cond));
}

void _typest_cond_signal(pthread_cond_t *cond) {
	//TYPEST_PRINT1(cond);
	etrace.add_event(COND_SIGNAL, UOID(cond));
}

void _typest_obj_read(int* addr) {
	//TYPEST_PRINT1(addr);
	assert(0 && " not implemented");
}

void _typest_obj_write(int* addr) {
	//TYPEST_PRINT1(addr);
	assert(0 && " not implemented");
}


//map<string, map<string, bool> >::iterator it;

//#define ATOMIC_CALL 0
//
//
//#if ATOMIC_CALL
//pthread_mutex_t call_lock = PTHREAD_MUTEX_INITIALIZER;
//int locked=0;
////class event_info{
////	char* fname;
////	char* ptr;
////public:
////	event_info(char* f, char* p){
////	fname=f;
////	ptr=p;
////	}
////
////	bool operator==(event_info* a){
////		if(strcmp(a->fname,this->fname)==0 && strcmp(a->ptr,this->ptr)==0) return true;
////		else return false;
////	}
////};
//
//
//
////static map<int, event_info*> last_call_begin;
//
//
//#endif


void _typest_call_begin(char* fname, char* ptr) {
//	cout<<"Call Begin>>>>>>>>>>>>>>>>>>>>>> ";
//		TYPEST_PRINTs(fname, ptr);
//		cout<<endl;
//lu:need to do: 1.atomic when function call are valid 2. avoid nested calls
//#if ATOMIC_CALL
////	event_info *ei=new event_info(fname,ptr);
//
//
//	etrace.add_event(OBJ_CALL, UOID(ptr), fname);
//
//	locked++;
//
//	cout<<"---------->>Lock: "<<locked;TYPEST_PRINTs(fname, ptr);
////	pthread_mutex_lock(&call_lock);
//
//#endif

//#if !ATOMIC_CALL //handle normally

	etrace.add_event(OBJ_CALL, UOID(ptr), fname);


//#endif
}

void _typest_call_end(char* fname, char* ptr) {
////	cout<<"Call End<<<<<<<<<<<<<<<<<<<<<<<< ";
////	TYPEST_PRINTs(fname, ptr);
////	cout<<endl;
//
//#if ATOMIC_CALL
//
////	pthread_mutex_unlock(&call_lock);
//	locked--;
//	cout<<"----------<<unLock: "<<locked;TYPEST_PRINTs(fname, ptr);
//
//#endif
//
//#if !ATOMIC_CALL//do nothing
//
//
//
//
//#endif


}

void _typest_inst_begin(int inst, int stat) {
	//TYPEST_PRINTi(inst, stat);
	assert(0 && " not implemented");
}

void _typest_inst_end(int inst, int stat, int retval) {
	//TYPEST_PRINTi(inst, stat);
	assert(0 && " not implemented");
}
