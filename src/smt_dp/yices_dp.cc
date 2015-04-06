#include"yices_dp.hh"

#include<map>
#include<cstdlib>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


YicesDP::Typ YicesDP::DEFAULT_VAR_TYPE = BVty;

const unsigned int YicesDP::DEFAULT_BV_SIZE = 32;

const YicesDP::status YicesDP::sat = YicesDP::status(YicesDP::SAT_);
const YicesDP::status YicesDP::unsat = YicesDP::status(YicesDP::UNSAT_);
const YicesDP::status YicesDP::unknown = YicesDP::status(YicesDP::UNKNOWN_);

ostream& operator<<(ostream& os, const YicesDP::status& status) 
{
  return status.print(os);
}

void YicesDP::init() 
{
  tmpcnt = -1;
  yices_enable_type_checker(1);
  yices_enable_log_file((char*) "yices_debug_log.log");
}

//only works with yicesl
void YicesDP::set_evidence(bool b) 
{
  yicesl_context ctx = yicesl_mk_context();
  stdstring s = b ? "true)" : "false)";
  s = "(set-evidence! " + s;
  cerr << "s is " << s << endl;
  yicesl_read(ctx, (char*) s.c_str());
  yicesl_del_context(ctx);
}

void show_lbool(lbool &lb) 
{
  switch (lb) {
  case l_true:
    cerr << "true\n";
    break;
  case l_false:
    cerr << "false\n";
    break;
  case l_undef:
    cerr << "undef\n";
    break;
  default:
    CHK(0);
  }
}

//float_type = 0 (float), 1 (double), 2 (long double)
YicesDP::expr YicesDP::mk_num_real(long double d, int float_type) 
{
  //CHK( !is_mode_bv());    
  char str[200];
  fprintf(stderr,
          "---- mk_num_real: d = %Lf, d = %0.50Lf, float_type = %d \n", d, d,
          float_type);
  stdstring format_str;
  int n;
  if (float_type == 0 || float_type == 1) {
    format_str = "%.5f";
    n = snprintf(str, 200, format_str.c_str(), (double) d);
  } else {
    format_str = "%.5Lf";
    n = snprintf(str, 200, format_str.c_str(), d);
  }
  CHK(n < 200);
  fprintf(stderr, "str is %s\n", str);
  //int n = snprintf(str,200,"%0.50L", d);
  char c = str[0];
  if (c == 'N' || c == 'I')
    CHK(0);
  //NA, NaN, Inf
  if (c == '+' && str[1] == 'I')
    CHK(0);
  //+Inf
  if (c == '-' && str[1] == 'I')
    CHK(0);
  //-Inf
  expr ret = yices_mk_num_from_string(dp_ct, str);
  CHK(ret);
  //print(ret);
  return ret;
}

YicesDP::expr YicesDP::mk_num_int(int n) 
{
  if (is_mode_bv())
    return yices_mk_bv_constant(dp_ct, DEFAULT_BV_SIZE, (unsigned long) n);
  //else mk_num_int(n);
  else
    return yices_mk_num(dp_ct, n);
}

YicesDP::expr YicesDP::mk_num_bv(int n){
  return yices_mk_bv_constant(dp_ct, DEFAULT_BV_SIZE, (unsigned long) n);
}

// ----- Build Types ----------

// ----- Build Symbols ----------

// ----- Build Expressions ----------

YicesDP_expr YicesDP::mk_app(expr f, expr a, expr b) 
{
  expr yargs[2];
  yargs[0] = a;
  yargs[1] = b;
  return yices_mk_app(dp_ct, f, yargs, 2);
}

YicesDP_expr YicesDP::mk_app(expr f, expr a[], int n) 
{
  return yices_mk_app(dp_ct, f, a, n);
}

YicesDP_expr YicesDP::mk_not(expr a) 
{
  return yices_mk_not(dp_ct, a);
}

YicesDP_expr YicesDP::mk_le(expr a, expr b) 
{
  if (is_mode_bv())
    return yices_mk_bv_sle(dp_ct, a, b);
  else
    return yices_mk_le(dp_ct, a, b);
}

YicesDP_expr YicesDP::mk_lt(expr a, expr b) 
{
  if (is_mode_bv())
    return yices_mk_bv_slt(dp_ct, a, b);
  else
    return yices_mk_lt(dp_ct, a, b);
}

