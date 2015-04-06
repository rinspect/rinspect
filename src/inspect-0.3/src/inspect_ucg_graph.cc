#include "inspect_ucg_graph.hh"
#include "yices_path_computer_singleton.hh"

#define MK_NUM(n)       yices->mk_num_int(n)
#define MK_VAR(n,t)     yices->mk_var(n,t)
#define MK_INT_VAR(n)   yices->mk_var(n,YicesDP::INTty)
#define MK_BOOL_VAR(n)  yices->mk_var(n,YicesDP::BOOLty)
#define MK_OR(a,b)      yices->mk_or(a,b)
#define MK_XOR(a,b)     yices->mk_xor(a,b)
#define MK_AND(a,b)     yices->mk_and(a,b)
#define MK_NOT(a)       yices->mk_not(a)
#define MK_EQ(a,b)      yices->mk_eq(a,b)
#define MK_LT(a,b)      yices->mk_lt(a,b)
#define MK_LE(a,b)      yices->mk_le(a,b)
#define MK_TRUE()       yices->mk_true()
#define MK_FALSE()      yices->mk_false()
static bool val_distinct = true; //whether all the values should be distinct

string Poly_NodeName(int ev_id) {
	static char res[32];
	sprintf(res, "n%d", ev_id);
	string str(res);
	return str;
}

YicesDP::expr PolyGraph::value_not_the_same(map<int, int> all_int) {
	map<int, int>::iterator it;
	map<int, int>::iterator it2;

	YicesDP::expr all = NULL;
	for (it = all_int.begin(); it != all_int.end(); it++) {
		YicesDP::expr src = MK_INT_VAR(Poly_NodeName(it->first));
		for (it2 = it; it2 != all_int.end(); it2++) {
			if (it2->first == it->first) {
				continue;
			}
			YicesDP::expr tgt = MK_INT_VAR(Poly_NodeName(it2->first));
			YicesDP::expr e = MK_NOT(MK_EQ(src,tgt));

			//cout<<it->first<<"!="<<it2->second<<endl;

			if (all != NULL && e != NULL) {
				all = MK_AND(all,e);
			} else {
				all = e;
			}
		}

	}
	return all;
}

//not(expr 1  and  expr 2 and  expr 3....)
YicesDP::expr PolyGraph::not_multiAnd(vector<pair<int, int> > edges) {
	if (edges.size() < 1)
		return NULL;
	vector<pair<int, int> >::iterator it;
	map<int, int> all_value;

	YicesDP::expr all = NULL;
	for (it = edges.begin(); it != edges.end(); it++) {
		//cout << it->first << "  ...   " << it->second << endl;

		all_value[it->first] = it->first;
		all_value[it->second] = it->second;

		YicesDP::expr src = MK_INT_VAR(Poly_NodeName(it->first));
		//cout <<it->first<<":"<<Poly_NodeName(it->first)<< endl;
		YicesDP::expr tgt = MK_INT_VAR(Poly_NodeName(it->second));
		//cout <<it->second<<":"<<Poly_NodeName(it->second)<< endl;
		YicesDP::expr e = MK_LT(src,tgt);
		if (all != NULL && e != NULL) {
			all = MK_AND(all,e);
		} else {
			all = e;
		}

	}
	all = MK_NOT(all);
	all = MK_AND(all,value_not_the_same(all_value));
	return all;
}

void PolyGraph::block_trace(vector<pair<int, int> > edges, bool retractable) {
	if (edges.size() < 1)
		return;

	YicesDP::expr all = not_multiAnd(edges);

	yices->assertdp(all);
}

void PolyGraph::addEdge(int src_ev, int tgt_ev, bool retractable) {
	pair<int, int> idx(src_ev, tgt_ev);
	map<pair<int, int>, assertion_id>::iterator it;
	it = map_edge.find(idx);
	if (it == map_edge.end()) {

		YicesDP::expr src = MK_INT_VAR(Poly_NodeName(src_ev));
		YicesDP::expr tgt = MK_INT_VAR(Poly_NodeName(tgt_ev));
		YicesDP::expr e = MK_LT(src,tgt);
		if (retractable == true) {
			assertion_id id = yices->assert_retract_dp(e);
			map_edge[idx] = id;
		} else {
			yices->assertdp(e);
		}
	} else {
		assert( 0 && "PolyGraph::addEdge() alread exists!\n");
	}
}

void PolyGraph::removeEdge(int src_ev, int tgt_ev) {
	pair<int, int> idx(src_ev, tgt_ev);
	map<pair<int, int>, assertion_id>::iterator it;
	it = map_edge.find(idx);
	if (it != map_edge.end()) {
		assertion_id id = it->second;
		map_edge.erase(it);
		yices->retract(id);
	} else {
		assert( 0 && "PolyGraph::removeEdge() does not exist!\n");
	}
}

