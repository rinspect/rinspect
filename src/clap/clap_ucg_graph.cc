#include "clap_ucg_graph.hh"

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

string Poly_NodeName(int ev_id)
{
  static char res[32];
  sprintf(res, "n%d", ev_id);
  string str(res);
  return str;
}

void PolyGraph::addEdge(int src_ev, int tgt_ev, bool retractable)
{
  pair<int,int> idx(src_ev,tgt_ev);
  map<pair<int,int>, assertion_id>::iterator it;
  it = map_edge.find(idx);
  if (it == map_edge.end()) {
    YicesDP::expr src = MK_INT_VAR(Poly_NodeName(src_ev));
    YicesDP::expr tgt = MK_INT_VAR(Poly_NodeName(tgt_ev));
    YicesDP::expr e = MK_LT(src,tgt);
    if (retractable == true) {
      assertion_id id = yices->assert_retract_dp(e);
      map_edge[idx] = id;
    }
    else {
      yices->assertdp(e);
    }
  }
  else {
    assert( 0 && "PolyGraph::addEdge() alread exists!\n" );
  }
}

void PolyGraph::removeEdge(int src_ev, int tgt_ev)
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
    assert( 0 && "PolyGraph::removeEdge() does not exist!\n" );
  }
}

void PolyGraph::addPolyEdge(int either_s, int either_t, int or_s, int or_t,
                            bool retractable)
{
  pair<int,int> either_idx(either_s, either_t);
  pair<int,int> or_idx(or_s, or_t);
  pair<pair<int,int>,pair<int,int> > idx(either_idx,or_idx);

  map<pair<pair<int,int>,pair<int,int> >, assertion_id>::iterator it;
  it = map_poly_edge.find(idx);

  if (it == map_poly_edge.end()) {
  
    YicesDP::expr either_src = MK_INT_VAR(Poly_NodeName(either_s));
    YicesDP::expr either_tgt = MK_INT_VAR(Poly_NodeName(either_t));
    YicesDP::expr either_e = MK_LT(either_src,either_tgt);
    YicesDP::expr or_src = MK_INT_VAR(Poly_NodeName(or_s));
    YicesDP::expr or_tgt = MK_INT_VAR(Poly_NodeName(or_t));
    YicesDP::expr or_e = MK_LT(or_src,or_tgt);
    YicesDP::expr exor = MK_XOR(either_e, or_e);

    if (retractable == true) {
      assertion_id id = yices->assert_retract_dp(exor);
      map_poly_edge[idx] = id;
    }
    else {
      yices->assertdp(exor);
    }

  }
  else {
    assert( 0 && "PolyGraph::addPolyEdge() already exists!\n" );
  }
}

void PolyGraph::removePolyEdge(int either_s, int either_t, int or_s, int or_t)
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
    assert( 0 && "PolyGraph::removePolyEdge() does not exist!\n" );
  }
}

bool PolyGraph::check()
{
  bool invalid = yices->get_sat_result();
  return invalid;
}