YicesDP_expr YicesDP::mk_ge(expr a, expr b) 
{
  if (is_mode_bv())
    return yices_mk_bv_sge(dp_ct, a, b);
  else
    return yices_mk_ge(dp_ct, a, b);
}

YicesDP_expr YicesDP::mk_gt(expr a, expr b) 
{
  if (is_mode_bv())
    return yices_mk_bv_sgt(dp_ct, a, b);
  else
    return yices_mk_gt(dp_ct, a, b);
}

YicesDP_expr YicesDP::mk_diseq(expr a, expr b) 
{
  return yices_mk_diseq(dp_ct, a, b);
}

YicesDP_expr YicesDP::mk_eq(expr a, expr b) 
{
  return yices_mk_eq(dp_ct, a, b);
}

YicesDP_expr YicesDP::mk_ite(expr c, expr t, expr f) 
{
  return yices_mk_ite(dp_ct, c, t, f);
}

YicesDP_expr YicesDP::mk_implies(expr a, expr b) 
{
  return mk_or(mk_not(a), b);
}

YicesDP_expr YicesDP::mk_sum(expr a[], unsigned int n) 
{
  if (is_mode_bv()) {
    CHK(n == 2);
    return yices_mk_bv_add(dp_ct, a[0], a[1]);
  } else
    return yices_mk_sum(dp_ct, a, n);
}

YicesDP_expr YicesDP::mk_sum(expr a, expr b) 
{
  expr res[2];
  res[0] = a;
  res[1] = b;
  return mk_sum(res, 2);
}

YicesDP_expr YicesDP::mk_sub(expr a[], unsigned int n) 
{
  if (is_mode_bv()) {
    CHK(n == 2);
    return yices_mk_bv_sub(dp_ct, a[0], a[1]);
  } else
    return yices_mk_sub(dp_ct, a, n);
}

YicesDP_expr YicesDP::mk_sub(expr a, expr b) 
{
  expr res[2];
  res[0] = a;
  res[1] = b;
  return mk_sub(res, 2);
}

YicesDP_expr YicesDP::mk_minus(expr a) 
{
  if (is_mode_bv()) {
    return yices_mk_bv_minus(dp_ct, a);
  } else
    return mk_sub(mk_num_int(0), a);
}

YicesDP_expr YicesDP::mk_and(expr a[], unsigned int n) 
{
  return yices_mk_and(dp_ct, a, n);
}

YicesDP_expr YicesDP::mk_and(expr a, expr b) 
{
  expr res[2];
  res[0] = a;
  res[1] = b;
  return mk_and(res, 2);
}

YicesDP_expr YicesDP::mk_or(expr a[], unsigned int n) 
{
  return yices_mk_or(dp_ct, a, n);
}

YicesDP_expr YicesDP::mk_xor(expr a, expr b) 
{
  return mk_or(mk_and(a, mk_not(b)), mk_and(mk_not(a), b));
}

YicesDP_expr YicesDP::mk_or(const vector<expr>& a) 
{
  assert(!a.empty());
  expr * const array = new expr[a.size()];
  copy(a.begin(), a.end(), array);

  expr e = yices_mk_or(dp_ct, array, a.size());

  delete[] array;
  return e;
}

YicesDP_expr YicesDP::mk_or(expr a, expr b) 
{
  expr res[2];
  res[0] = a;
  res[1] = b;
  return mk_or(res, 2);
}

YicesDP_expr YicesDP::mk_mul(expr a[], unsigned int n) 
{
  if (is_mode_bv()) {
    CHK(n == 2);
    return yices_mk_bv_mul(dp_ct, a[0], a[1]);
  }
  return yices_mk_mul(dp_ct, a, n);
}

YicesDP_expr YicesDP::mk_mul(expr a, expr b) 
{
  expr res[2];
  res[0] = a;
  res[1] = b;
  return mk_mul(res, 2);
}

// a/b = q; a = q*b + r, 0<= r <= b

void YicesDP::add_div_mod_constraints(expr a, expr b, expr &q, expr &r) 
{
  q = mk_var(get_new_tmp_name());
  r = mk_var(get_new_tmp_name());
  expr res = mk_eq(a, mk_sum(mk_mul(q, b), r));
  res = mk_and(mk_ge(r, mk_num_int(0)), mk_le(r, b));
  assertdp(res);
}

