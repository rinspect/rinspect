#include "naling.def"
#include <pthread.h> 
#include <map>
#include <cassert>
#include <iostream>
#include <fstream>
#include "object_table.hh"
#include "inspect_exception.hh"
#include <algorithm>

using namespace std;
using namespace __gnu_cxx;

/**
 *   global declarations
 * 
 *   IdIndex::get_object_id(void*);
 *   IdIndex::get_thread_id();
 *   IdIndex::get_socket();
 */

ObjectIndex g_object_index;
ThreadIndex g_thread_index;
SocketIndex g_socket_index;

MutexIndex  g_mutex_index;  //chao: 1/8/2013
CondIndex   g_cond_index;   //chao: 1/8/2013

#ifdef NLZ_FLAG

unsigned long g_op_count = 0;

hash_map<int, MemoryOpBuffer>  g_tso_buffers;
hash_map<int, hash_map<void*, MemoryOpBuffer> > g_pso_buffers;

#include <string>
#include <sstream>
string tso_buffers_toString(){
    std::stringstream ss;
    for (hash_map<int, MemoryOpBuffer>::iterator it=g_tso_buffers.begin(); it!=g_tso_buffers.end(); ++it){
	ss<<"thread "<< it->first <<":\n";
	ss<< it->second.toString();
    }
    return ss.str();
}




#endif

extern char serverName[];
extern int serverPort;



ObjectInfo::ObjectInfo()
  : addr(NULL),
    id(-1),
    type(UNKNOWN_OBJ),
    control_flag(false)
{ }


ObjectInfo::ObjectInfo(ObjectType t, void * address, int ident, bool ctrl = false)
  : addr(address), 
    id(ident), 
    type(t), 
    control_flag(ctrl)
{ }



int ObjectInfo::obj_size()
{
  int sz = -1;

  switch(type){
  case INT_OBJ:   sz = sizeof(int); break;
  case FLOAT_OBJ: sz = sizeof(float); break;
  case CHAR_OBJ:  sz = sizeof(char);  break;
    
  default:  assert(false);
  }

  return sz;
}



////////////////////////////////////////////////////////////////////////////
//
//  The implementation of ObjectIndex
// 
///////////////////////////////////////////////////////////////////////////


ObjectIndex::ObjectIndex()
  : next_obj_id(1)
{
  int retval;

  object_map.clear();  
  retval = ::pthread_mutex_init(&table_mutex, NULL);
  assert( retval == 0);
  valid_flag = true;
}


ObjectIndex::~ObjectIndex()
{
  iterator it;
  ObjectInfo * obj_info;

  for (it = object_map.begin(); it != object_map.end(); it++){
    obj_info = it->second;
    delete obj_info;	
  }
  object_map.clear();

  valid_flag = false;
  ::pthread_mutex_destroy(&table_mutex);
}


/**
 *  given a pointer, give out the correspondent object id
 */
int ObjectIndex::get_obj_id(void* objptr)
{
  ObjectInfo * obj;
  iterator it;

  pthread_mutex_lock(&table_mutex);
  it = object_map.find(objptr);
  
  obj = (it == object_map.end())? NULL : it->second;
  pthread_mutex_unlock(&table_mutex);
  
  if (obj == NULL) {
    cout <<"err:"<<__FUNCTION__<<"("<<hex<< ((long)objptr) <<dec<< ") = -1\n";
    return -1; 
  }
  return obj->id;
}


// int ObjectIndex::add(void* obj_ptr)
// {
//   iterator it;
//   ObjectInfo * obj_info;

//   if (obj_ptr == NULL){
//     cerr<<"going to read/write a null pointer !\n";
//     throw  NullObjectException();
//     //assert( obj_ptr !=NULL );
//   }

//   pthread_mutex_lock(&table_mutex);

//   it = object_map.find( obj_ptr );
//   assert( it == object_map.find( obj_ptr ) );
  
//   obj_info = new ObjectInfo();
//   obj_info->id = next_obj_id;
//   next_obj_id++;
//   object_map.insert( make_pair(obj_ptr, obj_info) );

//   assert( object_map.find(obj_ptr) != object_map.end() );
  
//   pthread_mutex_unlock(&table_mutex);
  
//   return obj_info->id;
// }




