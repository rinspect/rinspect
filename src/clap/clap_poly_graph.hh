#ifndef CLAP_POLY_GRAPH_HH
#define CLAP_POLY_GRAPH_HH

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
// 1. nodes are the POLY trace events
//
// 2. edges are the POLY edges (must-happen-before relation between events)
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

class PolyGraphSMT {

public:
  
public:

  PolyGraphSMT() { 
	  return;
    yices = new YicesDP();
    yices->set_default_var_type( YicesDP::INTty );
  }

  ~PolyGraphSMT() {
    if (yices != NULL) {
      delete yices;
      yices = NULL;
    }
  }

  //void addNode(int event_id);  

  void addEdge(int src_ev, int tgt_ev, bool retractable);
  void addEdgeConditional(int src_ev, int tgt_ev, bool retractable);
  void addEdge_internal(int src_ev, int tgt_ev, bool tgt_is_coupleR, bool retractable);
  void removeEdge(int src_ev, int tgt_ev);

  void addGuard(int src_ev, int tgt_ev, bool retractable);
  void addGuardRead(int src_ev, int tgt_ev, bool retractable);
  void addGuardAcq(int src_ev, int tgt_ev, bool retractable);
  void addGuardJoin(int src_ev, int src2_ev, int tgt_ev, bool retractable);
  void addGuard_internal(int src_ev, int src2_ev, int tgt_ev, bool src_is_a_R, 
                         bool src2_available, bool retractable);
  void removeGuard(int src_ev, int tgt_ev);

  void addReachableCond(int ev, bool retractable);
  void removeReachableCond(int ev);

  void addPolyEdge(int either_src, int either_tgt, int or_src, int or_tgt, bool retractable);
  void addPolyEdge_AcqRel(int either_src, int either_tgt, int or_src, int or_tgt, bool retractable);
  void addPolyEdgeConditional(int either_src, int either_tgt, int or_src, int or_tgt, int coupledR, bool use_coupledR, bool retractable);
  void removePolyEdge(int either_src, int either_tgt, int or_src, int or_tgt);

  bool check();
    
  YicesDP *yices;
  map<pair<int,int>,assertion_id> map_edge;
  map<pair<int,int>,assertion_id> map_guard;
  map<pair<pair<int,int>,pair<int,int> >,assertion_id> map_poly_edge;
  map<int,assertion_id> map_condition;
};



#endif //CLAP_POLY_GRAPH_HH
