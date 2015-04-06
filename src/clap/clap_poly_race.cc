#include <sys/time.h>
#include "clap_poly_trace.hh"


void PolyTrace::find_potential_races(vector<PolyEventPair>& races)
{
  vector<PolyObject*>::iterator it;
  for (it = objects.begin(); it != objects.end(); it++) {
    PolyObject* obj = (*it);
    //for each object, enumerate the (w, w/r) pairs
    vector<PolyEvent*>::iterator wit;
    for (wit = obj->write_evs.begin(); wit != obj->write_evs.end(); wit++) {
      PolyEvent* w1 = (*wit);
      vector<PolyEvent*>::iterator ait;
      for (ait = obj->all_evs.begin(); ait != obj->all_evs.end(); ait++) {
        PolyEvent* rw2 = (*ait);
        if (w1->thread_id != rw2->thread_id) {
          if ( (rw2->eid <= w1->eid) && (rw2->type == OBJ_WRITE) ) {
            //we've processed it before 
            continue;
          }
          if (w1->lockset.intersectIsEmpty(rw2->lockset)) {
            PolyEventPair cp(w1,rw2);
            cout << __FUNCTION__ << " : " << cp.toString() << endl;
            races.push_back( cp );
          }
        }
      }
    }
  }

  cout << __FUNCTION__ << " : " << "races = " << races.size() << endl;
}

void PolyTrace::filter_races_by_lockset(vector<PolyEventPair>& races)
{
  /*
  vector<PolyEventPair> p_races = races;
  races.clear();
  
  vector<PolyEventPair>::iterator it;
  for (it = p_races.begin(); it != p_races.end(); it++) {
    PolyEvent* w1 = it->first;
    PolyEvent* w2 = it->second;
    if (w1->lockset.intersectIsEmpty(w2->lockset)) {
      cout << __FUNCTION__ << " : "
           << "( e" << w1->eid << ", e" << w2->eid << " )" << endl;
      races.push_back( PolyEventPair(w1,w2) );
    }
  }
  cout << __FUNCTION__ << " : " << "races = " << races.size() << endl;
  */
}

void PolyTrace::filter_races_by_hb(vector<PolyEventPair>& races, bool dbg_flag)
{
  vector<PolyEventPair> p_races = races;
  races.clear();

  vector<PolyEventPair>::iterator it;
  for (it = p_races.begin(); it != p_races.end(); it++) {
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
      races.push_back( PolyEventPair(w1,w2) );
  }

  if (dbg_flag)
    cout  << "\033[1;31m@@@ Error: " << __FUNCTION__ << " : " << "races = " << races.size() << "\033[0m" << endl;
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


 void PolyTrace::filter_races(const char *str, vector<PolyEventPair>& races, bool dbg_flag)
{
  add_thread_edges();

  vector<PolyEventPair> p_races = races;
  races.clear();
  
  vector<PolyEventPair>::iterator it;
  for (it = p_races.begin(); it != p_races.end(); it++) {
    PolyEvent* w1 = it->first;
    PolyEvent* w2 = it->second;
    if (simultaneously_reachable(w1,w2)) {
      cout << str << " : " 
           << "( e" << w1->eid << ", e" << w2->eid << " )" << endl;
      races.push_back( PolyEventPair(w1,w2) );
    }
  }
  if (dbg_flag)
    cout << "\033[1;31m@@@ Error: " << str << " : " << "races = " << races.size() << "\033[0m" << endl;
}

void PolyTrace::filter_races_by_ucg(vector<PolyEventPair>& races, bool dbg_flag)
{
  add_acq_rel_edges();
  filter_races(__FUNCTION__,races, dbg_flag);
}

void PolyTrace::filter_races_by_vt(vector<PolyEventPair>& races, bool dbg_flag)
{
  add_write_read_edges();
  filter_races(__FUNCTION__,races, dbg_flag);
}

void PolyTrace::filter_races_by_cp(vector<PolyEventPair>& races, bool dbg_flag)
{
  add_causally_precedes_edges();
  filter_races(__FUNCTION__,races, dbg_flag);  
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


void PolyTrace::check_race()
{
  dump();

  double time_lockset = 0, time_hb = 0, time_ucg = 0, time_vt = 0, time_cp = 0;
  int n_race_lockset = 0, n_race_hb = 0, n_race_ucg = 0, n_race_vt = 0, n_race_cp = 0;
  
  struct timeval start_time;
  gettimeofday(&start_time,NULL);

  vector<PolyEventPair> races;
  find_potential_races( races );
  filter_races_by_lockset( races );
  n_race_lockset = races.size();

  add_thread_edges();
  add_signal_wait_edges();

  char *flag_str = getenv("CLAP_POLY_METHOD");
  if (flag_str && !strcmp(flag_str,"hb")) {
    filter_races_by_hb( races, true );
    time_hb = compute_elapse_time(&start_time);
  }
  else if (flag_str && !strcmp(flag_str,"ucg")) {
    filter_races_by_hb( races, false);
    filter_races_by_ucg( races, true );
    time_ucg = compute_elapse_time(&start_time);
  }
  else if (flag_str && !strcmp(flag_str,"cp")) {
    filter_races_by_hb( races, false );
    filter_races_by_ucg( races, false );
    filter_races_by_cp( races, true );
    time_cp = compute_elapse_time(&start_time);
  }
  else if (flag_str && !strcmp(flag_str,"vt")) {
    filter_races_by_hb( races, true );
    filter_races_by_ucg( races, true );
    filter_races_by_vt( races, true );
    time_vt = compute_elapse_time(&start_time);
  }
  else {
    filter_races_by_hb( races , true);
    n_race_hb = races.size();
    time_hb = compute_elapse_time(&start_time);

    filter_races_by_ucg( races , true);
    n_race_ucg = races.size();
    time_ucg = compute_elapse_time(&start_time);

    filter_races_by_vt( races , true);
    n_race_vt = races.size();
    time_vt = compute_elapse_time(&start_time);

    filter_races_by_cp( races , true);
    n_race_cp = races.size();
    time_cp = compute_elapse_time(&start_time);    

    //print_statistics();
    cout << endl
         << " @@ races_lockset= " << n_race_lockset
         << " races_hb= " << n_race_hb
         << " races_ucg= " << n_race_ucg
         << " races_vt= " << n_race_vt
         << " races_cp= " << n_race_cp
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
