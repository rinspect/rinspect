#include "clap_eraser.hh"
  

//printout for debug information
#define DBG_PRINT printf("thread %8x is calling %s, file %s, line %d\n", (unsigned)pthread_self(), __FUNCTION__, __FILE__, __LINE__)

//printout for each shared variable
#define PRINT //printf("map_shared_var[%d]: status: %d; C(v): %d; LH(%8x): %d; WLH(%8x): %d\n", tmp_var_index, map_shared_var[tmp_var_index].status, map_shared_var[tmp_var_index].locks_candidate, (unsigned)pthread_self(), map_thread[tmp_thread_index].locks_held, (unsigned)pthread_self(), map_thread[tmp_thread_index].write_locks_held);

//printout for all shared variables (provisional)
#define PRINT1 //printf("map_shared_var[0]: status: %d; C(v): %d; LH(%8x): %d; WLH(%8x): %d\nmap_shared_var[1]: status: %d; C(v): %d; LH(%8x): %d; WLH(%8x): %d\n", map_shared_var[0].status, map_shared_var[0].locks_candidate, (unsigned)pthread_self(), map_thread[tmp_thread].locks_held, (unsigned)pthread_self(), map_thread[tmp_thread].write_locks_held, map_shared_var[1].status, map_shared_var[1].locks_candidate, (unsigned)pthread_self(), map_thread[tmp_thread].locks_held, (unsigned)pthread_self(), map_thread[tmp_thread].write_locks_held);


//type definition for each lockset
typedef int LOCKS_CANDIDATE, LOCKS_HELD, WRITE_LOCKS_HELD;

//type definition for each status of each shared variable
typedef enum {VIRGIN, EXCLUSIVE, SHARED, SHARED_MODIFIED} STATUS;

//global flag whether data race is detected
bool data_race_detected = false;

//type definition for each shared variable struct
typedef struct {
  int *addr;    //memory location of each shared variable
  LOCKS_CANDIDATE locks_candidate;  // of each shared variable
  pthread_t thread_id;  //first thread that access each shared variable
  STATUS status;    //status of each shared variable
}DATA;

//type definition for each thread
typedef struct {
  pthread_t thread; //pthread_t object
  LOCKS_HELD locks_held;    //locks held by each thread
  WRITE_LOCKS_HELD write_locks_held;    //write locks held by each thread
}THREAD;

//maximum size for each array (obsolete in advanced c++ version, substituted by vector container
#define MAX 100

//array to store shared variable
//DATA shared_var_array[MAX];
map<int *, DATA> map_shared_var;

//index for the array of shared variables
int shared_var_index = 0;

//array to store locks (memory location of each pthread_mutex_t object)
void *mutex_array[MAX];
map<pthread_mutex_t *, int> map_mutex;

//index for the array of locks
int mutex_index = 0;

//array to store information of all the threads
//THREAD thread_array[MAX];
map<pthread_t, THREAD> map_thread;

//index of thread array
int thread_index = 0;

//lock for all newly added code  (Chao: not needed)
//pthread_mutex_t this_thread;


int eraser_mutex_find_or_add(pthread_mutex_t *mutex)
{
  int res = -1;
  //retrieve the mutex index
  res = map_mutex[mutex];
  /*
  for (int i=0; i<mutex_index; i++) {
    if (mutex_array[i] == mutex) {
      res = i;
      break;
    }
    }*/
  if (res == -1) {
    //insert if the mutex entry doesn't already exist
    map_mutex[mutex] = map_mutex.size(); 
    res = map_mutex[mutex];
    //    mutex_index++;
  }
  return res;
}

//int or pthread_t???
pthread_t eraser_thread_find_or_add(pthread_t thread) 
{
  unsigned res = 0xffffffff;
  // retrieve the thread index
  res = (unsigned)map_thread[thread].thread;
  /*  for (int i=0; i<thread_index; i++) {
    if (thread_array[i].thread == thread) {
      res = i;
      break;
    }
    }*/
  if (res == 0xffffffff) {
    //insert if the thread entry doesn't already exist
    DBG_PRINT;

    THREAD new_thread;

    new_thread.thread = pthread_self();
    new_thread.locks_held = 0;
    new_thread.write_locks_held = 0;

    map_thread[thread] = new_thread;
    /*
    thread_array[thread_index].thread = pthread_self();
    thread_array[thread_index].locks_held = 0;
    thread_array[thread_index].write_locks_held = 0;*/
    res = thread;   
    //    ++thread_index; 
  }
  return res;
}

int eraser_thread_find_or_add_self()
{
  return eraser_thread_find_or_add(pthread_self());
}

