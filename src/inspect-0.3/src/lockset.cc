#include "lockset.hh"
#include <cassert>
#include <sstream>
#include <utility>
#include <iostream>
using namespace std;



Lockset::Lockset(Lockset & set)
{
  locks = set.locks;
}


void Lockset::insert(int lid)
{
  set<int>::iterator it;
  it = locks.find(lid);
  assert( it == locks.end() );
  locks.insert(lid);
}


void Lockset::remove(int lid)
{
  set<int>::iterator it;
  it = locks.find(lid);
  assert( it != locks.end() );
  locks.erase(lid);
}


string Lockset::toString()
{
  stringstream ss;
  set<int>::iterator it;

  ss <<"{";
  for (it = locks.begin(); it != locks.end(); it++){
    ss << *it <<",";
  }
  ss <<"}";
  return ss.str();
}



bool  Lockset::mutual_exclusive(Lockset & lkst)
{
  iterator it;
  for (it = locks.begin(); it != locks.end(); it++){
    if (lkst.has_member(*it)) return true;
  }
  return false;
}


Lockset  Lockset::intersect(Lockset another_set)
{
  Lockset result;
  iterator it;
  int lock_id;

  for (it = locks.begin(); it != locks.end(); it++){
    lock_id = *it;
    if (another_set.has_member(lock_id))
      result.insert(lock_id);
  }
  return result;
}


Lockset Lockset::intersect(Lockset * another_set)
{
  Lockset result;
  iterator it;
  int lock_id;

  for (it = locks.begin(); it != locks.end(); it++){
    lock_id = *it;
    if (another_set->has_member(lock_id))
      result.insert(lock_id);
  }
  return result;
}



Lockset& Lockset::operator=(Lockset lkset)
{
  locks = lkset.locks;
  return *this;
}


///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

Locksets::Locksets()
{
  sets.clear();
}


Locksets::~Locksets()
{
  hash_map<int, Lockset*>::iterator it;
  Lockset * ptr;
  for (it = sets.begin(); it != sets.end(); it++){
    ptr= it->second;
    delete ptr;
  }
  sets.clear();
}


Locksets & Locksets::operator = (Locksets & another)
{
  iterator it;
  int lock_id;
  Lockset * set, * new_set;

  for (it = another.sets.begin(); it != another.sets.end(); it++){
    lock_id = it->first;
    set = it->second;
    new_set = new Lockset(*set);
    sets.insert( make_pair(lock_id, new_set) );
  }
  return *this;
}


Lockset * Locksets::get_lockset(int tid)
{
  iterator it;
  it = sets.find(tid);

  if (it == sets.end()) return NULL;
  return it->second;
}


void Locksets::add_thread(int tid)
{
  Lockset * lockset;

  assert(tid >= 0);
  assert( sets.find(tid) == sets.end() );

  lockset = new Lockset();
  sets.insert( make_pair(tid, lockset) );
}


void Locksets::remove_thread(int tid)
{
  Lockset * lockset;
  iterator it;

  assert(tid >= 0);
  it = sets.find(tid);
  lockset = it->second;
  delete lockset;
  sets.erase(tid);
}


void Locksets::acquire(int tid, int mid)
{
  iterator it;
  Lockset * lockset;
  it = sets.find(tid);
  assert(it != sets.end());
  lockset = it->second;
  lockset->insert(mid);
}


void Locksets::release(int tid, int mid)
{
  iterator it;
  Lockset * lockset;
  it = sets.find(tid);
  assert(it != sets.end());
  lockset = it->second;
  lockset->remove(mid);
}

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////



void Rwlockset::insert(int lid)
{
  set<int>::iterator it;
  it = rwlocks.find(lid);
  assert( it == rwlocks.end() );
  rwlocks.insert(lid);
}


void Rwlockset::remove(int lid)
{
  set<int>::iterator it;
  it = rwlocks.find(lid);
  assert( it != rwlocks.end() );
  rwlocks.erase(lid);
}


string Rwlockset::toString()
{
  stringstream ss;
  set<int>::iterator it;

  ss <<"{";
  for (it = rwlocks.begin(); it != rwlocks.end(); it++){
    ss << *it <<",";
  }
  ss <<"}";
  return ss.str();
}

