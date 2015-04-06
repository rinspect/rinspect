#include "clap_poly_graph.hh"

#define MK_NUM(n)       yices->mk_num_int(n)
#define MK_VAR(n,t)     yices->mk_var(n,t)
#define MK_INT_VAR(n)   yices->mk_var(n,YicesDP::INTty)
#define MK_BOOL_VAR(n)  yices->mk_var(n,YicesDP::BOOLty)
#define MK_OR(a,b)      yices->mk_or(a,b)
#define MK_AND(a,b)     yices->mk_and(a,b)
#define MK_NOT(a)       yices->mk_not(a)
#define MK_EQ(a,b)      yices->mk_eq(a,b)
#define MK_XOR(a,b)     yices->mk_xor(a,b)
#define MK_LT(a,b)      yices->mk_lt(a,b)
#define MK_LE(a,b)      yices->mk_le(a,b)
#define MK_TRUE()       yices->mk_true()
#define MK_FALSE()      yices->mk_false()

// a -> b  equals (!a + b)
#define MK_IMPLY(a,b)   MK_OR(MK_NOT(a),b)


string PolyGraphSMT_NodeName(int ev_id)
{
  static char res[32];
  sprintf(res, "n%d", ev_id);
  string str(res);
  return str;
}

string PolyGraphSMT_GuardName(int ev_id)
{
  static char res[32];
  sprintf(res, "g%d", ev_id);
  string str(res);
  return str;
}

string PolyGraphSMT_CoupledRName(int ev_id)
{
  static char res[32];
  sprintf(res, "cr%d", ev_id);
  string str(res);
  return str;
}

string PolyGraphSMT_CoupledAName(int ev_id)
{
  static char res[32];
  sprintf(res, "ca%d", ev_id);
  string str(res);
  return str;
}


void PolyGraphSMT::addEdge(int src_ev, int tgt_ev, bool retractable)
{
  // add edge (src ==> tgt)
  bool tgt_is_coupledR = false;
  addEdge_internal(src_ev, tgt_ev, tgt_is_coupledR, retractable);
}

void PolyGraphSMT::addEdgeConditional(int src_ev, int tgt_ev, bool retractable)
{
  // add conditional edge:  coupledR(tgt)  ->  g(src) && (src ==> tgt)
  bool tgt_is_coupledR = true;
  addEdge_internal(src_ev, tgt_ev, tgt_is_coupledR, retractable);
}

void PolyGraphSMT::addEdge_internal(int src_ev, int tgt_ev, bool tgt_is_coupledR, bool retractable)
{
  pair<int,int> idx(src_ev,tgt_ev);
  map<pair<int,int>, assertion_id>::iterator it;
  it = map_edge.find(idx);
  if (it == map_edge.end()) {
    YicesDP::expr src = MK_INT_VAR(PolyGraphSMT_NodeName(src_ev));
    YicesDP::expr tgt = MK_INT_VAR(PolyGraphSMT_NodeName(tgt_ev));
    YicesDP::expr e = MK_LT(src,tgt);

    if (tgt_is_coupledR) {
      // coupledR(tgt) -> g(src) && (src ==> tgt)
      YicesDP::expr cr = MK_BOOL_VAR(PolyGraphSMT_CoupledRName(tgt_ev));
      YicesDP::expr g  = MK_BOOL_VAR(PolyGraphSMT_GuardName(src_ev));
      e = MK_IMPLY(cr, MK_AND(g,e) );
    }

    if (retractable == true) {
      assertion_id id = yices->assert_retract_dp(e);
      map_edge[idx] = id;
    }
    else {
      yices->assertdp(e);
    }
  }
  else {
    assert( 0 && "PolyGraphSMT::addEdge() alread exists!\n" );
  }
}

void PolyGraphSMT::removeEdge(int src_ev, int tgt_ev)
{
  pair<int,int> idx(src_ev,tgt_ev);
  map<pair<int,int>, assertion_id>::iterator it;
  it = map_edge.find(idx);
  if (it != map_edge.end()) {
    assertion_id id = it->second;
    map_edge.erase(it);
    yices->retract( id );
  }
  else {
    assert( 0 && "PolyGraphSMT::removeEdge() does not exist!\n" );
  }
}

