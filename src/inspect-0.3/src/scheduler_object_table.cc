#include "scheduler_object_table.hh"
#include <iostream>

using namespace std;


////////////////////////////////////////////////////////////////////////////
//
//  the implementation of SchedulerMutex
//
////////////////////////////////////////////////////////////////////////////


SchedulerMutex::SchedulerMutex()
  : id(-1), owner(-1) , is_recursive(0), count(0)
{ }


SchedulerMutex::SchedulerMutex(int mid, int recur)
  : id(mid), owner(-1), is_recursive(recur), count(0)
{ }


SchedulerMutex::~SchedulerMutex()
{ }


/**
 *  reset the mutex's status to the initial state, clear the 
 *  waiting list and ower, etc
 */
void SchedulerMutex::reset()
{  
  owner = -1; 
  count = 0;
}


bool SchedulerMutex::acquire_by(int tid)
{
  count++;

  if (owner == -1){
    owner = tid; 
    return true;
  }

  if (is_recursive && owner == tid)
    return true;

  assert(false);
  return false;
}


void SchedulerMutex::release()
{
  count --;

  if ( !is_recursive || count <= 0) {
    owner = -1;
  }
}

SchedulerMutex *  SchedulerMutex::duplicate()
{
  SchedulerMutex * new_copy;
  new_copy = new SchedulerMutex();
  new_copy->id = this->id;
  new_copy->owner = this->owner;
  new_copy->count = this->count;
  new_copy->is_recursive = this->is_recursive;
  return new_copy;
}


bool SchedulerMutex::operator==(SchedulerMutex &another)
{
  return (id == another.id) && (owner == another.owner);
}


bool SchedulerMutex::operator!=(SchedulerMutex &another)
{
  return (id != another.id) || (owner != another.owner);
}




////////////////////////////////////////////////////////////////////////////
//
//  implementation of SchedulerMutexIndex 
//
////////////////////////////////////////////////////////////////////////////


SchedulerMutexIndex::SchedulerMutexIndex()
{
  mutexes.clear();
}

SchedulerMutexIndex::~SchedulerMutexIndex()
{
  this->clear();
}


void SchedulerMutexIndex::clear()
{
  hash_map<int, SchedulerMutex*>::iterator it;
  SchedulerMutex * mutex;

  for (it = mutexes.begin(); it != mutexes.end(); it++){
    mutex = it->second;
    delete mutex;
  }
  mutexes.clear();
}


void SchedulerMutexIndex::init(int mid, int recur)
{
  SchedulerMutex * mutex;
  assert( mid > 0 );
  mutex = new SchedulerMutex(mid, recur);
  mutexes.insert( make_pair(mid, mutex) );
}


SchedulerMutex * SchedulerMutexIndex::get_mutex(int mid)
{
  hash_map<int,SchedulerMutex*>::iterator it;  
  it = mutexes.find( mid );
  assert( it != mutexes.end() );
  return it->second;  
}

void SchedulerMutexIndex::reset_mutexes_heldby_thread(int tid)
{
  //chao: reset all MUTEX held by the cancelled thread
  hash_map<int,SchedulerMutex*>::iterator it;
  for (it = mutexes.begin(); it != mutexes.end(); it++){
    SchedulerMutex* mutex = it->second;
    if (mutex->get_owner() == tid) {
      mutex->reset();
    }
  }
}
  
void SchedulerMutexIndex::remove(int mid)
{
  hash_map<int,SchedulerMutex*>::iterator it;
  it = mutexes.find( mid );
  assert( it != mutexes.end() );

  delete it->second;
  mutexes.erase(it);
}


bool SchedulerMutexIndex::is_member( int mid )
{
  hash_map<int, SchedulerMutex*>::iterator it;
  it = mutexes.find( mid );
  return  it != mutexes.end();
}



SchedulerMutexIndex & SchedulerMutexIndex::operator = (SchedulerMutexIndex &midx)
{
  hash_map<int, SchedulerMutex*>::iterator it;
  SchedulerMutex * mutex;
  int mid;

  mutexes.clear();
  for (it = midx.mutexes.begin(); it != midx.mutexes.end(); it++){
    mid = it->first;
    mutex = it->second;
    mutexes[mid] = mutex->duplicate();
  }
  return *this;
}


