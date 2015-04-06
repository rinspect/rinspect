#include "clap_lockset.hh"
#include <algorithm>


bool LockSet::intersectIsEmpty(LockSet& set2)
{
  set<MutexId> v;
  set_intersection(locks.begin(), locks.end(), 
                   set2.locks.begin(), set2.locks.end(), 
                   inserter(v,v.begin()) );
  return (v.size() == 0);
}

set<MutexId> LockSet::intersect(LockSet& set2)
{
  set<MutexId> v;
  set_intersection(locks.begin(), locks.end(), 
                   set2.locks.begin(), set2.locks.end(), 
                   inserter(v,v.begin()) );
  return v;
}

string LockSet::toString()
{
  stringstream ss;

  ss << "{ ";

  set<MutexId>::iterator it;
  for (it = locks.begin(); it != locks.end(); it++) {
    if (it != locks.begin()) 
      ss << ", ";
    ss << (*it);
  }

  ss << " }";

  return ss.str();
}