void PolyGraph::addPolyEdge(int either_s, int either_t, int or_s, int or_t,
		bool retractable) {
	pair<int, int> either_idx(either_s, either_t);
	pair<int, int> or_idx(or_s, or_t);
	pair<pair<int, int>, pair<int, int> > idx(either_idx, or_idx);

	map<pair<pair<int, int>, pair<int, int> >, assertion_id>::iterator it;
	it = map_poly_edge.find(idx);

	if (it == map_poly_edge.end()) {

		YicesDP::expr either_src = MK_INT_VAR(Poly_NodeName(either_s));
		YicesDP::expr either_tgt = MK_INT_VAR(Poly_NodeName(either_t));
		YicesDP::expr either_e = MK_LT(either_src,either_tgt);
		YicesDP::expr or_src = MK_INT_VAR(Poly_NodeName(or_s));
		YicesDP::expr or_tgt = MK_INT_VAR(Poly_NodeName(or_t));
		YicesDP::expr or_e = MK_LT(or_src,or_tgt);
		YicesDP::expr either_xor = MK_XOR(either_e, or_e);

		if (retractable == true) {
			assertion_id id = yices->assert_retract_dp(either_xor);
			map_poly_edge[idx] = id;
		} else {
			yices->assertdp(either_xor);
		}

	} else {
		assert( 0 && "PolyGraph::addPolyEdge() already exists!\n");
	}
}

void PolyGraph::removePolyEdge(int either_s, int either_t, int or_s, int or_t) {
	pair<int, int> either_idx(either_s, either_t);
	pair<int, int> or_idx(or_s, or_t);
	pair<pair<int, int>, pair<int, int> > idx(either_idx, or_idx);

	map<pair<pair<int, int>, pair<int, int> >, assertion_id>::iterator it;
	it = map_poly_edge.find(idx);

	if (it != map_poly_edge.end()) {
		assertion_id id = it->second;
		map_poly_edge.erase(it);
		yices->retract(id);
	} else {
		assert( 0 && "PolyGraph::removePolyEdge() does not exist!\n");
	}
}

bool PolyGraph::check() {
	make_distinct_vals();

	bool res = (yices->check() == YicesDP::SAT_);

	YICES_DBG( cout << __FUNCTION__ << "() = " << res << endl);
	YICES_DBG( if (res) yices->show_sat());

	return res;
}

bool PolyGraph::check_and_getValue() {
	make_distinct_vals();

	bool res = (yices->check() == YicesDP::SAT_);
	if (res==false)
	{
		return res;
	}

	YICES_DBG( cout << __FUNCTION__ << "() = " << res << endl);
	//YICES_DBG( if (res) yices->show_sat());

	map<int, InspectEvent>::iterator it;
	for (it = yices_path_computer_singleton::getInstance()->event_map.begin();
			it != yices_path_computer_singleton::getInstance()->event_map.end();
			it++) {
		string name = yices_path_computer_singleton::getInstance()->get_n_name(
				it->first);
		int value = yices->show_val(name);

		//cout << name << "  "<<value<<endl;
		yices_path_computer_singleton::getInstance()->value_map[value] =
				it->first;
	}
	map<int, int>::iterator it2;
	for (it2 = yices_path_computer_singleton::getInstance()->value_map.begin();
			it2 != yices_path_computer_singleton::getInstance()->value_map.end();
			it2++) {
		//cout<< it2->first<<" :::: "<< it2->second<<endl;
	}

	return res;
}

void PolyGraph::make_distinct_vals() {

}

void PolyGraph::test() {
//  check();  //sat
//
//  addEdge(1,2,false);
//  check();  //sat
//
//  addEdge(2,3,false);
//  check();  //sat
//
//  addEdge(3,1,true);
//  check();  //unsat
//
//  removeEdge(3,1);
//  check();  //sat

	addEdge(11, 22, false);

	addEdge(33, 44, false);

	check();

	vector<pair<int, int> > edges;

	edges.push_back(pair<int, int>(11, 22));
	edges.push_back(pair<int, int>(22, 33));
	edges.push_back(pair<int, int>(33, 44));
	block_trace(edges, false);
	check();

	edges.clear();
	edges.push_back(pair<int, int>(33, 44));
	edges.push_back(pair<int, int>(44, 11));
	edges.push_back(pair<int, int>(11, 22));
	block_trace(edges, false);
	check();

	edges.clear();
	edges.push_back(pair<int, int>(33, 11));
	edges.push_back(pair<int, int>(11, 44));
	edges.push_back(pair<int, int>(44, 22));
	block_trace(edges, false);
	check();

	edges.clear();
	edges.push_back(pair<int, int>(33, 11));
	edges.push_back(pair<int, int>(11, 22));
	edges.push_back(pair<int, int>(22, 44));
	block_trace(edges, false);
	check();

	edges.clear();
	edges.push_back(pair<int, int>(11, 33));
	edges.push_back(pair<int, int>(33, 22));
	edges.push_back(pair<int, int>(22, 44));
	block_trace(edges, false);
	check();

	edges.clear();
	edges.push_back(pair<int, int>(11, 33));
	edges.push_back(pair<int, int>(33, 44));
	edges.push_back(pair<int, int>(44, 22));
	block_trace(edges, false);
	check();

}