int ObjectIndex::add(void * obj_ptr,bool cflag)
{
  iterator it;
  ObjectInfo * obj_info;

  if (obj_ptr == NULL){
    cerr<<"going to read/write a null pointer !\n";
    throw  NullObjectException();
    //assert( obj_ptr !=NULL );
  }

  pthread_mutex_lock(&table_mutex);

  it = object_map.find( obj_ptr );

  assert( it == object_map.end());
  
  obj_info = new ObjectInfo();
  obj_info->addr = obj_ptr;
  obj_info->id = next_obj_id;
  obj_info->control_flag = cflag;

  next_obj_id++;
  object_map.insert( make_pair(obj_ptr, obj_info) );

  assert( object_map.find(obj_ptr) != object_map.end() );
  
  pthread_mutex_unlock(&table_mutex);
  
  return obj_info->id;
}



int ObjectIndex::add(void * obj_ptr, ObjectType type, bool cflag)
{
  iterator it;
  ObjectInfo * obj_info;

  if (obj_ptr == NULL){
    cerr<<"going to read/write a null pointer !\n";
    throw  NullObjectException();
    //assert( obj_ptr !=NULL );
  }

  pthread_mutex_lock(&table_mutex);

  it = object_map.find( obj_ptr );
  assert( it == object_map.end());
  
  obj_info = new ObjectInfo();
  obj_info->addr = obj_ptr;
  obj_info->id = next_obj_id;
  obj_info->control_flag = cflag;
  obj_info->type = type;

  next_obj_id++;
  object_map.insert( make_pair(obj_ptr, obj_info) );

  assert( object_map.find(obj_ptr) != object_map.end() );
  
  pthread_mutex_unlock(&table_mutex);
  
  return obj_info->id;
}


void ObjectIndex::remove(void * obj_ptr)
{
  iterator it;
 
  pthread_mutex_lock( &table_mutex );
  it = object_map.find( obj_ptr );
  assert( it != object_map.end() );
  delete it->second;
  object_map.erase( it );
  pthread_mutex_unlock( &table_mutex );
}


bool ObjectIndex::is_member(void * obj_addr)
{
  iterator it;
  bool result;

  pthread_mutex_lock(&table_mutex);
  it = object_map.find( obj_addr );
  result = it != object_map.end();
  pthread_mutex_unlock(&table_mutex);
  return  result;
}



struct AscendingSortById
{
  bool operator()(ObjectInfo * obj1, ObjectInfo * obj2){
    return obj1->id < obj2->id;
  }
};


////////////////////////////////////////////////////////////////////////////
//
//  The implementation of MutexIndex
// 
///////////////////////////////////////////////////////////////////////////


MutexIndex::MutexIndex()
  : next_mutex_id(1)
{
  int retval;

  mutex_map.clear();  
  retval = ::pthread_mutex_init(&table_mutex, NULL);
  assert( retval == 0);
  valid_flag = true;
}


MutexIndex::~MutexIndex()
{
  iterator it;
  MutexInfo * obj_info;

  for (it = mutex_map.begin(); it != mutex_map.end(); it++){
    obj_info = it->second;
    delete obj_info;	
  }
  mutex_map.clear();

  valid_flag = false;
  ::pthread_mutex_destroy(&table_mutex);
}


/**
 *  given a pointer, give out the correspondent mutex id
 */
int MutexIndex::get_mutex_id(void* objptr)
{
  MutexInfo * obj;
  iterator it;

  pthread_mutex_lock(&table_mutex);
  it = mutex_map.find(objptr);
  
  obj = (it == mutex_map.end())? NULL : it->second;
  pthread_mutex_unlock(&table_mutex);
  
  if (obj == NULL) {
    cout <<"err:"<<__FUNCTION__<<"("<<hex<< ((long)objptr) <<dec<< ") = -1\n";
    return -1; 
  }
  return obj->id;
}

int MutexIndex::add(void * obj_ptr,bool cflag)
{
  iterator it;
  MutexInfo * obj_info;

  if (obj_ptr == NULL){
    cerr<<"going to read/write a null pointer !\n";
    throw  NullMutexException();
    //assert( obj_ptr !=NULL );
  }

  pthread_mutex_lock(&table_mutex);

  it = mutex_map.find( obj_ptr );

  assert( it == mutex_map.end());
  
  obj_info = new MutexInfo();
  obj_info->addr = obj_ptr;
  obj_info->id = next_mutex_id;
  obj_info->control_flag = cflag;

  next_mutex_id++;
  mutex_map.insert( make_pair(obj_ptr, obj_info) );

  assert( mutex_map.find(obj_ptr) != mutex_map.end() );
  
  pthread_mutex_unlock(&table_mutex);
  
  return obj_info->id;
}


