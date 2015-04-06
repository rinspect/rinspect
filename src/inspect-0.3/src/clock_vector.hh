#ifndef __CLOCK_VECTOR_H__
#define __CLOCK_VECTOR_H__

#include <vector>
#include <string>

#ifdef __GNUC__
  #include <ext/hash_map>
  using __gnu_cxx::hash_map;
#else
  #include <hash_map>
#endif


using std::vector;
using std::string;

/**
 *  the clock vector 
 * 
 */
class ClockVector
{
public:
  ClockVector();
  ClockVector(ClockVector& cv);
  ClockVector(int num_threads);
  ~ClockVector();
  int& operator[](int pos);    
  string toString();
  int size() { return timestamps.size(); } 
  
  void clear();
  void increase_size(int sz, int init_val = -1 );
  void resize(int size, int init_val = -1);
  void merge(ClockVector & another_vec);

  bool must_happen_before(ClockVector & another_vec);  
  bool is_concurrent_with(ClockVector & another_vec);

  ClockVector * duplicate();
public:
  int width; 
  vector<int> timestamps;
};



/**
 *  this is a set of clock vectors
 */
class ClockVectorList
{
public:
  typedef vector<ClockVector*>::iterator  iterator;
  
public:
  ClockVectorList();
  ClockVectorList(ClockVectorList & cvs);
  ~ClockVectorList();

  iterator begin() { return vecs.begin();}
  iterator end()   { return vecs.end();  }

  int size() { return vecs.size(); } 
  ClockVectorList & operator=(ClockVectorList& cvlst);

  ClockVector * get_clock_vector(int tid);
  
  void add_thread(int thread_id, int parent);
  void add_the_first_thread();
public:
  vector<ClockVector*>  vecs;
};


#endif

