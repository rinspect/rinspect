#ifndef __CLAP_CLOCKVECTOR_HH__
#define __CLAP_CLOCKVECTOR_HH__

#include <cstring> 
#include <cassert>
#include <string> 
#include <map>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

typedef int ThreadId;

class ClockVector 
{
public:
  map<ThreadId,int>  clocks;

public:
  ClockVector();
  ~ClockVector();

  void insert_thread(ThreadId t);
  void increment(ThreadId t);
  void merge(ClockVector &other);
  bool must_happen_before(ClockVector &other);
  bool must_happen_before_except(ClockVector &other, int except);
  bool may_happen_concurrently(ClockVector &other);

  string toString();
};

#endif // #ifndef __CLAP_CLOCKVECTOR_HH__
