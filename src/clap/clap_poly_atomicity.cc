#include <sys/time.h>
#include "clap_poly_trace.hh"

/*

void PolyTrace::find_potential_avs(vector<PolyEventPair>& avs)
{

  cout << __FUNCTION__ << " : " << "races = " << avs.size() << endl;
}

void PolyTrace::filter_avs_by_lockset(vector<PolyEventPair>& avs)
{
  vector<PolyEventPair> p_avs = avs;
  avs.clear();
  
  vector<PolyEventPair>::iterator it;
  for (it = p_avs.begin(); it != p_avs.end(); it++) {
    PolyEvent* w1 = it->first;
    PolyEvent* w2 = it->second;
    if (w1->lockset.intersectIsEmpty(w2->lockset)) {
      cout << __FUNCTION__ << " : "
           << "( e" << w1->eid << ", e" << w2->eid << " )" << endl;
      avs.push_back( PolyEventPair(w1,w2) );
    }
  }
  cout << __FUNCTION__ << " : " << "avs = " << avs.size() << endl;
}

void PolyTrace::filter_avs_by_hb(vector<PolyEventPair>& avs, bool dbg_flag)
{
  vector<PolyEventPair> p_avs = avs;
  avs.clear();

  vector<PolyEventPair>::iterator it;
  for (it = p_avs.begin(); it != p_avs.end(); it++) {
    PolyEvent* w1 = it->first;
    PolyEvent* w2 = it->second;
    if (main_first_thread_create_ev != NULL) {
      if (w1->eid < main_first_thread_create_ev->eid ||
          w2->eid < main_first_thread_create_ev->eid)  continue;
    }
    if (main_last_thread_join_ev != NULL) {
      if (w1->eid > main_last_thread_join_ev->eid ||
          w2->eid > main_last_thread_join_ev->eid)  continue;
    }
    cout << __FUNCTION__ << " : "
         << "( e" << w1->eid << ", e" << w2->eid << " )" << endl;
      avs.push_back( PolyEventPair(w1,w2) );
  }

  if (dbg_flag)
    cout  << "\033[1;31m@@@ Error: " << __FUNCTION__ << " : " << "avs = " << avs.size() << "\033[0m" << endl;
}


bool PolyTrace::simultaneously_reachable(PolyEvent* ev1, PolyEvent* ev2)
{
 bool res = true;

  PolyEvent* prev1 = ev1->prev;
  PolyEvent* prev2 = ev2->prev;

  graph.addReachableCond(ev1->eid, true);
  graph.addReachableCond(ev2->eid, true);

  if (prev1 != NULL) 
    graph.addEdge(prev1->eid, ev2->eid, true);
  if (prev2 != NULL)
    graph.addEdge(prev2->eid, ev1->eid, true);

  if (prev1 || prev2) {
    if (!graph.check()) { // UNSAT
      res = false;
    }
  }
  
  if (prev2 != NULL)
    graph.removeEdge(prev2->eid, ev1->eid);
  if (prev1 != NULL)
    graph.removeEdge(prev1->eid, ev2->eid);

  graph.removeReachableCond(ev1->eid);
  graph.removeReachableCond(ev2->eid);

  return res;
}


 void PolyTrace::filter_avs(const char *str, vector<PolyEventPair>& avs, bool dbg_flag)
{
  add_thread_edges();

  vector<PolyEventPair> p_avs = avs;
  avs.clear();
  
  vector<PolyEventPair>::iterator it;
  for (it = p_avs.begin(); it != p_avs.end(); it++) {
    PolyEvent* w1 = it->first;
    PolyEvent* w2 = it->second;
    if (simultaneously_reachable(w1,w2)) {
      cout << str << " : " 
           << "( e" << w1->eid << ", e" << w2->eid << " )" << endl;
      avs.push_back( PolyEventPair(w1,w2) );
    }
  }
  if (dbg_flag)
    cout << "\033[1;31m@@@ Error: " << str << " : " << "avs = " << avs.size() << "\033[0m" << endl;
}

void PolyTrace::filter_avs_by_ucg(vector<PolyEventPair>& avs, bool dbg_flag)
{
  add_acq_rel_edges();
  filter_avs(__FUNCTION__,avs, dbg_flag);
}

void PolyTrace::filter_avs_by_vt(vector<PolyEventPair>& avs, bool dbg_flag)
{
  add_write_read_edges();
  filter_avs(__FUNCTION__,avs, dbg_flag);
}

void PolyTrace::filter_avs_by_cp(vector<PolyEventPair>& avs, bool dbg_flag)
{
  add_causally_precedes_edges();
  filter_avs(__FUNCTION__,avs, dbg_flag);  
}



double compute_elapse_time(struct timeval * start_time)
{
  struct timeval end_time;
  gettimeofday(&end_time,NULL);

  double sec;
  double usec;
  sec = end_time.tv_sec - start_time->tv_sec;
  usec = end_time.tv_usec - start_time->tv_usec;

  if (usec < 0){
    usec += 1000000;
    sec--;
  }

  return sec+(usec/1000000);
}


void PolyTrace::check_violation()
{
  dump();

  double time_lockset, time_hb, time_ucg, time_vt, time_cp;
  int n_av_lockset, n_av_hb, n_av_ucg, n_av_vt, n_av_cp;
  
  struct timeval start_time;
  gettimeofday(&start_time,NULL);

  vector<PolyEventPair> avs;
  find_potential_avs( avs );
  filter_avs_by_lockset( avs );
  n_av_lockset = avs.size();

  add_thread_edges();
  add_signal_wait_edges();

  char *flag_str = getenv("CLAP_POLY_METHOD");
  if (flag_str && !strcmp(flag_str,"hb")) {
    filter_avs_by_hb( avs, true );
    time_hb = compute_elapse_time(&start_time);
  }
  else if (flag_str && !strcmp(flag_str,"ucg")) {
    filter_avs_by_hb( avs, false);
    filter_avs_by_ucg( avs, true );
    time_ucg = compute_elapse_time(&start_time);
  }
  else if (flag_str && !strcmp(flag_str,"cp")) {
    filter_avs_by_hb( avs, false );
    filter_avs_by_ucg( avs, false );
    filter_avs_by_cp( avs, true );
    time_cp = compute_elapse_time(&start_time);
  }
  else if (flag_str && !strcmp(flag_str,"vt")) {
    filter_avs_by_hb( avs, true );
    filter_avs_by_ucg( avs, true );
    filter_avs_by_vt( avs, true );
    time_vt = compute_elapse_time(&start_time);
  }
  else {
    filter_avs_by_hb( avs , true);
    n_av_hb = avs.size();
    time_hb = compute_elapse_time(&start_time);

    filter_avs_by_ucg( avs , true);
    n_av_ucg = avs.size();
    time_ucg = compute_elapse_time(&start_time);

    filter_avs_by_vt( avs , true);
    n_av_vt = avs.size();
    time_vt = compute_elapse_time(&start_time);

    filter_avs_by_cp( avs , true);
    n_av_cp = avs.size();
    time_cp = compute_elapse_time(&start_time);    

    print_statistics();
    cout << endl
         << " @@ avs_lockset= " << n_av_lockset
         << " avs_hb= " << n_av_hb
         << " avs_ucg= " << n_av_ucg
         << " avs_vt= " << n_av_vt
         << " avs_cp= " << n_av_cp
         << endl;

    cout << endl
         << " @@ time_lockset= " << time_lockset
         << " time_hb= " << time_hb 
         << " time_ucg= " << time_ucg
         << " time_vt= " << time_vt 
         << " time_cp= " << time_cp
         << endl;
  }


}


*/

void PolyTrace::check_atomicity()
{
  assert(0);
}
