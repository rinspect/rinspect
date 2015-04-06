#ifndef __THREAD_INFO_H__
#define __THREAD_INFO_H__

#include <vector>
#include <string>
#include <ext/hash_map>

using std::string;
using std::vector;
using __gnu_cxx::hash_map;


struct ThreadInfo
{
  int  tid;
  string  name;
  void * arg;
};


class ThreadTable
{
public:
  typedef hash_map<int, ThreadInfo*>::iterator iterator;
public:
  ThreadTable();
  ~ThreadTable();
 
  void clear();
  void reset();
  void add_thread(int tid, const char * name, void *arg);
  void add_thread(int tid, string &name,  void * arg);
  void add_main();

  vector<ThreadInfo*> get_threads_by_name(string &name);
  ThreadInfo * get_thread(int tid);

  string toString();

  bool is_symmetric_threads(int t1, int t2);
public:
  hash_map<int, ThreadInfo *> threads;
};


extern ThreadTable thread_table;

#endif