void PolyGraphSMT::addReachableCond(int ev, bool retractable)
{
  int idx = ev;
  map<int, assertion_id>::iterator it;
  it = map_condition.find(idx);
  if (it == map_condition.end()) {
    YicesDP::expr g = MK_BOOL_VAR(PolyGraphSMT_GuardName(ev));
    if (retractable == true) {
      assertion_id id = yices->assert_retract_dp(g);
      map_condition[idx] = id;
    }
    else {
      yices->assertdp(g);
    }
  }
  else {
    assert( 0 && "PolyGraphSMT::addReachableCond() alread exists!\n" );
  }
}


void PolyGraphSMT::removeReachableCond(int ev)
{
  int idx = ev;
  map<int, assertion_id>::iterator it;
  it = map_condition.find(idx);
  if (it != map_condition.end()) {
    assertion_id id = it->second;
    map_condition.erase(it);
    yices->retract( id );
  }
  else {
    assert( 0 && "PolyGraphSMT::removerReachableCond() does not exist!\n" );
  }
}

  


void PolyGraphSMT::addGuard(int src_ev, int tgt_ev, bool retractable)
{
  bool src_is_a_R = false;
  bool src2_available = false;
  addGuard_internal(src_ev, 0, tgt_ev, src_is_a_R, src2_available, retractable);
}

void PolyGraphSMT::addGuardRead(int src_ev, int tgt_ev, bool retractable)
{
  bool src_is_a_R = true;
  bool src2_available = false;
  addGuard_internal(src_ev, 0, tgt_ev, src_is_a_R, src2_available, retractable);
}

void PolyGraphSMT::addGuardJoin(int src_ev, int src2_ev, int tgt_ev, bool retractable)
{
  bool src_is_a_R = false;
  bool src2_available = true;
  addGuard_internal(src_ev, src2_ev, tgt_ev, src_is_a_R, src2_available, retractable);
}

void PolyGraphSMT::addGuard_internal(int src_ev, int src2_ev, int tgt_ev, bool src_is_a_R, bool src2_available, bool retractable)
{
  pair<int,int> idx(src_ev,tgt_ev);
  map<pair<int,int>, assertion_id>::iterator it;
  it = map_guard.find(idx);
  if (it == map_guard.end()) {
    YicesDP::expr src = MK_BOOL_VAR(PolyGraphSMT_GuardName(src_ev));
    YicesDP::expr tgt = MK_BOOL_VAR(PolyGraphSMT_GuardName(tgt_ev));

    YicesDP::expr RHS = src;
    if (src2_available) {
      YicesDP::expr src2 = MK_BOOL_VAR(PolyGraphSMT_GuardName(src2_ev));
      RHS = MK_AND(RHS,src2);
    }
    if (src_is_a_R) {
      YicesDP::expr coupledR = MK_BOOL_VAR(PolyGraphSMT_CoupledRName(src_ev));
      RHS = MK_AND(RHS,coupledR);
    }

    YicesDP::expr g = MK_EQ(tgt, RHS);

    if (retractable == true) {
      assertion_id id = yices->assert_retract_dp(g);
      map_guard[idx] = id;
    }
    else {
      yices->assertdp(g);
    }
  }
  else {
    assert( 0 && "PolyGraphSMT::addGuard() alread exists!\n" );
  }
}

// g(tgt) = g(src) && coupleA(src)
void PolyGraphSMT::addGuardAcq(int src_ev, int tgt_ev, bool retractable)
{
  pair<int,int> idx(src_ev,tgt_ev);
  map<pair<int,int>, assertion_id>::iterator it;
  it = map_guard.find(idx);
  if (it == map_guard.end()) {
    YicesDP::expr g_src = MK_BOOL_VAR(PolyGraphSMT_GuardName(src_ev));
    YicesDP::expr g_tgt = MK_BOOL_VAR(PolyGraphSMT_GuardName(tgt_ev));
    YicesDP::expr ca_src = MK_BOOL_VAR(PolyGraphSMT_CoupledAName(src_ev));
    YicesDP::expr res = MK_EQ( g_tgt, MK_AND( g_src, ca_src ) );
    if (retractable == true) {
      assertion_id id = yices->assert_retract_dp(res);
      map_guard[idx] = id;
    }
    else {
      yices->assertdp(res);
    }
  }
  else {
    assert( 0 && "PolyGraphSMT::addGuardAcq() alread exists!\n" );
  }
}