void eraser_obj_find_or_add(int *addr)  
{
  int res = -1;
  //retrieve the object index
  res = (unsigned)map_shared_var[addr].addr;
  /*  for (int i = 0; i<shared_var_index; ++i) {
    if (map_shared_var[i].addr == addr) {
      res = i;
      break;
    }
    }*/
  if (res == -1) {
    //insert if the object entry doesn't already exist
    DBG_PRINT;

    DATA new_shared_var;

    new_shared_var.addr = addr;
    new_shared_var.locks_candidate = 0;
    new_shared_var.thread_id = 0;
    new_shared_var.status = VIRGIN;

    map_shared_var[addr] = new_shared_var;
    /*
    map_shared_var[addr].addr = addr;
    map_shared_var[addr].locks_candidate = 0;
    map_shared_var[addr].thread_id = 0;
    map_shared_var[addr].status = VIRGIN;
    */
    //    res = shared_var_index;
    //    ++shared_var_index;
  }
}



//used in main function
bool eraser_race_detected()  
{
  DBG_PRINT;    //print out debug information
  /*
  if (data_race_detected == true)   //if data race is detected, print out message
    printf("data race detected!\n");
  else
  printf("no data race detected!\n");*/
  return data_race_detected;
}

/*
//used in main function
void _eraser_main_start() 
{
  DBG_PRINT;    //print out debug information
  data_race_detected = false;   //initialize the global flag
  
  //initialize all the indexes for each array
  shared_var_index = 0;

  mutex_index = 0;

  thread_index = 0;
}
*/
//----------------------------------------------------------------------------
// Start of the monitored events
//----------------------------------------------------------------------------

void _eraser_thread_start() 
{
  DBG_PRINT;
  pthread_t tid = eraser_thread_find_or_add_self();
  if (tid == 0) {
    // main thread start
  }
}

void _eraser_thread_end() 
{
  DBG_PRINT;    
  pthread_t tid = eraser_thread_find_or_add_self(); 
  if (tid == 0) {
    // main thread end
    if (data_race_detected == true) {
      printf("Eraser Summary: data race detected!\n");
    }
  }
}

void _eraser_thread_create(pthread_t *thread, const pthread_attr_t * attr, void*(*start_routine)(void*), void *arg) 
{
  DBG_PRINT;   
}

void _eraser_thread_join(pthread_t thread, void **value_ptr) 
{
  DBG_PRINT;
}

void _eraser_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
  DBG_PRINT; 
  //  mutex_array[mutex_index++] = mutex; 
}

void _eraser_mutex_destroy(pthread_mutex_t *mutex) 
{
  DBG_PRINT;
}

void _eraser_mutex_lock(pthread_mutex_t *mutex) 
{
  DBG_PRINT; 
  int tmp_mutex_index;
  pthread_t tmp_thread;
  tmp_mutex_index = eraser_mutex_find_or_add(mutex);   
  tmp_thread = eraser_thread_find_or_add_self(); 
  //  if (tmp_mutex != -1)  {
    map_thread[tmp_thread].locks_held |= 1<<tmp_mutex_index;    
    /* }
  else {
    //assert( 0 && "_eraser_mutex_lock: thread or mutex not found!" );
    printf("%s(%x): thread or mutex not found!", __FUNCTION__, (unsigned)mutex);
    }*/
  PRINT1 
}

void _eraser_mutex_trylock(pthread_mutex_t *mutex)
{
  DBG_PRINT;
}

void _eraser_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime)  
{
  DBG_PRINT;
}

void _eraser_mutex_unlock(pthread_mutex_t *mutex) 
{
  DBG_PRINT;
  int tmp_mutex_index;
  pthread_t tmp_thread;
  tmp_mutex_index = eraser_mutex_find_or_add(mutex);   
  tmp_thread = eraser_thread_find_or_add_self();
  //  if (tmp_mutex_index != -1 && tmp_thread_index != -1) {    
    map_thread[tmp_thread].locks_held &= ~(1<<tmp_mutex_index); 
    map_thread[tmp_thread].write_locks_held &= ~(1<<tmp_mutex_index);
    /*  }
  else {
    //assert( 0 && "_eraser_mutex_lock: thread or mutex not found!" );
    printf("%s(%x): thread or mutex not found!", __FUNCTION__, (unsigned)mutex);
    }*/
  PRINT1;
}

void _eraser_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr)
{
  ERASER_PRINT1(cond);
}

void _eraser_cond_destroy(pthread_cond_t *cond)
{
  ERASER_PRINT1(cond);
}

void _eraser_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex)
{
  ERASER_PRINT2(cond, mutex);
}

void _eraser_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime)
{
  ERASER_PRINT2(cond, mutex);
}

void _eraser_cond_broadcast(pthread_cond_t *cond)
{
  ERASER_PRINT1(cond);
}

void _eraser_cond_signal(pthread_cond_t *cond)
{ 
  ERASER_PRINT1(cond);
}