bool SchedulerMutexIndex::operator==(SchedulerMutexIndex &another)
{
  iterator it;
  int mutex_id;
  SchedulerMutex * mutex1, *mutex2;

  if (this->size() != another.size()) return false;
  
  for (it = mutexes.begin(); it != mutexes.end(); it++){
    mutex_id = it->first;
    mutex1 = it->second;
    mutex2 = another.get_mutex(mutex_id);
    if (*mutex1 != *mutex2) return false;
  }
  return true;
}

bool SchedulerMutexIndex::operator!=(SchedulerMutexIndex &another)
{
  return !(*this == another);
}

/////////////////////////////////////////////////////////////////////////
//
//  the implementation of SchedulerCond
//
/////////////////////////////////////////////////////////////////////////

// SchedulerCond::SchedulerCond()
//   : id(-1)
// {}

// SchedulerCond::SchedulerCond(int cid)
//   : id(cid)
// { }
 

// SchedulerCond::~SchedulerCond()
// {}


// SchedulerCond * SchedulerCond::duplicate()
// {
//   SchedulerCond * new_copy;
//   new_copy = new SchedulerCond();
//   new_copy->id = id;
//   return new_copy;
// }



////////////////////////////////////////////////////////////////////////////
//
//  the implementation of SchedulerCondIndex
//
////////////////////////////////////////////////////////////////////////////


// SchedulerCondIndex::SchedulerCondIndex()
// {  
//   conds.clear();
// }


// SchedulerCondIndex::~SchedulerCondIndex()
// { }


// void SchedulerCondIndex::clear()
// {
//   hash_map<int, SchedulerCond*>::iterator it;
//   SchedulerCond * cond;

//   for (it = conds.begin(); it != conds.end(); it++){
//     cond = it->second;
//     delete cond;
//   }
//   conds.clear();
// }


// void SchedulerCondIndex::init(int cid)
// {
//   SchedulerCond * cond;
//   assert( cid > 0 );

// //   cerr <<" init a new Cond .. \n";
//   cond = new SchedulerCond(cid);
//   conds.insert( make_pair(cid, cond) );
// }


// void SchedulerCondIndex::destroy(int cid)
// {
//   hash_map<int, SchedulerCond*>::iterator it;
//   it = conds.find( cid );
//   assert( it != conds.end() );
  
//   delete it->second;
//   conds.erase(it);
// }


// SchedulerCond * SchedulerCondIndex::get_cond(int cid)
// {
//   hash_map<int, SchedulerCond*>::iterator it;

//   it = conds.find( cid );
//   assert( it != conds.end() );
//   return it->second;
// }


// bool SchedulerCondIndex::is_member(int cid)
// {
//   hash_map<int, SchedulerCond*>::iterator it;
//   it = conds.find(cid);
//   return it != conds.end();
// }


// void SchedulerCondIndex::copy(SchedulerCondIndex & scidx)
// {
//   hash_map<int, SchedulerCond*>::iterator it;
//   int sid;
//   SchedulerCond * sc;

//   for (it = scidx.conds.begin(); it != scidx.conds.end(); it++){
//     sid = it->first;
//     sc = it->second;
//     conds[sid] = sc->duplicate();
//   }
// }

////////////////////////////////////////////////////////////////////////////////
//
//  implementation of Rwlock 
//
////////////////////////////////////////////////////////////////////////////////


SchedulerRwlock::SchedulerRwlock()
  : status( RWLS_IDLE ),
    rwlock_id(-1),
    writer(-1)
{
  readers.clear();
}


SchedulerRwlock::SchedulerRwlock(int lid)
  : status( RWLS_IDLE ),
    rwlock_id(lid),
    writer(-1)
{
  readers.clear();
}


SchedulerRwlock::~SchedulerRwlock()
{ }



void SchedulerRwlock::reader_acquire(int tid)
{
  assert( status == RWLS_IDLE || status == RWLS_READING );
  status = RWLS_READING;
  readers.insert(tid);
}