void PolyGraphSMT::removeGuard(int src_ev, int tgt_ev)
{
  pair<int,int> idx(src_ev,tgt_ev);
  map<pair<int,int>, assertion_id>::iterator it;
  it = map_guard.find(idx);
  if (it != map_guard.end()) {
    assertion_id id = it->second;
    map_guard.erase(it);
    yices->retract( id );
  }
  else {
    assert( 0 && "PolyGraphSMT::removeGuard() does not exist!\n" );
  }
}

void PolyGraphSMT::addPolyEdge(int es, int et, int os, int ot, bool retractable)
{
  // Either-OR (es => et, os => ot)
  bool use_coupledR = false;
  addPolyEdgeConditional(es, et, os, ot, 0, use_coupledR, retractable);
}

void PolyGraphSMT::addPolyEdgeConditional(int either_s, int either_t, int or_s, int or_t,
                                          int coupledR, bool use_coupledR, bool retractable)
{
  pair<int,int> either_idx(either_s, either_t);
  pair<int,int> or_idx(or_s, or_t);
  pair<pair<int,int>,pair<int,int> > idx(either_idx,or_idx);

  map<pair<pair<int,int>,pair<int,int> >, assertion_id>::iterator it;
  it = map_poly_edge.find(idx);

  if (it == map_poly_edge.end()) {
  
    YicesDP::expr either_src = MK_INT_VAR(PolyGraphSMT_NodeName(either_s));
    YicesDP::expr either_tgt = MK_INT_VAR(PolyGraphSMT_NodeName(either_t));
    YicesDP::expr either_e = MK_LT(either_src,either_tgt);
    YicesDP::expr or_src = MK_INT_VAR(PolyGraphSMT_NodeName(or_s));
    YicesDP::expr or_tgt = MK_INT_VAR(PolyGraphSMT_NodeName(or_t));
    YicesDP::expr or_e = MK_LT(or_src,or_tgt);
    YicesDP::expr exor = MK_XOR(either_e, or_e);
    
    if (use_coupledR) {
      YicesDP::expr cond = MK_BOOL_VAR(PolyGraphSMT_CoupledRName(coupledR));
      exor = MK_IMPLY(cond, exor);
    }

    if (retractable == true) {
      assertion_id id = yices->assert_retract_dp(exor);
      map_poly_edge[idx] = id;
    }
    else {
      yices->assertdp(exor);
    }

  }
  else {
    assert( 0 && "PolyGraphSMT::addPolyEdge() already exists!\n" );
  }
}

/*
// g(either_s) -> Either-Or( either_s < either_t, g(or_s) && or_s < or_t )
void PolyGraphSMT::addPolyEdge_AcqRel(int either_s, int either_t, int or_s, int or_t, 
                                      bool retractable)
{
  pair<int,int> either_idx(either_s, either_t);
  pair<int,int> or_idx(or_s, or_t);
  pair<pair<int,int>,pair<int,int> > idx(either_idx,or_idx);

  map<pair<pair<int,int>,pair<int,int> >, assertion_id>::iterator it;
  it = map_poly_edge.find(idx);

  if (it == map_poly_edge.end()) {
  
    YicesDP::expr either_src = MK_INT_VAR(PolyGraphSMT_NodeName(either_s));
    YicesDP::expr either_tgt = MK_INT_VAR(PolyGraphSMT_NodeName(either_t));
    YicesDP::expr either_e = MK_LT(either_src,either_tgt);
    YicesDP::expr or_src = MK_INT_VAR(PolyGraphSMT_NodeName(or_s));
    YicesDP::expr or_tgt = MK_INT_VAR(PolyGraphSMT_NodeName(or_t));
    YicesDP::expr or_e = MK_LT(or_src,or_tgt);
    YicesDP::expr g_or_src = MK_BOOL_VAR(PolyGraphSMT_GuardName(or_s));
    YicesDP::expr exor = MK_XOR(either_e, MK_AND(g_or_src,or_e));
    YicesDP::expr g_either_src = MK_BOOL_VAR(PolyGraphSMT_GuardName(either_s));
    YicesDP::expr res = MK_IMPLY(g_either_src, exor);

    if (retractable == true) {
      assertion_id id = yices->assert_retract_dp(res);
      map_poly_edge[idx] = id;
    }
    else {
      yices->assertdp(res);
    }

  }
  else {
    assert( 0 && "PolyGraphSMT::addPolyEdge() already exists!\n" );
  }
}
*/

 // add conditional edge
 //   coupledA(acq1) -> Either-Or( acq1 < acq2,  g(rel2) & (rel2 < acq1)
 //   coupledA(acq2) -> Either-Or( acq2 < acq1,  g(rel1) & (rel1 < acq2)