/*
int MutexIndex::add(void * obj_ptr, MutexType type, bool cflag)
{
  iterator it;
  MutexInfo * obj_info;

  if (obj_ptr == NULL){
    cerr<<"going to read/write a null pointer !\n";
    throw  NullMutexException();
    //assert( obj_ptr !=NULL );
  }

  pthread_mutex_lock(&table_mutex);

  it = mutex_map.find( obj_ptr );
  assert( it == mutex_map.end());
  
  obj_info = new MutexInfo();
  obj_info->addr = obj_ptr;
  obj_info->id = next_mutex_id;
  obj_info->control_flag = cflag;
  obj_info->type = type;

  next_mutex_id++;
  mutex_map.insert( make_pair(obj_ptr, obj_info) );

  assert( mutex_map.find(obj_ptr) != mutex_map.end() );
  
  pthread_mutex_unlock(&table_mutex);
  
  return obj_info->id;
}
*/

void MutexIndex::remove(void * obj_ptr)
{
  iterator it;
 
  pthread_mutex_lock( &table_mutex );
  it = mutex_map.find( obj_ptr );
  assert( it != mutex_map.end() );
  delete it->second;
  mutex_map.erase( it );
  pthread_mutex_unlock( &table_mutex );
}


bool MutexIndex::is_member(void * obj_addr)
{
  iterator it;
  bool result;

  pthread_mutex_lock(&table_mutex);
  it = mutex_map.find( obj_addr );
  result = it != mutex_map.end();
  pthread_mutex_unlock(&table_mutex);
  return  result;
}



////////////////////////////////////////////////////////////////////////////
//
//  The implementation of CondIndex
// 
///////////////////////////////////////////////////////////////////////////


CondIndex::CondIndex()
  : next_cond_id(1)
{
  int retval;

  cond_map.clear();  
  retval = ::pthread_mutex_init(&table_mutex, NULL);
  assert( retval == 0);
  valid_flag = true;
}


CondIndex::~CondIndex()
{
  iterator it;
  CondInfo * obj_info;

  for (it = cond_map.begin(); it != cond_map.end(); it++){
    obj_info = it->second;
    delete obj_info;	
  }
  cond_map.clear();

  valid_flag = false;
  ::pthread_mutex_destroy(&table_mutex);
}


/**
 *  given a pointer, give out the correspondent cond id
 */
int CondIndex::get_cond_id(void* objptr)
{
  CondInfo * obj;
  iterator it;

  pthread_mutex_lock(&table_mutex);
  it = cond_map.find(objptr);
  
  obj = (it == cond_map.end())? NULL : it->second;
  pthread_mutex_unlock(&table_mutex);
  
  if (obj == NULL) {
    cout <<"err:"<<__FUNCTION__<<"("<<hex<< ((long)objptr) <<dec<< ") = -1\n";
    return -1; 
  }
  return obj->id;
}


int CondIndex::add(void * obj_ptr,bool cflag)
{
  iterator it;
  CondInfo * obj_info;

  if (obj_ptr == NULL){
    cerr<<"going to read/write a null pointer !\n";
    throw  NullCondException();
    //assert( obj_ptr !=NULL );
  }

  pthread_mutex_lock(&table_mutex);

  it = cond_map.find( obj_ptr );

  assert( it == cond_map.end());
  
  obj_info = new CondInfo();
  obj_info->addr = obj_ptr;
  obj_info->id = next_cond_id;
  obj_info->control_flag = cflag;

  next_cond_id++;
  cond_map.insert( make_pair(obj_ptr, obj_info) );

  assert( cond_map.find(obj_ptr) != cond_map.end() );
  
  pthread_mutex_unlock(&table_mutex);
  
  return obj_info->id;
}


/*
int CondIndex::add(void * obj_ptr, ObjectType type, bool cflag)
{
  iterator it;
  CondInfo * obj_info;

  if (obj_ptr == NULL){
    cerr<<"going to read/write a null pointer !\n";
    throw  NullCondException();
    //assert( obj_ptr !=NULL );
  }

  pthread_mutex_lock(&table_mutex);

  it = cond_map.find( obj_ptr );
  assert( it == cond_map.end());
  
  obj_info = new CondInfo();
  obj_info->addr = obj_ptr;
  obj_info->id = next_cond_id;
  obj_info->control_flag = cflag;
  obj_info->type = type;

  next_cond_id++;
  cond_map.insert( make_pair(obj_ptr, obj_info) );

  assert( cond_map.find(obj_ptr) != cond_map.end() );
  
  pthread_mutex_unlock(&table_mutex);
  
  return obj_info->id;
}
*/

