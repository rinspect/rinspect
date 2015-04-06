#ifndef CLAP_UCG_GRAPH_HH
#define CLAP_UCG_GRAPH_HH

#include "yices_dp.hh"

#include <pthread.h>
#include <stdio.h>
#include <map>
#include <vector>

using namespace std;


//////////////////////////////////////////////////////////////////////////////
//
// checking if there exists a set of satisfying assignments to the PolyEdges
// (either ... or ...) such that there is not cycle in the graph 
//
// Note:
//
// 1. nodes are the UCG trace events
//
// 2. edges are the UCG edges (must-happen-before relation between events)
//
// 3. poly-edges are the pairs of critical sections
//
//    for example,
//
//       Thread#1 --> ev1:LOCK(l) ---> ev2:UNLOCK(l) -->
//       Thread#2 --> ev3:LOCK(l) ---> ev4:UNLOCK(l) -->
//
//    we have the following choice,
//
//       Either  must-happen-before(ev4,ev1)
//       Or      must-happen-before(ev2,ev3)
//        
//    This choice is represented as a Poly-Edge( ev4, ev1, ev2, ev3 );
//
//////////////////////////////////////////////////////////////////////////////

class PolyGraph {

public:
  
  PolyGraph() { 
    yices = new YicesDP();
    yices->set_default_var_type( YicesDP::INTty );
  }

  ~PolyGraph() {
    if (yices != NULL) {
      delete yices;
      yices = NULL;
    }
  }

  //void addNode(int event_id);  

  void addEdge(int src_ev, int tgt_ev, bool retractable);

  void block_trace(vector<pair<int,int> > edges, bool retractable);
  YicesDP::expr not_multiAnd(vector<pair<int, int> > edges);
  YicesDP::expr value_not_the_same(map<int,int> all_int);


  void removeEdge(int src_ev, int tgt_ev);

  void addPolyEdge(int either_src, int either_tgt, int or_src, int or_tgt, bool retractable);
  void removePolyEdge(int either_src, int either_tgt, int or_src, int or_tgt);

  bool check(); // return TRUE if graph is satisfable

  bool check_and_getValue();


  void make_distinct_vals();

  void test(); //sample code

public:
  YicesDP *yices;
  map<pair<int,int>,assertion_id> map_edge;
  map<pair<pair<int,int>,pair<int,int> >,assertion_id> map_poly_edge;
  vector<vector<pair<int,int> > > blocked_edges;
  vector<int> all_vals;

};



#endif //CLAP_UCG_GRAPH_HH
