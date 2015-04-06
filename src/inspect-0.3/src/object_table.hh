#ifndef __INSPECTOR_OBJECT_H__
#define __INSPECTOR_OBJECT_H__

#include "naling.def"
#include <map>
#include <ext/hash_map>
#include <pthread.h>
#include "inspect_util.hh"
#include "program_state.hh"

using std::map;
using __gnu_cxx::hash_map;
using __gnu_cxx::hash;


namespace __gnu_cxx
{
  template<>
  struct hash<void*>
  {
    size_t operator()(const void * ptr) const {
      return (size_t)ptr;
    }
  };
};


using namespace __gnu_cxx;

struct eqvoidptr
{
  bool operator()(const void* p1, const void* p2) const
  {
    return (p1 == p2);
  }
};


enum ObjectType
{
  INT_OBJ    = 0,
  FLOAT_OBJ  = 1,
  CHAR_OBJ   = 2, 
  BINARY_OBJ = 3, 
  UNKNOWN_OBJ= 99
};


struct ObjectInfo
{
public:
  ObjectInfo();
  ObjectInfo(ObjectType t, void * address, int ident, bool ctrl);
  
  int obj_size(); 

public:
  void * addr;
  int id;
  ObjectType  type;  
  bool control_flag;  // whether this object affects the interaction
                      // of threads
};

typedef ObjectInfo MutexInfo;  //chao, 1/8/2013
typedef ObjectInfo CondInfo;   //chao, 1/8/2013



/**
 *   This table contains the mapping between object address
 *   and their id
 */
class ObjectIndex
{
public:
  typedef hash_map<void*, ObjectInfo*, hash<void*>, eqvoidptr >::iterator iterator;

public:
  ObjectIndex();
  ~ObjectIndex();

  int get_obj_id(void * objptr);
  //int add(void *objptr);
  int add(void *objptr, bool cflag=false);
  int add(void* objptr, ObjectType ot, bool ctrl=false);
  void remove(void* objptr);  
  void clear();
  bool is_member(void * obj_addr);
  
public:
  bool valid_flag;
  int next_obj_id;
  hash_map<void*, ObjectInfo*, hash<void*>, eqvoidptr> object_map;
  pthread_mutex_t  table_mutex;
};


class MutexIndex
{
public:
  typedef hash_map<void*, MutexInfo*, hash<void*>, eqvoidptr >::iterator iterator;

public:
  MutexIndex();
  ~MutexIndex();

  int get_mutex_id(void * objptr);
  int add(void *objptr, bool cflag=false);
  //int add(void* objptr, ObjectType ot, bool ctrl=false);
  void remove(void* objptr);  
  void clear();
  bool is_member(void * obj_addr);
  
public:
  bool valid_flag;
  int next_mutex_id;
  hash_map<void*, MutexInfo*, hash<void*>, eqvoidptr> mutex_map;
  pthread_mutex_t  table_mutex;
};

class CondIndex
{
public:
  typedef hash_map<void*, CondInfo*, hash<void*>, eqvoidptr >::iterator iterator;

public:
  CondIndex();
  ~CondIndex();

  int get_cond_id(void * objptr);
  int add(void *objptr, bool cflag=false);
  //int add(void* objptr, ObjectType ot, bool ctrl=false);
  void remove(void* objptr);  
  void clear();
  bool is_member(void * obj_addr);
  
public:
  bool valid_flag;
  int next_cond_id;
  hash_map<void*, CondInfo*, hash<void*>, eqvoidptr> cond_map;
  pthread_mutex_t  table_mutex;
};

class ThreadIndex
{
public:
  typedef map<pthread_t, int>::iterator iterator;
public: 
  ThreadIndex();
  ~ThreadIndex();  
  bool is_member( pthread_t );
  int get_thread_id( pthread_t );
  int get_my_thread_id();
  int insert(pthread_t thread);
  void insert(pthread_t thread, int tid);
  
  void remove_by_thread_id(int tid);
  void self_remove();

public:
  bool valid_flag;
  int next_tid;
  int max_tid;    // the maximum number of threads in
                  // the program under test
  map<pthread_t, int> tid_index;
  pthread_mutex_t table_mutex;
};


class SocketIndex
{
public:
  typedef hash_map<int, Socket*>::iterator iterator;
public:
  SocketIndex();
  SocketIndex(const char * config_file);
  ~SocketIndex();
  
  bool read_config_file(const char * filename);
  Socket * get_socket( int tid );
  Socket * self_register();
  Socket * register_by_tid(int tid);
  Socket * get_my_socket();

  void remove(int tid);
  void clear();

public:  
  bool valid_flag;
  hash_map<int, Socket*> sockets;
  pthread_mutex_t table_mutex;

  string socket_file;
};




extern ObjectIndex  g_object_index;
extern ThreadIndex  g_thread_index;
extern SocketIndex  g_socket_index;

extern MutexIndex   g_mutex_index;  //chao: added on 1/8/2013
extern CondIndex    g_cond_index;   //chao: added on 1/8/2013

#ifdef NLZ_FLAG
#include <deque>
#include <ctime>    // for time_type
#include <string>
#include <sstream>  // for toString
#include <ext/hash_map>  // for g_tso_buffers

using __gnu_cxx::hash_map;

struct MemoryOperation{
    typedef unsigned long time_type;
    void* addr;
    int value;
    int inst_id;
    time_type commit_time;
    MemoryOperation(void* addr_in, int value_in, int inst_id_in, time_type commit_time_in):addr(addr_in), value(value_in), inst_id(inst_id_in), commit_time(commit_time_in) {};

    string toString() const{
	std::stringstream ss;
	ss<<"{ "<<addr<<", val= "<<value<<", inst_id= "<<inst_id<<", tc= "<<commit_time<<" }";
	return ss.str();
    }
};

extern unsigned long g_op_count;

class MemoryOpBuffer{
public:
    MemoryOperation& front() { assert(!buffer.empty() && "buffer is empty, there is no front element"); return buffer.front(); };
    MemoryOperation& back() {  assert(!buffer.empty() && "buffer is empty, there is no back element"); return buffer.back(); };
    void push(const MemoryOperation& op) { buffer.push_back(op); };
    void pop() { assert(!buffer.empty() && "buffer is empty, cannot pop element"); buffer.pop_front(); };
    bool empty() const { return buffer.empty(); };
    std::deque<MemoryOperation>::size_type size() const { return buffer.size(); }
    
    typedef std::deque<MemoryOperation>::reverse_iterator reverse_iterator;
    reverse_iterator find_from_back(void* addr);
    reverse_iterator rend() { return buffer.rend(); }

    string toString() const;
    
private:
    std::deque<MemoryOperation> buffer;
};

extern hash_map<int, MemoryOpBuffer>  g_tso_buffers;
extern hash_map<int, hash_map<void*, MemoryOpBuffer> > g_pso_buffers;

#endif  // endif NLZ_FLAG


#endif  // file end if



