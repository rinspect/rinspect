#ifndef __LOCKSET_HH__
#define __LOCKSET_HH__

#include <set>
#include <string> 
#include <ext/hash_map>

using std::set;
using std::string;
using __gnu_cxx::hash_map;


class Lockset
{
public:
  typedef set<int>::iterator  iterator; 

  public:
  Lockset(){  locks.clear();  }
  Lockset(Lockset & set);
  ~Lockset(){}
  void insert(int lid);
  void remove(int lid);
  bool mutual_exclusive(Lockset & lkst);
  inline bool has_member(int lid) {  return  locks.find(lid) != locks.end(); }

  Lockset intersect(Lockset);
  Lockset intersect(Lockset*);
  string toString();

  bool empty() { return locks.empty(); } 
  int get_lock() { return  *locks.begin(); }

  Lockset& operator=(Lockset);
public:
  set<int> locks;
};



class Locksets
{
public:
  typedef hash_map<int, Lockset*>::iterator iterator;
  
public:
  Locksets();
  ~Locksets();
  Locksets(Locksets &copy);

  void add_thread(int tid);
  void remove_thread(int tid);

  Lockset* get_lockset(int tid);
  void acquire(int tid, int mid);
  void release(int tid, int mid);

  Locksets & operator = (Locksets& sets);
public:
  hash_map<int, Lockset*>  sets;
};



class Rwlockset
{
public:
  typedef set<int>::iterator  iterator; 

public:
  Rwlockset() { rwlocks.clear(); } 
  ~Rwlockset() {}
  void insert(int lid);
  void remove(int lid);
  string toString();

public:
  set<int>  rwlocks;
};


class Rwlocksets
{
public:
  hash_map<int, Lockset*>::iterator iterator;
  
public:
  Rwlocksets();
  ~Rwlocksets();
};


#endif
