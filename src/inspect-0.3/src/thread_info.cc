#include "thread_info.hh"
#include <cassert>
#include <sstream>

using namespace std;
using namespace __gnu_cxx;

// global declaration of thread table


ThreadTable  thread_table;

ThreadTable::ThreadTable()
{  
  threads.clear();
  this->add_main();
}


ThreadTable::~ThreadTable()
{
  this->clear();
}


void ThreadTable::clear()
{
  iterator it;
  ThreadInfo * thread;

  for (it = threads.begin(); it != threads.end(); it++){
    thread = it->second;
    delete thread;
  }
  threads.clear();  
}

void ThreadTable::reset()
{
  this->clear();
  this->add_main();
}


void ThreadTable::add_main()
{
  ThreadInfo * info;
  info = new ThreadInfo();
  info->tid = 0;
  info->name = "main";
  info->arg = 0;
  threads.insert( make_pair(0, info) );
}

void ThreadTable::add_thread(int tid, const char * name, void * arg)
{
  ThreadInfo * info;
  info = new ThreadInfo();
  info->tid = tid;
  info->name = name;
  info->arg = arg;
  assert( threads.find(tid) == threads.end() );
  threads.insert( make_pair(tid, info) );
}


void ThreadTable::add_thread(int tid, string &name, void *arg)
{
  ThreadInfo * info;
  info = new ThreadInfo();
  info->tid = tid;
  info->name = name;
  info->arg = arg;
  assert( threads.find(tid) == threads.end() );
  threads.insert( make_pair(tid, info) );
}


vector<ThreadInfo*>  ThreadTable::get_threads_by_name(string &name)
{
  iterator it;
  ThreadInfo * info;
  vector<ThreadInfo*>  tids;

  for (it = threads.begin(); it != threads.end(); it++){
    info = it->second;
    if (info->name == name)  tids.push_back(info);
  }
  return tids;
}


ThreadInfo * ThreadTable::get_thread(int tid)
{
  assert(tid >= 0);
  iterator it;
  it = threads.find(tid);
  assert( it != threads.end() );
  assert( it->second != NULL );
  return it->second;
}


bool ThreadTable::is_symmetric_threads(int t1, int t2)
{
  ThreadInfo * thread1, * thread2;
  
  assert(t1 != t2);
  thread1 = this->get_thread(t1);
  thread2 = this->get_thread(t2);
  
  assert(thread1 != NULL);
  assert(thread2 != NULL);
  
  if (thread1->name == thread2->name && thread1->arg == thread2->arg) return true;
  return false;
}



string  ThreadTable::toString()
{
  ThreadInfo * info;
  stringstream ss;

  iterator it;
  for (it = threads.begin(); it != threads.end(); it++){
    info = it->second;
    ss <<"("
       << info->tid << ", "
       << info->name << ", "
       << hex << info->arg << ")\n";
  }  
  return ss.str();
}