YicesDP_expr YicesDP::mk_div(expr a, expr b) 
{
  if (is_mode_bv()) {
    expr q, r;
    add_div_mod_constraints(a, b, q, r);
    return q;
  } else
    return mk_app(mk_mydiv_op(), a, b);
}

YicesDP_expr YicesDP::mk_mod(expr a, expr b) 
{
  if (is_mode_bv()) {
    expr q, r;
    add_div_mod_constraints(a, b, q, r);
    return r;
  } else
    return mk_app(mk_mymod_op(), a, b);
}

YicesDP_expr YicesDP::mk_bv_and(expr a, expr b) 
{
  if (is_mode_bv()) {
    return yices_mk_bv_and(dp_ct, a, b);
  } else
    return mk_app(mk_my_bv_and(), a, b);
}

YicesDP_expr YicesDP::mk_bv_or(expr a, expr b) 
{
  if (is_mode_bv()) {
    return yices_mk_bv_or(dp_ct, a, b);
  } else
    return mk_app(mk_my_bv_or(), a, b);
}

YicesDP_expr YicesDP::mk_bv_xor(expr a, expr b) 
{
  if (is_mode_bv()) {
    return yices_mk_bv_xor(dp_ct, a, b);
  } else
    return mk_app(mk_my_bv_xor(), a, b);
}

YicesDP_expr YicesDP::mk_bv_rs(expr a, unsigned int n) 
{
  expr first_bit = yices_mk_bv_extract(dp_ct, DEFAULT_BV_SIZE - 1,
                                       DEFAULT_BV_SIZE - 1, a);
  expr cond = mk_eq(first_bit, yices_mk_bv_constant(dp_ct, 1, 1));

  expr ret = mk_ite(cond, yices_mk_bv_shift_right1(dp_ct, a, n),
                    yices_mk_bv_shift_right0(dp_ct, a, n));
  return ret;
}

YicesDP_expr YicesDP::mk_bv_rs(expr a, expr b) 
{
  if (is_mode_bv()) {
    //return yices_mk_bv_rs (dp_ct, a, b);
    unsigned int n = DEFAULT_BV_SIZE - 2;
    CHK(n>=0);
    expr res = mk_ite(mk_eq(b, mk_num_int(n)), mk_bv_rs(a, n),
                      mk_bv_rs(a, n + 1));
    n--;
    for (; n > 0; n--)
      res = mk_ite(mk_eq(b, mk_num_int(n)), mk_bv_rs(a, n), res);
    return res;
  } else
    return mk_app(mk_my_bv_rs(), a, b);
}

YicesDP_expr YicesDP::mk_bv_ls(expr a, unsigned int n) 
{
  return yices_mk_bv_shift_left0(dp_ct, a, n);
}

YicesDP_expr YicesDP::mk_bv_ls(expr a, expr b) 
{
  if (is_mode_bv()) {
    unsigned int n = DEFAULT_BV_SIZE - 2;
    CHK(n>=0);
    expr res = mk_ite(mk_eq(b, mk_num_int(n)), mk_bv_ls(a, n),
                      mk_bv_ls(a, n + 1));
    n--;
    for (; n > 0; n--)
      res = mk_ite(mk_eq(b, mk_num_int(n)), mk_bv_ls(a, n), res);
    return res;
  } else
    return mk_app(mk_my_bv_ls(), a, b);
}

