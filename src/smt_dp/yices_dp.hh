#ifndef YICES_DP_HH
#define YICES_DP_HH

#include"yices_c.h"
#include "yicesl_c.h"

#include<set>
#include<vector>
#include<list>
#include<map>
#include<cstdio>
#include<iostream>
#include<cassert>
#include<string.h>
#include<sstream>


#define YICES_DBG(s)  s


using namespace std;

typedef std::string stdstring;

#define CHK(s) assert(s)

#define const_foreach( i, c )\
  typedef __typeof__( c ) c##_CONTAINERTYPE;\
  for( c##_CONTAINERTYPE::const_iterator i = c.begin(); i != c.end(); ++i )
  


class YicesDP {
public:
  typedef yices_expr expr ;
  typedef yices_context context ;
  typedef yices_type DP_type;

  enum status_t {
    SAT_,
    UNSAT_,
    UNKNOWN_
  };

  enum Typ { BOOLty, BVty, INTty, REALty };

  enum OP { 
    TRUEop, FALSEop, 
    NOTop, MINUSop, ADDRop, DEREFop, 
    GTop, LTop, GTEop, LTEop, EQop, NEQop, ANDop, ORop, IMPLIESop, XORop, IORop, MODop,
    BVANDop, BVORop, BVXORop, BVRSop , BVLSop,
    ADDop, SUBop, MULTop, DIVop, 
    ITEop, ITEPop, 
    UNKop 
  }; 

  class status {
  public:
            
    status() : _status(UNKNOWN_) {}

    status(const status_t status) : _status(status) {}
      
    status(const lbool lb)
    {
      switch(lb)
        {
        case l_false  : _status = UNSAT_; break; 
        case l_true   : _status = SAT_; break; 
        case l_undef  : _status = UNKNOWN_; break; 
        default       : assert(false);
        }
    }
      
    const char * str() const
    {
      switch(_status)
        {
        case SAT_     : return "SAT";
        case UNSAT_   : return "UNSAT";
        case UNKNOWN_ : return "UNKNOWN";
        }
        
      assert(false);
        
    }
      
    ostream& print(ostream& os) const { os << str(); return os; };

    bool operator==(const status& other) const { return _status == other._status; }
    bool operator!=(const status& other) const { return _status != other._status; }

  private:
      
    status_t _status;
  };

  static const status sat; 
  static const status unsat; 
  static const status unknown; 

protected:
  context dp_ct;
  static Typ DEFAULT_VAR_TYPE; 
  static const unsigned int DEFAULT_BV_SIZE; 
  int tmpcnt;
  set<yices_var_decl> var_decls;
  map<assertion_id, expr> retract_map;

  yices_var_decl get_var_decl (const stdstring &name, DP_type dpty) {
    yices_var_decl yvd =yices_get_var_decl_from_name(dp_ct,name.c_str());
    if ( !yvd ) {
      yvd = yices_mk_var_decl (dp_ct, name.c_str(), dpty);
      var_decls.insert(yvd);
    }
    CHK (yvd);
    return yvd;
  }

  bool is_mode_bv () { return DEFAULT_VAR_TYPE == BVty; }

  stdstring get_new_tmp_name () { 
    tmpcnt++; 
    char res[32];
    sprintf(res, "__yices_dp_tmp__%d", tmpcnt);
    return res;
  }


public:

  YicesDP() {
    dp_ct = yices_mk_context();
    init();
  }
  ~YicesDP() { yices_del_context(dp_ct); }

  yices_context get_context() { return dp_ct; }

  void init() ;
  static void set_default_var_type (Typ typ) { DEFAULT_VAR_TYPE = typ; }
  static Typ get_default_var_type () { return DEFAULT_VAR_TYPE; }

  void set_evidence (bool b) ; //don't use
  static void print(const expr& e) { yices_pp_expr(e); }
  void dump () { yices_dump_context(dp_ct); }
  void set_log_file_name (const stdstring &name) { yices_enable_log_file (name.c_str()); }

  // -------- Build Types ----------------
  DP_type mk_bool_type() const { return yices_mk_type(dp_ct, "bool"); }
  DP_type mk_int_type() const { return yices_mk_type(dp_ct, "int"); }
  DP_type mk_real_type() const { return yices_mk_type(dp_ct, "real"); }
  DP_type mk_bv_type (unsigned int size = DEFAULT_BV_SIZE) const { return yices_mk_bitvector_type (dp_ct, size); }

  inline DP_type mk_nary_ty_function_type (Typ ty, unsigned int arity) {
    DP_type yty;
    if ( ty == INTty ) {
      yty = mk_int_type();
    }
    else if ( ty == BVty ) {
      yty = mk_bv_type();
    }
    else if ( ty == BOOLty ) {
      yty = mk_bool_type();
    }
    else if  (ty == REALty) {
      yty = mk_real_type();
    }
    else CHK (0);
    assert(arity < 128);
    DP_type domain[128];
    for (unsigned i=0; i<arity; i++) domain[i] = yty;
    return yices_mk_function_type (dp_ct, domain, arity, yty);
  }

  expr mk_function (const stdstring &s, Typ ty, int arity = 2) {
    DP_type fn_type = mk_nary_ty_function_type (ty, arity);
    yices_var_decl yvd  = get_var_decl(s, fn_type);
    return yices_mk_var_from_decl(dp_ct, yvd);
  }

  inline DP_type mk_func_type_decl (Typ ty, Typ ty1, unsigned int siz){
    DP_type ytyp, ytyr;
    // for parameters;
    if ( ty == INTty ) {
      ytyp = mk_int_type();
    }
    else if ( ty == BVty ) {
      ytyp = mk_bv_type();
    }
    else if ( ty == BOOLty ) {
      ytyp = mk_bool_type();
    }
    else if  (ty == REALty) {
      ytyp = mk_real_type();
    }
    else CHK (0);

    // for return range;
    if ( ty1 == INTty ) {
      ytyr = mk_int_type();
    }
    else if ( ty1 == BVty ) {
      ytyr = mk_bv_type();
    }
    else if ( ty1 == BOOLty ) {
      ytyr = mk_bool_type();
    }
    else if  (ty1 == REALty) {
      ytyr = mk_real_type();
    }
    else CHK (0);
    DP_type domain[3];
    domain[0] = ytyp;
    //domain[1] = ytyr;
    return yices_mk_function_type (dp_ct, domain, siz, ytyr);
  }

  expr mk_func2 (const stdstring &s, Typ ty, Typ ty1, int arity = 1){
    DP_type fn_type = mk_func_type_decl(ty, ty1, arity);
    yices_var_decl yvd = get_var_decl(s, fn_type);
    return yices_mk_var_from_decl(dp_ct, yvd);
  }

  // ------ Build Symbols ----------------
  expr mk_mymul_op () { return mk_function ("mymul", DEFAULT_VAR_TYPE); }
  expr mk_mydiv_op () { return mk_function ("mydiv", DEFAULT_VAR_TYPE); }
  expr mk_mymod_op () { return mk_function ("mymod", DEFAULT_VAR_TYPE); }

  expr mk_my_bv_and () { return mk_function ("my_bv_and", DEFAULT_VAR_TYPE); }
  expr mk_my_bv_or () { return mk_function ("my_bv_or", DEFAULT_VAR_TYPE); }
  expr mk_my_bv_xor () { return mk_function ("my_bv_xor", DEFAULT_VAR_TYPE); }
  expr mk_my_bv_rs () { return mk_function ("my_bv_rs", DEFAULT_VAR_TYPE); }
  expr mk_my_bv_ls () { return mk_function ("my_bv_ls", DEFAULT_VAR_TYPE); }

  expr mk_true() { return yices_mk_true(dp_ct); }
  expr mk_false() { return yices_mk_false(dp_ct); }

  expr mk_num_from_string(const stdstring& s) { 
    return yices_mk_num_from_string( dp_ct, s.c_str() ); 
  }
  expr mk_num_real (long double d, int float_type) ;
  expr mk_num_int(int n) ;
  expr mk_num_bv(int n) ;

  expr mk_bool_var(const stdstring& name) { return yices_mk_bool_var_decl(dp_ct,name.c_str()); }
  expr mk_fresh_bool_var() { return yices_mk_fresh_bool_var(dp_ct); }

  expr mk_var(const stdstring& name, Typ ty) {
    DP_type dpty;
    if (ty == INTty) dpty = mk_int_type();
    else  if (ty == BOOLty) dpty = mk_bool_type();
    else if (ty == BVty) dpty = mk_bv_type ();
    else if (ty == REALty) dpty = mk_real_type ();
    else CHK (0);

    yices_var_decl yvd = get_var_decl(name, dpty);
    yices_expr var_expr = yices_mk_var_from_decl(dp_ct, yvd);
    return var_expr;
  }
  expr mk_var(const stdstring& name) { return mk_var(name, DEFAULT_VAR_TYPE); }

  expr mk_fresh_real_var () {	
    stdstring name = get_new_tmp_name ();
    return mk_var (name, REALty);
  }

  // ---- Build Expressions ---------------

  expr mk_app (expr f, expr a, expr b) ;
  expr mk_app (expr f, expr a[], int n);

  // -- Simple wrappers
  expr mk_not (expr a) 	;
  expr mk_le(expr a, expr b) ;
  expr mk_lt(expr a, expr b) ;
  expr mk_ge(expr a, expr b) ;
  expr mk_gt(expr a, expr b) ;
  expr mk_diseq(expr a, expr b) ;
  expr mk_eq(expr a, expr b) ;
  expr mk_ite( expr c, expr t, expr f) ;
  expr mk_implies (expr a, expr b) ;

  expr mk_sum(expr a[], unsigned int n) ; 
  expr mk_sum(expr a, expr b) ; 

  expr mk_sub(expr a[], unsigned int n) ; 
  expr mk_sub(expr a, expr b) ; 

  expr mk_minus(expr a) ;
    
  expr mk_and (expr a[], unsigned int n) ;
  expr mk_and(expr a, expr b) ; 

  expr mk_xor (expr a, expr b) ;

  expr mk_or (const vector<expr>& a) ;
  expr mk_or (expr a[], unsigned int n) ;


  expr mk_or(expr a, expr b) ; 

  expr mk_mul (expr a[], unsigned int n); 
  expr mk_mul(expr a, expr b) ; 

  void add_div_mod_constraints (expr a, expr b, expr &q, expr &r) ;
  expr mk_mod(expr a, expr b) ;
  expr mk_div(expr a, expr b) ;

  expr mk_bv_and(expr a, expr b) ;
  expr mk_bv_or(expr a, expr b)   ;
  expr mk_bv_xor(expr a, expr b) ;
  expr mk_bv_rs(expr a, expr b) ;
  expr mk_bv_rs(expr a, unsigned int n) ;
  expr mk_bv_ls(expr a, expr b) ;
  expr mk_bv_ls(expr a, unsigned int n) ;

  // -- mk_appl

  expr mk_appl (OP op, expr yargs[], int n) ;

  expr mk_appl (OP op, const vector<expr> &args);


  //Functions to add constraints to current context and check for SAT/UNSAT
  //Usage: assertdp and then check/get_sat_result
  void assertdp(yices_expr e) ;
  assertion_id assert_weighted(yices_expr e, long long w) ;
  status check() { return status(yices_check(dp_ct)); }

  //Returns Yices SAT/UNSAT/UNKNOWN result converted to Bool
  bool get_sat_result() ;
  bool check_max_sat (long long max_cost = -1) ;
  bool find_weighted_model() ;

  //Incremental SMT
  void push() { yices_push(dp_ct); }
  void pop() { yices_pop(dp_ct); }

  assertion_id assert_retract_dp(yices_expr e) ;
  void retract ( assertion_id id ) ;
  void get_retractable_false_ids (set<assertion_id> &ids) ;
  void get_unsat_core_ids ( const set<assertion_id> &rel_ids, set<assertion_id> &ids);
    
  // native yices functionality
  unsigned get_unsat_core_size();
  void get_unsat_core(set<assertion_id> &ids) ;

  //Locally inconsistent check - avoid using it.
  bool inconsistent() { 
    int res = yices_inconsistent(dp_ct);
    YICES_DBG( cout << "yices_inconsistent(dp_ct) = " << res << endl );
    return (res != 0); 
  }

  //Displaying Yices model or UNSAT result
  void show_sat () ;
  string bv_string(int int_array[], int size);



  //Functions for extracting models, once the formula is satisfiable
  int show_val(yices_model m, yices_var_decl yvd) ;
  int show_val(const stdstring &name) ;
  void get_model ( const pair<expr,expr> & p, pair<int,int> &val) ;
  void eval_and_print_in_model (expr e);
  void create_model ( map<stdstring,int> & model ) ;

};

ostream& operator<<(ostream& os, const YicesDP::status& status);

typedef YicesDP::expr YicesDP_expr;


#endif //YICES_DP_HH