void SchedulerRwlock::writer_acquire(int tid)
{
  assert( status == RWLS_IDLE );
  assert( readers.empty() );
  assert( writer == -1 );
  status = RWLS_WRITING;
  writer = tid;
}


void SchedulerRwlock::release(int tid)
{
  if (writer == tid){
    assert(status == RWLS_WRITING);
    assert(readers.empty());
    writer = -1;
    status = RWLS_IDLE;
    return;
  }
  
  assert(status == RWLS_READING);
  assert(readers.find(tid) != readers.end());
  readers.erase(tid);  
  if(readers.empty()) 
    status = RWLS_IDLE;
}


SchedulerRwlock * SchedulerRwlock::duplicate()
{
  SchedulerRwlock * rwlock = NULL;
  rwlock = new SchedulerRwlock(rwlock_id);
  rwlock->status = status;
  rwlock->readers = readers;
  rwlock->writer = writer;
  return rwlock;
}


bool SchedulerRwlock::operator==(SchedulerRwlock &another)
{
  if (rwlock_id != another.rwlock_id) return false;
  if (status != another.status) return false;

  switch(status){
  case RWLS_READING:
    if (readers != another.readers) return false;
    break;

  case RWLS_WRITING: 
    if (writer != another.writer) return false;
    
  default:  break;
  }
  return true;
}


bool SchedulerRwlock::operator!=(SchedulerRwlock &another)
{
  return !(*this == another);
}

/////////////////////////////////////////////////////////////////////////////
// 
//  
//
/////////////////////////////////////////////////////////////////////////////

SchedulerRwlockIndex::SchedulerRwlockIndex()
{
  rwlocks.clear();
}


SchedulerRwlockIndex::~SchedulerRwlockIndex()
{
  this->clear();
}


void SchedulerRwlockIndex::clear()
{
  hash_map<int, SchedulerRwlock*>::iterator it;
  SchedulerRwlock * rwlock;

  for (it = rwlocks.begin(); it != rwlocks.end(); it++){
    rwlock = it->second;
    delete rwlock;
  }
  rwlocks.clear();  
}


void SchedulerRwlockIndex::init(int lid)
{
  SchedulerRwlock * rwlock;
  rwlock = new SchedulerRwlock(lid);  
  rwlocks.insert( make_pair(lid, rwlock) );
}


void SchedulerRwlockIndex::destroy(int lid)
{
  hash_map<int, SchedulerRwlock*>::iterator it;
  it = rwlocks.find( lid );
  assert( it != rwlocks.end() );
  delete it->second;
  rwlocks.erase( it );
}


SchedulerRwlock * SchedulerRwlockIndex::get_rwlock(int lid)
{
  hash_map<int, SchedulerRwlock*>::iterator it;
  it = rwlocks.find(lid);
  assert( it != rwlocks.end() );
  return it->second;
}


bool SchedulerRwlockIndex::is_member(int lid)
{
  hash_map<int, SchedulerRwlock*>::iterator it;
  it = rwlocks.find(lid);
  return it != rwlocks.end(); 
}



SchedulerRwlockIndex&  SchedulerRwlockIndex::operator =(SchedulerRwlockIndex & rwidx)
{
  hash_map<int, SchedulerRwlock*>::iterator it;
  SchedulerRwlock * rwlock;
  int lid;

  this->rwlocks.clear();
  for (it = rwidx.rwlocks.begin(); it != rwidx.rwlocks.end(); it++){
    lid = it->first;
    rwlock = it->second;
    rwlocks[lid] = rwlock->duplicate();    
  }  

  return *this;
}



bool SchedulerRwlockIndex::operator==(SchedulerRwlockIndex &another)
{
  iterator it;
  int rwlock_id;
  SchedulerRwlock * rwlock1, *rwlock2;
  
  if (this->size() != another.size()) return false;
  
  for (it = rwlocks.begin(); it != rwlocks.end(); it++){
    rwlock_id = it->first;
    rwlock1 = it->second;
    rwlock2 = another.get_rwlock(rwlock_id);
    if (*rwlock1 != *rwlock2) return false;
  }
  
  return true;
}


bool SchedulerRwlockIndex::operator!=(SchedulerRwlockIndex &another)
{
  return !(*this == another);
}


