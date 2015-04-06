#ifndef __SCHEDULER__OBJECT__TABLE__H__
#define __SCHEDULER__OBJECT__TABLE__H__

#include "inspect_event.hh"
#include <set>
#include <vector>


#include <ext/hash_map>
#include <deque>


using std::vector;
using std::deque;
using std::set;
using __gnu_cxx::hash_map;


class SchedulerMutex
{
public:
  SchedulerMutex();
  SchedulerMutex(int mid, int is_recursive);
  ~SchedulerMutex();

  inline int get_id()             { return id;    } 
  inline int get_owner()          { return owner; } 
  inline void set_owner( int oid) { owner = oid;  } 
  inline bool is_available()      { return owner == -1; } 

  
  bool acquire_by(int tid);
  void release();
  void reset();
  SchedulerMutex * duplicate();
  
  bool operator==(SchedulerMutex &another);
  bool operator!=(SchedulerMutex &another);
public:
  int id;
  int owner;

#ifdef RSS_EXTENSION
  int is_recursive;
  int count;
#endif//RSS_EXTENSION

};



class SchedulerMutexIndex
{
public:
  typedef hash_map<int, SchedulerMutex*>::iterator iterator;
public:
  SchedulerMutexIndex();
  ~SchedulerMutexIndex();
  
  inline int size() { return mutexes.size(); }
  SchedulerMutexIndex & operator =(SchedulerMutexIndex &midx);
  void clear();
  void init(int mid, int is_recursive);
  void remove(int mid);
  SchedulerMutex * get_mutex(int mid);
  void reset_mutexes_heldby_thread(int tid); //RSS

  bool is_member( int mid );
    
  bool operator==(SchedulerMutexIndex &another);
  bool operator!=(SchedulerMutexIndex &another);
  
public:
  hash_map<int, SchedulerMutex*> mutexes;
};



// class SchedulerCond
// {
// public:
//   SchedulerCond();
//   SchedulerCond(int);
//   ~SchedulerCond();

//   SchedulerCond * duplicate();
// public:
//   int id;
// };


// class SchedulerCondIndex
// {
// public:
//   SchedulerCondIndex();
//   ~SchedulerCondIndex();
  
//   void clear();
//   void init(int cid);
//   void destroy(int cid);

//   SchedulerCond * get_cond(int cid);
//   bool is_member(int cid);

//   void copy(SchedulerCondIndex& scidx);

// public:
//   hash_map<int, SchedulerCond*> conds;
// };


enum RwlockStatus
{
  RWLS_READING = 0, 
  RWLS_WRITING = 1, 
  RWLS_IDLE = 2,
  RWLS_ERROR = 3
};


class SchedulerRwlock
{
public:
  SchedulerRwlock();
  SchedulerRwlock(int lid);
  ~SchedulerRwlock();
  
  inline RwlockStatus get_status()               { return status; } 

  void reader_acquire(int tid);
  void writer_acquire(int tid);
  void release(int tid);
  
  SchedulerRwlock  * duplicate();

  bool operator==(SchedulerRwlock& another);
  bool operator!=(SchedulerRwlock& another);

public:
  RwlockStatus status;
  int rwlock_id;
  set<int> readers;
  int writer;
};



class SchedulerRwlockIndex
{
public:
  typedef hash_map<int, SchedulerRwlock*>::iterator  iterator;
public:
  SchedulerRwlockIndex();
  ~SchedulerRwlockIndex();
  
  SchedulerRwlockIndex & operator =(SchedulerRwlockIndex &r);
  void clear();
  void init(int lid);
  void destroy(int lid);
  
  SchedulerRwlock * get_rwlock(int lid);
  bool is_member(int lid);

  bool operator==(SchedulerRwlockIndex &another);
  bool operator!=(SchedulerRwlockIndex &another);

  inline int size(){  return rwlocks.size(); }

public:
  hash_map<int, SchedulerRwlock*> rwlocks;
};




#endif


