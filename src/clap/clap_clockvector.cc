#include "clap_clockvector.hh"


ClockVector::ClockVector()
{

}

ClockVector::~ClockVector()
{

}

void ClockVector::insert_thread(ThreadId t)
{
  clocks[t] = 0;
}

void ClockVector::increment(ThreadId t)
{
  clocks[t]++;
}

// Merging two clock vectors: "this" and "other"
// 
// for each thread in either "this" or "other", or in both 
//    choose the larger clock value
//
// for example:  this = { T1 => 5,  T3 => 7 , T7 => 0}
//              other = { T1 => 3,  T3 => 10, T5 => 2}
//
//     result is    { T1 => 5,  T3 => 10, T5 => 2, T7 => 0 }

void ClockVector::merge(ClockVector& other)
{
  map<ThreadId,int>::iterator it;
  for(it = other.clocks.begin(); it != other.clocks.end(); it++) {
    ThreadId tid  = it->first;
    int val = it->second;
    
    int this_val = -1; 
    map<ThreadId,int>::iterator it0 = this->clocks.find(tid);
    if (it0 != this->clocks.end()) {
      this_val = it0->second;
    }
    
    int new_val = (this_val > val)? this_val: val;

    this->clocks[tid] = new_val;
  }
}

bool ClockVector::must_happen_before_except(ClockVector &other, int except)
{
  map<ThreadId,int> union_map = other.clocks;
  union_map.insert(clocks.begin(), clocks.end());

  map<ThreadId,int>::iterator it;
  for (it = union_map.begin(); it != union_map.end(); it++) {
    int tid = it->first;
    if (tid==except) continue;

    // value in this clock vector
    int this_val = -1;
    map<ThreadId,int>::iterator it1 = clocks.find(tid);
    if (it1 != clocks.end()) {
      this_val = it1->second;
    }
    // value in other clock vector
    int other_val = -1;
    map<ThreadId,int>::iterator it2 = other.clocks.find(tid);
    if (it2 != other.clocks.end()) {
      other_val = it2->second;
    }
//    cout<<"tid: "<<tid<< "       "<<this_val<<" vs "<<other_val<<endl;

    if (this_val < other_val)    return false;
  }

  return true;
}

bool ClockVector::must_happen_before(ClockVector &other)
{
  map<ThreadId,int> union_map = other.clocks;
  union_map.insert(clocks.begin(), clocks.end());

  map<ThreadId,int>::iterator it;
  for (it = union_map.begin(); it != union_map.end(); it++) {
    int tid = it->first;

    // value in this clock vector
    int this_val = -1;
    map<ThreadId,int>::iterator it1 = clocks.find(tid);
    if (it1 != clocks.end()) {
      this_val = it1->second;
    }    
    // value in other clock vector
    int other_val = -1;
    map<ThreadId,int>::iterator it2 = other.clocks.find(tid);
    if (it2 != other.clocks.end()) {
      other_val = it2->second;
    }

    if (this_val > other_val)    return false;
  }
  
  return true;
}

bool ClockVector::may_happen_concurrently(ClockVector &other) 
{
  bool res1 = this->must_happen_before(other);
  bool res2 = other.must_happen_before(*this);
  
  return ( !res1 && !res2);
}

string ClockVector::toString()
{
  stringstream ss;

  ss << "{ ";

  map<ThreadId,int>::iterator it;
  for (it = clocks.begin(); it != clocks.end(); it++) {
    ThreadId tid = it->first;
    int val = it->second;
    if (it != clocks.begin()) 
      ss << " , ";
    ss << tid << ":" << val;
  }

  ss << " }";

  return ss.str();
}