void PolyGraphSMT::addPolyEdge_AcqRel(int acq1, int rel1, int acq2, int rel2, bool retractable)
{
  pair<int,int> pair1(acq1,rel1);
  pair<int,int> pair2(acq2,rel2);
  pair<pair<int,int>,pair<int,int> > idx(pair1,pair2);

  map<pair<pair<int,int>,pair<int,int> >, assertion_id>::iterator it;
  it = map_poly_edge.find(idx);

  if (it == map_poly_edge.end()) {
  
    YicesDP::expr ca_acq1 = MK_BOOL_VAR(PolyGraphSMT_CoupledAName(acq1));
    YicesDP::expr ca_acq2 = MK_BOOL_VAR(PolyGraphSMT_CoupledAName(acq2));
    YicesDP::expr g_rel1 = MK_BOOL_VAR(PolyGraphSMT_GuardName(rel1));
    YicesDP::expr g_rel2 = MK_BOOL_VAR(PolyGraphSMT_GuardName(rel2));
    YicesDP::expr n_acq1 = MK_INT_VAR(PolyGraphSMT_NodeName(acq1));
    YicesDP::expr n_acq2 = MK_INT_VAR(PolyGraphSMT_NodeName(acq2));
    YicesDP::expr n_rel1 = MK_INT_VAR(PolyGraphSMT_NodeName(rel1));
    YicesDP::expr n_rel2 = MK_INT_VAR(PolyGraphSMT_NodeName(rel2));

    YicesDP::expr exor1 = MK_XOR( MK_LT(n_acq1,n_acq2), MK_AND(g_rel2, MK_LT(n_rel2,n_acq1)));
    YicesDP::expr exor2 = MK_XOR( MK_LT(n_acq2,n_acq1), MK_AND(g_rel1, MK_LT(n_rel1,n_acq2)));
    
    YicesDP::expr res1 =  MK_IMPLY( ca_acq1, exor1 );
    YicesDP::expr res2 =  MK_IMPLY( ca_acq2, exor2 );
    YicesDP::expr res = MK_AND(res1, res2);

    if (retractable == true) {
      assertion_id id = yices->assert_retract_dp(res);
      map_poly_edge[idx] = id;
    }
    else {
      yices->assertdp(res);
    }

  }
  else {
    assert( 0 && "PolyGraphSMT::addPolyEdge() already exists!\n" );
  }
}

void PolyGraphSMT::removePolyEdge(int either_s, int either_t, int or_s, int or_t)
{
  pair<int,int> either_idx(either_s, either_t);
  pair<int,int> or_idx(or_s, or_t);
  pair<pair<int,int>,pair<int,int> > idx(either_idx,or_idx);

  map<pair<pair<int,int>,pair<int,int> >, assertion_id>::iterator it;
  it = map_poly_edge.find(idx);

  if (it != map_poly_edge.end()) {
    assertion_id id = it->second;
    map_poly_edge.erase(it);
    yices->retract( id );
  }
  else {
    assert( 0 && "PolyGraphSMT::removePolyEdge() does not exist!\n" );
  }
}

bool PolyGraphSMT::check()
{
  bool invalid = yices->get_sat_result();
  return invalid;
}