void CondIndex::remove(void * obj_ptr)
{
  iterator it;
 
  pthread_mutex_lock( &table_mutex );
  it = cond_map.find( obj_ptr );
  assert( it != cond_map.end() );
  delete it->second;
  cond_map.erase( it );
  pthread_mutex_unlock( &table_mutex );
}


bool CondIndex::is_member(void * obj_addr)
{
  iterator it;
  bool result;

  pthread_mutex_lock(&table_mutex);
  it = cond_map.find( obj_addr );
  result = it != cond_map.end();
  pthread_mutex_unlock(&table_mutex);
  return  result;
}




///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

ThreadIndex::ThreadIndex()
  : valid_flag(false),
    next_tid(0),
    max_tid(9999)
{ 
  tid_index.clear();
  ::pthread_mutex_init( &table_mutex, NULL );
  valid_flag = true;
}

ThreadIndex::~ThreadIndex()
{ 
  valid_flag = false;
  ::pthread_mutex_destroy( &table_mutex );
  tid_index.clear();
}


bool ThreadIndex::is_member( pthread_t thread )
{
  iterator it;
  bool flag;

  pthread_mutex_lock( &table_mutex );
  it = tid_index.find( thread );
  flag = it != tid_index.end() ;
  pthread_mutex_unlock( &table_mutex );

  return flag;
}


int ThreadIndex::get_thread_id( pthread_t thread )
{
  iterator it;
  int thread_id;
  
  pthread_mutex_lock( &table_mutex );
  it = tid_index.find( thread );
  assert( it != tid_index.end() );  
  thread_id = it->second;
  pthread_mutex_unlock( &table_mutex );

  return thread_id;
}


int ThreadIndex::insert(pthread_t thread)
{
  iterator it;
  int thread_id;
  
  pthread_mutex_lock(&table_mutex);
  it = tid_index.find( thread );
  if ( it != tid_index.end() ){
    pthread_mutex_unlock(&table_mutex);
    return it->second;
  }

  thread_id = next_tid; 
  next_tid++;

  tid_index.insert( make_pair(thread, thread_id) );
  pthread_mutex_unlock(&table_mutex);
  
  return thread_id;
}


void ThreadIndex::insert(pthread_t thread, int tid)
{ 
  iterator it;

  assert(! is_member(thread) );
  assert(tid >= max_tid);
  
  pthread_mutex_lock(&table_mutex);
  it = tid_index.find(thread);
  assert(it == tid_index.end());

  tid_index.insert(make_pair(thread, tid));
  pthread_mutex_unlock(&table_mutex);
}


void ThreadIndex::remove_by_thread_id(int tid)
{
  iterator it;
  
  pthread_mutex_lock(&table_mutex);
  for (it = tid_index.begin(); it != tid_index.end(); it++){
    if ( it->second == tid ) break;
  }
  if ( it != tid_index.end() ) tid_index.erase(it);
  pthread_mutex_unlock(&table_mutex);
}


int ThreadIndex::get_my_thread_id()
{
  pthread_t  myself;
  iterator it;
  int thread_id;

  myself = pthread_self();

  pthread_mutex_lock( &table_mutex );
  it = tid_index.find( myself );

  if (it == tid_index.end()){
    cout << hex << myself << endl;
    assert( it != tid_index.end() );  
  }

  thread_id = it->second;
  pthread_mutex_unlock( &table_mutex );
  return thread_id;
}


void ThreadIndex::self_remove()
{
  assert(false);
}

///////////////////////////////////////////////////////////////////////////////
//
//  the implementation of SocketIndex
//
///////////////////////////////////////////////////////////////////////////////

SocketIndex::SocketIndex()
{
  sockets.clear();
  pthread_mutex_init(&table_mutex, NULL);

  char * env_str;
  env_str = getenv("INSPECT_SOCKET_FILE");

  if (env_str != NULL) 
    socket_file = env_str;
  else    
    socket_file = string("/tmp/_") + getenv("USER") + "_inspect_socket" ;
}


SocketIndex::SocketIndex(const char * config_file)
{
  assert( config_file != NULL );

  sockets.clear();
  pthread_mutex_init(&table_mutex, NULL);
  
  char * env_str;
  env_str = getenv("INSPECT_SOCKET_FILE");
  
  socket_file = (env_str == NULL)? "/tmp/inspect_socket" : env_str;
}