// -- mk_appl
YicesDP_expr YicesDP::mk_appl(OP op, expr yargs[], int n) 
{
  if (n == 0) {
    switch (op) {
    case TRUEop:
      return mk_true();
    case FALSEop:
      return mk_false();
    default:
      CHK(0);
    }
  }

  switch (op) {
  case NOTop:
    CHK(n == 1);
    return mk_not(yargs[0]);
  case MINUSop: {
    CHK(n == 1);
    return mk_minus(yargs[0]);
  }

  case GTop:
    CHK( n == 2);
    return mk_gt(yargs[0], yargs[1]);
  case LTop:
    CHK( n == 2);
    return mk_lt(yargs[0], yargs[1]);
  case GTEop:
    CHK( n == 2);
    return mk_ge(yargs[0], yargs[1]);
  case LTEop:
    CHK( n == 2);
    return mk_le(yargs[0], yargs[1]);
  case EQop:
    CHK( n == 2);
    return mk_eq(yargs[0], yargs[1]);
  case NEQop:
    CHK( n == 2);
    return mk_diseq(yargs[0], yargs[1]);
  case ANDop:
    CHK(n == 2);
    return mk_and(yargs, n);
  case ORop:
    CHK(n == 2);
    return mk_or(yargs, n);
  case IMPLIESop:
    CHK(n == 2);
    return mk_implies(yargs[0], yargs[1]);
  case XORop:
    CHK(0);
    break;

  case ITEop:
    CHK(n == 3);
    return mk_ite(yargs[0], yargs[1], yargs[2]);

  case BVANDop:
    CHK(n == 2);
    return mk_bv_and(yargs[0], yargs[1]);
  case BVORop:
    CHK(n == 2);
    return mk_bv_or(yargs[0], yargs[1]);
  case BVXORop:
    CHK(n == 2);
    return mk_bv_xor(yargs[0], yargs[1]);
  case BVLSop:
    CHK(n == 2);
    return mk_bv_ls(yargs[0], yargs[1]);
  case BVRSop:
    CHK(n == 2);
    return mk_bv_rs(yargs[0], yargs[1]);

  case ADDop:
    CHK(n==2);
    return mk_sum(yargs, n);
  case SUBop:
    CHK(n==2);
    return mk_sub(yargs, n);
  case MULTop:
    CHK(n==2);
    return mk_mul(yargs, n);
  case DIVop:
    CHK(n==2);
    return mk_div(yargs[0], yargs[1]);
  case MODop:
    CHK(n==2);
    return mk_mod(yargs[0], yargs[1]);

  default:
    assert( 0 && " unknown op : \n");
  }
}

YicesDP_expr YicesDP::mk_appl(OP op, const vector<expr> &args) 
{
  int n = args.size();
  expr yargs[n];
  for (int i = 0; i < n; i++)
    yargs[i] = args[i];
  return mk_appl(op, yargs, n);
}

//------ Assert, Retract, MaxSMT ---
void YicesDP::assertdp(yices_expr e) 
{
  try {
    yices_assert(dp_ct, e);
  } catch (std::exception &ex) {
    fprintf(stderr, "typechecker exception during asserting expr\n");
    print(e);
    cerr << "\nException.what() = " << ex.what() << endl;
    exit(1);
  }
}

assertion_id YicesDP::assert_retract_dp(yices_expr e) 
{
  assertion_id id = yices_assert_retractable(dp_ct, e);
  retract_map[id] = e;
  return id;
}

assertion_id YicesDP::assert_weighted(yices_expr e, long long w) 
{
  assertion_id id = yices_assert_weighted(dp_ct, e, w);
  retract_map[id] = e;
  return id;
}

void YicesDP::retract(assertion_id id) 
{
  if (retract_map.find(id) == retract_map.end())
    return;
  retract_map.erase(id);
  yices_retract(dp_ct, id);
}

void YicesDP::get_retractable_false_ids(set<assertion_id> &ids) 
{
  yices_model m = yices_get_model(dp_ct);
  CHK(m);
  const_foreach(it, retract_map)
    {
      assertion_id id = it->first;
      int is_sat = yices_get_assertion_value(m, id);
      if (is_sat == 0)
        ids.insert(id);
    }
}

unsigned YicesDP::get_unsat_core_size() 
{
  return yices_get_unsat_core_size(dp_ct);
}

void YicesDP::get_unsat_core(set<assertion_id> &ids) 
{
  unsigned size, size2, i;
  assertion_id *buf;

  size = yices_get_unsat_core_size(dp_ct);
  if (size > 0) {
    buf = (assertion_id*) malloc(sizeof(assertion_id) * size);
    size2 = yices_get_unsat_core(dp_ct, buf);
    assert(size == size2);
    for (i = 0; i < size; i++) {
      ids.insert(buf[i]);
    }
    free(buf);
  }
}

//find the ids from the set of relevant ids that are in unsat core
//assumes that the relevant ids are the superset of unsat core ids
void YicesDP::get_unsat_core_ids(const set<assertion_id> &relevant_ids,
                                 set<assertion_id> &ids) 
{
  set<assertion_id> retractable_ids = relevant_ids;
  if (relevant_ids.empty()) {
    const_foreach(it, retract_map)
      {
        retractable_ids.insert(it->first);
      }
  }

  const_foreach(it, retractable_ids) {
    assertion_id id = *it;
    retract(id);
    bool ret = get_sat_result();
    ids.insert(id);
    if (ret)
      return;
  }
  //removing from retractable ids should lead to unsat
  CHK(0);
}

