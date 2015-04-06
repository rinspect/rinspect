#ifndef __CLAP_LOCKSET_HH__
#define __CLAP_LOCKSET_HH__


#include <cstring> 
#include <cassert>
#include <string> 
#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

typedef int MutexId;

class LockSet 
{
public: 

  set<MutexId>  locks;
  void insert(MutexId m) {  locks.insert(m); }
  void erase(MutexId m) { locks.erase(m); }
  void clear() { locks.clear(); }
  set<MutexId> intersect(LockSet& set2);
  bool intersectIsEmpty(LockSet& set2);
  int size() { return locks.size(); }

  string toString();
};

typedef class LockSet  VarSet;
typedef class LockSet  CondSet;


#endif // #ifndef __CLAP_LOCKSET_HH__