SocketIndex::~SocketIndex()
{
  iterator it;
  Socket * socket;

  pthread_mutex_destroy(&table_mutex);  
  for (it = sockets.begin(); it != sockets.end(); it++){
    socket = it->second;
    socket->close();
    delete socket;
  }
  sockets.clear();
}


// bool SocketIndex::read_config_file(const char * file_name)
// {
//   ifstream is(file_name);
//   char buf[1024], name[64], name2[128];;
//   int val;

//   if ( is.fail() )  return false;
//   while ( !is.eof() ){
//     memset( buf, 0, sizeof(buf) );
//     is.getline(buf, sizeof(buf), '\n');
//     if ( buf[0] == '#' ) continue;  

//     memset(name, 0, sizeof(name) );
//     memset( name2, 0, sizeof(name2) );
//     sscanf(buf, "%s = %d", name, &val);

//     if ( strcmp(name, "SOCKET_FILE") == 0 ){      
//       sscanf(buf, "%s = %s", name, name2);
//       socket_file = name2;
//     }    
//   }
//   return true;
// }


Socket* SocketIndex::get_socket(int tid)
{
  Socket* retval = NULL;
  pthread_mutex_lock(&table_mutex);
  if ( sockets.find(tid) != sockets.end() )
    retval = sockets[tid];
  pthread_mutex_unlock(&table_mutex);
  return retval;
}


Socket * SocketIndex::register_by_tid(int tid)
{
  Socket * sock = NULL;
  int retval;

  pthread_mutex_lock(&table_mutex);
  assert( sockets.find(tid) == sockets.end() );  
  
//   cerr<<" registered tid "<< tid<<endl;
  
#ifdef _USE_INET_
  sock = new Socket( SOCK_INET );  
  retval = sock->connect( "localhost", _INET_PORT_);
#else
  sock = new Socket( SOCK_UNIX );  
  retval = sock->connect( socket_file.c_str() );
#endif
  if (retval == -1) {
    pthread_mutex_unlock( &table_mutex );
    return NULL;
  }
  assert( tid >= 0 );
  sockets.insert( make_pair(tid, sock ) );

  pthread_mutex_unlock( &table_mutex );
  return sock;
}


Socket * SocketIndex::self_register()
{
  pthread_t myself;
  int thread_id;
  myself = pthread_self();
    
  if ( ! g_thread_index.is_member( myself ) )
    g_thread_index.insert( myself );
  
  thread_id = g_thread_index.get_my_thread_id();
  
  return this->register_by_tid( thread_id );
}


void SocketIndex::remove(int tid)
{
  pthread_mutex_lock(&table_mutex);
  assert( sockets.find(tid) != sockets.end() );
  Socket * sock = sockets[tid];
  delete sock;
  sockets.erase(tid);
  pthread_mutex_unlock(&table_mutex);
}


Socket * SocketIndex::get_my_socket()
{
  int thread_id;
  Socket * my_socket;
  iterator it;

  thread_id = g_thread_index.get_my_thread_id();

  pthread_mutex_lock(&table_mutex);
  it = sockets.find( thread_id );

  if ( it == sockets.end() ){
    cerr << "Error: fail to find socket for thread "<< thread_id << endl;
    cerr << " sockets.size() = " << sockets.size() << endl;

    for (it = sockets.begin(); it != sockets.end();it++){
      cerr << " socket info : "
	   << it->first << "  " << it->second << endl;
    }    
  }

  //  assert( it != sockets.end() );  
  my_socket = it->second;
  pthread_mutex_unlock(&table_mutex);

  return my_socket;
}


#ifdef NLZ_FLAG// OR NLZ_FLAG depends on the function call by other function(used in inspect_pthread.cc) 

MemoryOpBuffer::reverse_iterator MemoryOpBuffer::find_from_back(void* addr) {
    MemoryOpBuffer::reverse_iterator rit;
    for (rit=buffer.rbegin(); rit!=buffer.rend(); ++rit){
	if (rit->addr == addr) return rit;
    }
    return rit;
}

string MemoryOpBuffer::toString() const {
    std::stringstream ss;
    ss<<"buffer[[ ";
    if (buffer.empty()) return "buffer[[ None ]]";
    for (std::deque<MemoryOperation>::const_iterator it=buffer.begin(); it!=buffer.end()-1; ++it){
	ss<<it->toString()<<'\n';
    }
    ss<<(buffer.end()-1)->toString()<<"]]";
    return ss.str();
}


#endif