void _eraser_obj_read(int *addr) 
{
  DBG_PRINT;

  int tmp_thread;
  eraser_obj_find_or_add(addr);    
  tmp_thread = eraser_thread_find_or_add_self();
  //  if (tmp_thread_index != -1) {  
    // maintain each lockset based on 
    // the status of specified shared variable and thread
    switch (map_shared_var[addr].status) { 

    case VIRGIN:  
      //record the first thread accessed the shared variable 
      //if it has never been accessed
      map_shared_var[addr].thread_id = pthread_self();
    break;

    case EXCLUSIVE:
      if (map_thread[tmp_thread].locks_held != 0) {
        //refine the lock candidates of current accessed shared variable 
        //if current thread is holding some lock
        map_shared_var[addr].locks_candidate = map_thread[tmp_thread].locks_held;
      }
      if (map_shared_var[addr].thread_id != pthread_self()) {
        //update current shared variable's status if current thread is 
        //not the first thread that accessed this shared variable
        map_shared_var[addr].status = SHARED;
      }
      break;

    case SHARED:
      if (map_thread[tmp_thread].locks_held != 0) {
        //refine the lock candidates of current accessed shared variable
        //if current thread is holding some lock
        map_shared_var[addr].locks_candidate &= map_thread[tmp_thread].locks_held;
      }
      break;

    case SHARED_MODIFIED:
      if (map_thread[tmp_thread].locks_held != 0) {
        //refine the lock candidates of current accessed shared variable 
        //if current thread is holding some lock
        map_shared_var[addr].locks_candidate &= map_thread[tmp_thread].locks_held;
      }
      if(map_shared_var[addr].locks_candidate == 0) {
        //update the global flag if data race is detected
        data_race_detected = true;
        printf("data race detected!\n");
      }
      break;

    default:
      break;
    }
    PRINT;
    //  }
}

void _eraser_obj_write(int *addr) 
{
  DBG_PRINT; 

  int tmp_thread;

  tmp_thread = eraser_thread_find_or_add_self(); 
  if (tmp_thread != -1) {
    //update write locks held by current thread
    map_thread[tmp_thread].write_locks_held = map_thread[tmp_thread].locks_held;
  }

  eraser_obj_find_or_add(addr);    
  //  if (tmp_thread_index != -1) {  
    //maintain each lockset based on the status of 
    //specified shared variable and thread
    switch (map_shared_var[addr].status) { 

    case VIRGIN:
      //update current shared variable's status if it has never been accessed
      map_shared_var[addr].status = EXCLUSIVE; 
      //record the first thread accessed the shared variable
      //if it has never been accessed
      map_shared_var[addr].thread_id = pthread_self(); 
      if (map_shared_var[addr].locks_candidate == 0 && map_thread[tmp_thread].locks_held != 0) {
        //refine the lock candidates of current accessed shared variable 
        //if current thread is holding some lock and current shared variable 
        //is not consistently protected by any lock candidate
        map_shared_var[addr].locks_candidate = map_thread[tmp_thread].locks_held;
      }
      break;

    case EXCLUSIVE:
      //refine the lock candidates of current accessed shared variable
      //if current thread is holding some lock and current shared variable 
      //is not consistently protected by any lock candidate
      if (map_shared_var[addr].thread_id != pthread_self()) {
        //update current shared variable's status if current thread is not the
        //first thread that accessed this shared variable
        map_shared_var[addr].status = SHARED_MODIFIED;
      }
      if (map_thread[tmp_thread].write_locks_held != 0) {
        //refine the lock candidates of current accessed shared variable if
        //current thread is holding some write lock
        map_shared_var[addr].locks_candidate &= map_thread[tmp_thread].write_locks_held;
      }
      if (map_shared_var[addr].locks_candidate == 0) {
        //update the global flag if data race is detected
        data_race_detected = true;
        printf("data race detected!\n");
      }
      break;

    case SHARED:
      //update current shared variable's status
      map_shared_var[addr].status = SHARED_MODIFIED;   

    case SHARED_MODIFIED:
      PRINT;
      if (map_thread[tmp_thread].write_locks_held != 0) {
        //refine the lock candidates of current accessed shared variable if
        //current thread is holding some write lock
        map_shared_var[addr].locks_candidate &= map_thread[tmp_thread].write_locks_held;
      }
      if (map_shared_var[addr].locks_candidate == 0) {
        //update the global flag if data race is detected
        data_race_detected = true;
        printf("data race detected!\n");
      }
      break;

    default:
      break;
    }
    PRINT;
    //  }
}

void _eraser_call_begin(char* fname, char* ptr)
{
  ERASER_PRINT1(fname);  
}

void _eraser_call_end(char* fname, char* ptr)
{
  ERASER_PRINT1(fname);  
}

void _eraser_inst_begin(int inst, int stat)
{
  ERASER_PRINT2(inst, stat);
}

void _eraser_inst_end(int inst, int stat, int retval)
{
  ERASER_PRINT2(inst, stat);
}