bool YicesDP::get_sat_result() 
{
  fprintf(stderr, "\nINVOKE DP...");

  lbool check_res = yices_check(dp_ct);
 
  bool res;
  if (check_res == l_true) {
    res = true;
  } else if (check_res == l_false) {
    res = false;
  } else
    CHK(0);

  fprintf(stderr, (res?"SAT\n":"UNSAT\n"));

  return res;
}

bool YicesDP::check_max_sat(long long max_cost) 
{
  if (retract_map.empty())
    return get_sat_result();
  lbool check_res;

  fprintf(stderr, "INVOKE DP (max sat)...");

  if (max_cost != -1)
    check_res = yices_max_sat_cost_leq(dp_ct, max_cost);
  else
    check_res = yices_max_sat(dp_ct);

  if (check_res == l_true) {
    return true;
  } else if (check_res == l_false)
    return false;
  else
    CHK(0);
}

bool YicesDP::find_weighted_model() 
{
  lbool check_res = yices_find_weighted_model(dp_ct, 0);
  if (check_res == l_true) {
    return true;
  } else if (check_res == l_false)
    return false;
  else
    CHK(0);
}

// ------------- Models ----------------

//Given a yices model M and a var declaration V, returns the value of V in M. 
int YicesDP::show_val(yices_model m, yices_var_decl yvd) 
{
  long res;
  int tmp1 = yices_get_int_value(m, yvd, &res);
  if (tmp1) {
    return (int) res;
  }
  assert( 0 && "YicesDP::show_val() is not integer or bool!\n");
}

int YicesDP::show_val(const stdstring &name) 
{
  yices_var_decl yvd = yices_get_var_decl_from_name(dp_ct,
                                                    (char*) name.c_str());
  CHK( yvd);
  yices_model m = yices_get_model(dp_ct);
  CHK( m != NULL);
  return show_val(m, yvd);
}

// New function convert int to string;
std::string YicesDP::bv_string(int int_array[], int size){
  string retv;
  stringstream retstr;
  for(int i = size-1; i >= 0; i--){
    retstr << int_array[i];
  }
  retv = "0b" + retstr.str();
  return retv;
}

void YicesDP::show_sat() 
{
  yices_model m = yices_get_model(dp_ct);
  CHK(m);
  cout << "---[\n";
  const_foreach(it, var_decls) {
    string name = yices_get_var_decl_name(*it);
    long c;
    double dc;

    //for bitvector:
    int len = 32;
    int bv [32];

    if (yices_get_int_value(m,*it,&c)) 
      cout << name << ":::" << (int)c << endl;
    else if (yices_get_double_value(m,*it,&dc)) 
      cout << name << " ::: " << (double)dc << endl;                          //Here original is c
    else if (yices_get_bitvector_value(m,*it,len,bv)){
      string bv_value;
      bv_value = bv_string(bv, len);
      cout << name << " ::: " << bv_value <<endl;
    }
      //cout << name << " ::: " << "sth bv" <<endl;
    else {
      lbool val = yices_get_value(m, *it);
      if (val==l_false)
        cout << name << " ::: " << "0"<< endl;
      else if (val==l_true)
        cout << name << " ::: " << "1"<< endl;
      else 
        cout << name << " ::: " << "undefffff"<< endl;
    }
  }
  cout << "---]\n";


}

void YicesDP::eval_and_print_in_model(YicesDP_expr e) 
{
  yices_model m = yices_get_model(dp_ct);
  CHK(m);
  lbool lb = yices_evaluate_in_model(m, e);
  cerr << "expr : ";
  print(e);
  show_lbool(lb);
}

void YicesDP::create_model(map<stdstring, int> & model) 
{
  yices_model m = yices_get_model(dp_ct);
  CHK(m);
  const_foreach(it, var_decls)
    {
      int c = show_val(m, *it);
      model[yices_get_var_decl_name(*it)] = c;
    }
}

void YicesDP::get_model(const pair<expr, expr> & p, pair<int, int> &val) 
{
  yices_model m = yices_get_model(dp_ct);
  CHK(m);
  val.first = (yices_evaluate_in_model(m, p.first));
  val.second = (yices_evaluate_in_model(m, p.second));
}

