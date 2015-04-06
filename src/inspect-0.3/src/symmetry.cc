#include "symmetry.hh"
#include <cassert>

using namespace std;


bool  Symmetry::is_symmetry(int t1, int t2)
{
  int_set * ptr;
  vector<int_set*>::iterator it;
  
  for (it = symm_sets.begin(); it != symm_sets.end(); it++){
    ptr = *it;
    assert(ptr != NULL);
    if (ptr->find(t1) != ptr->end())
  }
  
}



