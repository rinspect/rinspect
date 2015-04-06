#include <sys/time.h>
#include "clap_poly_trace.hh"

#define USE_SLICING 0

PolyTrace::PolyTrace()
{
  main_start_ev = NULL;
  main_end_ev = NULL;
  main_first_thread_create_ev = NULL;
  main_last_thread_join_ev = NULL;
}

PolyTrace::~PolyTrace()
{
  id_to_thread.clear();
  id_to_mutex.clear();
  id_to_object.clear();
  id_to_condvar.clear();
  thread_to_start.clear();  
  thread_to_last_event.clear();  
}

void PolyTrace::add_event(PolyEventType typ, int tid, int var)
{

#if USE_SLICING  

  if (tid != 1) { //child thread encounter unknown reads/writes
    if (typ == OBJ_READ || typ == OBJ_WRITE) {
      if (id_to_object.find(var) == id_to_object.end()) {
        return;
      }
    }
  }
  else { //main thread before child threads are created
    if (typ == OBJ_READ || typ == OBJ_WRITE) {
      if (main_first_thread_create_ev == NULL)
        return;
    }
  }

#endif

  PolyEvent *ev = new PolyEvent(typ,tid,var);
  events.push_back(ev);
  
  handle_thread(ev);
  handle_mutex(ev);
  handle_condvar(ev);
  handle_object(ev);
}

void PolyTrace::handle_thread(PolyEvent* ev)
{
  ev->prev = thread_to_last_event[ev->thread_id];
  thread_to_last_event[ev->thread_id] = ev;

  switch (ev->type) {
  case THREAD_START:  {
    PolyThread* t = new PolyThread(ev->thread_id);
    threads.push_back(t);
    id_to_thread[ev->thread_id] = t;
    thread_to_start[ev->thread_id] = ev;

    LockSet emptyls;
    curr_locksets[ev->thread_id] = emptyls;

    if (ev->thread_id == 1) 
      main_start_ev = ev;
    break;
  }
  case THREAD_END: {
    PolyThread* t = id_to_thread[ev->thread_id];
    PolyEvent* start_ev = thread_to_start[ev->thread_id];
    PolyEvent* end_ev   = ev;
    t->entry = start_ev;
    t->exit  = end_ev;
    thread_to_start.erase(ev->thread_id);

    if (ev->thread_id == 1) {
      main_end_ev = ev;
      //as a pre-caution, check if child threads ended
      for (map<int,PolyThread*>::iterator it = id_to_thread.begin();
           it != id_to_thread.end(); it++) {
        if (it->first == 1) continue;
        if (it->second->entry && it->second->exit) continue;
        //child thread still running
        it->second->entry = thread_to_start[it->first];
        it->second->exit = thread_to_last_event[it->first];
      }
    }

    break;
  }

  case THREAD_CREATE: 
    if (ev->thread_id == 1 && main_first_thread_create_ev == NULL) {
      main_first_thread_create_ev = ev;
    }
    break;

  case THREAD_JOIN:
    if (ev->thread_id == 1) {
      main_last_thread_join_ev = ev;
    }

  default:
    break;
  }
}

void PolyTrace::handle_mutex(PolyEvent* ev)
{
  LockSet& curr_lockset = curr_locksets[ev->thread_id];

  ev->lockset = curr_lockset;
  switch (ev->type) {
  case MUTEX_LOCK:   curr_lockset.insert(ev->mutex_id);   break;
  case MUTEX_UNLOCK: curr_lockset.erase(ev->mutex_id);    break;
  default:    break;
  }
  
  switch (ev->type) {
  case MUTEX_INIT:    {
    PolyMutex* m = new PolyMutex(ev->mutex_id);
    mutexes.push_back(m);
    id_to_mutex[ev->mutex_id] = m;
    break;
  }
  case MUTEX_LOCK:    {
    mutex_to_acq[ev->mutex_id] = ev;
    break;
  }
  case MUTEX_UNLOCK:  {
    PolyMutex* m = id_to_mutex[ev->mutex_id];
    PolyEvent* acq_ev = mutex_to_acq[ev->mutex_id];
    PolyEvent* rel_ev = ev;
    m->acq_rel_pairs.push_back(PolyEventPair(acq_ev,rel_ev));
    mutex_to_acq.erase(ev->mutex_id);
    break;
  }
  default:  break;
  }

}

void PolyTrace::handle_condvar(PolyEvent* ev)
{
  ev->condset = curr_condset;
  switch (ev->type) {
  case COND_SIGNAL:   curr_condset.insert(ev->cond_id);   break;
  case COND_WAIT:     curr_condset.erase(ev->cond_id);    break;
  default:    break;
  }

  switch (ev->type) {
  case COND_INIT:    {
    PolyCondVar* c = new PolyCondVar(ev->cond_id);
    condvars.push_back(c);
    id_to_condvar[ev->cond_id] = c;
    break;
  }
  case COND_SIGNAL:    {
    cond_to_signal[ev->cond_id] = ev;
    break;
  }
  case COND_WAIT:      {
    PolyCondVar* c = id_to_condvar[ev->cond_id];
    assert(c);
    PolyEvent* s_ev = cond_to_signal[ev->cond_id];
    PolyEvent* w_ev = ev;
    c->signal_wait_pairs.push_back(PolyEventPair(s_ev,w_ev));

    // chao: why do we have to erase it?  retaining it main be useful for 
    //       handling broadcast in the same with as signal
    //cond_to_signal.erase(ev->cond_id);
    break;
  }
  default:
    break;
  }

}


void PolyTrace::handle_object(PolyEvent* ev)
{
  ev->varset = curr_varset;
  switch (ev->type) {
  case OBJ_WRITE:   curr_varset.insert(ev->obj_id);   break;
  case OBJ_READ:    curr_varset.erase(ev->obj_id);    break;
  default:    break;
  }

  switch (ev->type) {
  case OBJ_REGISTER:    {
    PolyObject* m = new PolyObject(ev->obj_id);
    objects.push_back(m);
    id_to_object[ev->obj_id] = m;
    break;
  }
  case OBJ_WRITE:    {
    if (id_to_object.find(ev->obj_id) == id_to_object.end()) {
      //just in case...
      PolyObject* m = new PolyObject(ev->obj_id);
      objects.push_back(m);
      id_to_object[ev->obj_id] = m;
    }
    obj_to_write[ev->obj_id] = ev;
    PolyObject* m = id_to_object[ev->obj_id];
    assert(m);
    m->write_evs.push_back(ev);
    m->all_evs.push_back(ev);
    break;
  }
  case OBJ_READ:  {
    if (id_to_object.find(ev->obj_id) == id_to_object.end()) {
      //just in case...
      PolyObject* m = new PolyObject(ev->obj_id);
      objects.push_back(m);
      id_to_object[ev->obj_id] = m;
    }
    PolyObject* m = id_to_object[ev->obj_id];
    assert(m);
    m->all_evs.push_back(ev);

    PolyEvent* acq_ev = obj_to_write[ev->obj_id];
    PolyEvent* rel_ev = ev;
    if (acq_ev == 0) {
      acq_ev = main_start_ev;
    }
    m->write_read_pairs.push_back(PolyEventPair(acq_ev,rel_ev));
    //obj_to_write.erase(ev->obj_id);
    break;
  }
  default:
    break;
  }

}

void PolyTrace::slicing()
{

#if USE_SLICING

  //remove local objects
  int count_thread_local_object = 0;
  int count_thread_local_event = 0;
  for (vector<PolyObject*>::iterator it = objects.begin(); it != objects.end(); ) {
    PolyObject* obj = (*it);
    bool obj_is_thread_local = true;
    
    //if (obj->write_read_pairs.size() < 100 ) {
    map<int,int> tmp_threads;
    for (vector<PolyEvent*>::iterator eit = obj->all_evs.begin(); eit != obj->all_evs.end(); eit++) {
      PolyEvent* ev = (*eit);
      if (main_first_thread_create_ev && ev->eid < main_first_thread_create_ev->eid) continue;
      if (main_last_thread_join_ev && ev->eid > main_last_thread_join_ev->eid) continue;
      tmp_threads[ev->thread_id] = 1;
    }
    obj_is_thread_local = (tmp_threads.size() == 1);
     //}

    if (obj_is_thread_local) {
      count_thread_local_object++;
      //cout << __FUNCTION__ << " : thread local object_id=" << obj->id << endl;
      map<PolyEvent*,int> map_all_evs;
      for (vector<PolyEvent*>::iterator it2 = obj->all_evs.begin(); it2 != obj->all_evs.end(); it2++) {
        PolyEvent* ev = (*it2);
        map_all_evs[ev] = 1;
      }
      for (vector<PolyEvent*>::iterator it2 = events.begin(); it2 != events.end(); ) {
        PolyEvent* ev = (*it2);
        if (map_all_evs.find(ev) != map_all_evs.end()) {
          delete ev;
          count_thread_local_event++;
          it2 = events.erase(it2);        
        }
        else {
          it2++;
        }
      }
      delete obj;
      it = objects.erase(it);
    }
    else {
      it ++;
    }
  }
  cout << __FUNCTION__ << " : num_objects = " << objects.size() 
       << " , num_thread_local_objects = " << count_thread_local_object << endl;
  cout << __FUNCTION__ << " : num_events = " << (events.size() + count_thread_local_event)
       << " , num_thread_local_events = " << count_thread_local_event << endl;

#endif
}

void PolyTrace::dump()
{
  string default_console = "\033[0m";

  cout << "--------------------PolyTrace::dump()-------------------\n";
  {
    vector<PolyEvent*>::iterator it;
    for (it = events.begin(); it != events.end(); it++) {
      PolyEvent* ev = (*it);
      
      string color = "\033[0;";
      switch (ev->type) {
      case OBJ_WRITE:      color = "\033[1;"; break;
      case OBJ_READ:       color = "\033[1;"; break;
      case MUTEX_LOCK:     color = "\033[1;"; break;
      case MUTEX_UNLOCK:   color = "\033[1;"; break;
      default:
        color = "\033[0;"; break;
      }

      switch (ev->thread_id) {
      case 101: color += "32m";  break;
      case 201: color += "33m";  break;
      case 301: color += "34m";  break;
      case 401: color += "35m";  break;
      case 501: color += "36m";  break;
      case 601: color += "37m";  break;
      case 701: color += "38m";  break;
      case 801: color += "39m";  break;
      default: 
        color += "37m"; break;
      }

      cout << color << ev->toString() << endl;
      
    }
    cout << default_console << endl;
  }

  {
    vector<PolyThread*>::iterator it;
    for (it = threads.begin(); it != threads.end(); it++) {
      PolyThread* thread = (*it);
      cout << thread->toString() << endl;
    }
  }

  {
    vector<PolyMutex*>::iterator it;
    for (it = mutexes.begin(); it != mutexes.end(); it++) {
      PolyMutex* mutex = (*it);
      cout << mutex->toString() << endl;
    }
  }

  {
    vector<PolyObject*>::iterator it;
    for (it = objects.begin(); it != objects.end(); it++) {
      PolyObject* object = (*it);
      cout << object->toString() << endl;
    }
  }

  {
    vector<PolyCondVar*>::iterator it;
    for (it = condvars.begin(); it != condvars.end(); it++) {
      PolyCondVar* condvar = (*it);
      cout << condvar->toString() << endl;
    }
  }

  cout << "--------------------------------------------------------\n";
  print_statistics();
}

void PolyTrace::print_statistics()
{
  int n_threads = threads.size();
  int n_conds = condvars.size();
  int n_objs = objects.size();
  int n_locks = mutexes.size();

  int n_evs = events.size();
  int n_lock_ev = 0;
  int n_unlock_ev = 0;
  int n_signal_ev = 0;
  int n_wait_ev = 0;
  int n_read_ev = 0;
  int n_write_ev = 0;

  for (vector<PolyEvent*>::iterator it=events.begin(); it!=events.end(); it++) {
    PolyEvent* ev = (*it);
    switch( ev->type ) {
    case MUTEX_LOCK: n_lock_ev++; break;
    case MUTEX_UNLOCK: n_unlock_ev++; break;
    case COND_SIGNAL: n_signal_ev++; break;
    case COND_WAIT: n_wait_ev++; break;
    case OBJ_READ: n_read_ev++; break;
    case OBJ_WRITE: n_write_ev++; break;
    default: break;
    }
  }
  
  cout << " @@ "
       << " threads= " << n_threads 
       << " locks= " << n_locks
       << " conds= " << n_conds
       << " objs= " << n_objs
       << " evs= " << n_evs
       << " lock_evs= " << (n_lock_ev+n_unlock_ev) 
       << " cond_evs= " << (n_signal_ev+n_wait_ev)
       << " obj_evs = " << (n_read_ev+n_write_ev)
       << " read_evs= " << n_read_ev
       << " write_evs= " << n_write_ev
       << endl;
}

// thread-local, and fork/join, precedence edges
void PolyTrace::add_thread_edges()
{
  map<int,PolyEvent*>  last_event_of_thread;

  vector<PolyEvent*>::iterator it;
  for (it = events.begin(); it != events.end(); it++) {
    PolyEvent* ev = (*it);
    int tid = ev->thread_id;
    //cout << __FUNCTION__ << " : " << ev->toString() << endl;

    if (last_event_of_thread.find(tid) != last_event_of_thread.end()) {
      PolyEvent* ev_last = last_event_of_thread[tid];
      //add edge (ev_last ==> ev)
      graph.addEdge(ev_last->eid, ev->eid, false);
    }
    last_event_of_thread[tid] = ev;

    if (ev->type == THREAD_CREATE) {
      PolyThread* t_child = id_to_thread[ev->child_id];
      assert(t_child);
      PolyEvent* ev_child = t_child->entry;
      //add edge (fork ==> child_last_ev)
      graph.addEdge(ev->eid, ev_child->eid, false);
    }
    else if (ev->type == THREAD_JOIN) {
      PolyThread* t_child = id_to_thread[ev->child_id];
      assert(t_child);
      PolyEvent* ev_child = t_child->exit;
      //add edge (child_last_ev ==> join)
      graph.addEdge(ev_child->eid, ev->eid, false);
    }
  }

  last_event_of_thread.clear();
  for (it = events.begin(); it != events.end(); it++) {
    PolyEvent* ev = (*it);
    int tid = ev->thread_id;
    //cout << __FUNCTION__ << " : " << ev->toString() << endl;

    if (last_event_of_thread.find(tid) != last_event_of_thread.end()) {
      PolyEvent* ev_last = last_event_of_thread[tid];

      if (ev_last->type == OBJ_READ || ev_last->type == COND_WAIT) {
        //g(ev) = g(ev_last) && coupledR(gv_last)
        graph.addGuardRead(ev_last->eid, ev->eid, false);
      }
      else if (ev_last->type == MUTEX_LOCK) {
        //g(ev) = g(ev_last) && coupledA(gv_last)
        graph.addGuardAcq(ev_last->eid, ev->eid, false);
      }
      else if (ev->type == THREAD_JOIN) {
        //g(ev) = g(ev_last) && g(ev_child)
        PolyThread* t_child = id_to_thread[ev->child_id];
        assert(t_child);
        PolyEvent* ev_child = t_child->exit;
        graph.addGuardJoin(ev_last->eid, ev_child->eid, ev->eid, false);
      }
      else {
        //g(ev) = g(ev_last)
        graph.addGuard(ev_last->eid, ev->eid, false);
      }

    }

    if (ev->type == THREAD_CREATE) {
      PolyThread* t_child = id_to_thread[ev->child_id];
      assert(t_child);
      PolyEvent* ev_child = t_child->entry;
      //g(ev_child) = g(ev)
      graph.addGuard(ev->eid, ev_child->eid, false);
    }
    
    last_event_of_thread[tid] = ev;
  }
  
}

void PolyTrace::add_acq_rel_edges()
{
  vector<PolyMutex*>::iterator it;
  for (it = mutexes.begin(); it != mutexes.end(); it++) {
    PolyMutex* m = (*it);
    vector<PolyEventPair>& pairs = m->acq_rel_pairs;

    //for each mutex, go throug all it's acq_rel_pairs
    vector<PolyEventPair>::iterator pit1;
    for (pit1 = pairs.begin(); pit1 != pairs.end(); pit1++) {
      PolyEvent* acq1 = pit1->first;
      PolyEvent* rel1 = pit1->second;

      vector<PolyEventPair>::iterator pit2;
      for (pit2 = pit1+1; pit2 != pairs.end(); pit2++) {
        if (pit1 == pit2) continue;
        PolyEvent* acq2 = pit2->first;
        PolyEvent* rel2 = pit2->second;
        if (acq1->thread_id != acq2->thread_id) {
          cout << __FUNCTION__ << " : " 
               << pit1->toString() << pit2->toString() << endl;
          // add conditional edge
          //   coupledA(acq1) -> Either-Or( acq1 < acq2,  g(rel2) & (rel2 < acq1)
          //   coupledA(acq2) -> Either-Or( acq2 < acq1,  g(rel1) & (rel1 < acq2)
          graph.addPolyEdge_AcqRel(acq1->eid, rel1->eid, acq2->eid, rel2->eid, false);            
        }
      }
    }
  }
}



void PolyTrace::add_write_read_edges()
{
  vector<PolyObject*>::iterator it;
  for (it = objects.begin(); it != objects.end(); it++) {
    PolyObject* m = (*it);
    vector<PolyEventPair>& pairs = m->write_read_pairs;

    //for each object, go throug all it's write_read_pairs
    vector<PolyEventPair>::iterator pit1;
    for (pit1 = pairs.begin(); pit1 != pairs.end(); pit1++) {
      PolyEvent* w1 = pit1->first;
      PolyEvent* r1 = pit1->second;
      cout << __FUNCTION__ << " : " << pit1->toString() << endl;
      // add conditional edge: coupledR(r1) -> g(w) && (w1 ==> r1)
      graph.addEdgeConditional(w1->eid, r1->eid, false);

      vector<PolyEventPair>::iterator pit2;
      for (pit2 = pit1+1; pit2 != pairs.end(); pit2++) {
        if (pit1 != pit2) {
          PolyEvent* w2 = pit2->first;
          PolyEvent* r2 = pit2->second;
          if (w1->thread_id != w2->thread_id) {
            cout << __FUNCTION__ << " : " 
                 << pit1->toString() << pit2->toString() << endl;
            // add conditional edge:
            //    coupledR(r1) -> Either-Or( r1 => w2, w2 => w1 )
            //    coupledR(r2) -> Either-Or( r2 => w1, w1 => w2 )
            graph.addPolyEdgeConditional(r1->eid,w2->eid,w2->eid,w1->eid,
                                         r1->eid,true, false);
            graph.addPolyEdgeConditional(r2->eid,w1->eid,w1->eid,w2->eid,
                                         r2->eid,true, false);
          }
        }
      }
    }
  }
}


void PolyTrace::add_signal_wait_edges()
{
  vector<PolyCondVar*>::iterator it;
  for (it = condvars.begin(); it != condvars.end(); it++) {
    PolyCondVar* c = (*it);
    vector<PolyEventPair>& pairs = c->signal_wait_pairs;

    //for each object, go throug all it's signal_wait_pairs
    vector<PolyEventPair>::iterator pit1;
    for (pit1 = pairs.begin(); pit1 != pairs.end(); pit1++) {
      PolyEvent* w1 = pit1->first;
      PolyEvent* r1 = pit1->second;
      cout << __FUNCTION__ << " : " << pit1->toString() << endl;
      // add conditional edge: coupledR(r1) -> (w1 ==> r1)
      graph.addEdgeConditional(w1->eid, r1->eid, false);

      vector<PolyEventPair>::iterator pit2;
      for (pit2 = pit1+1; pit2 != pairs.end(); pit2++) {
        if (pit1 != pit2) {
          PolyEvent* w2 = pit2->first;
          PolyEvent* r2 = pit2->second;
          if (w1->thread_id != w2->thread_id) {
            cout << __FUNCTION__ << " : " 
                 << pit1->toString() << pit2->toString() << endl;
            // add conditional edge:
            //    coupledR(r1) -> Either-Or( r1 => w2, w2 => w1 )
            //    coupledR(r2) -> Either-Or( r2 => w1, w1 => w2 )
            graph.addPolyEdgeConditional(r1->eid,w2->eid,w2->eid,w1->eid,
                                         r1->eid,true, false);
            graph.addPolyEdgeConditional(r2->eid,w1->eid,w1->eid,w2->eid,
                                         r2->eid,true, false);
          }
        }
      }
    }
  }
}


void PolyTrace::add_causally_precedes_edges()
{
  vector<PolyObject*>::iterator it;
  for (it = objects.begin(); it != objects.end(); it++) {
    PolyObject* obj = (*it);
    //for each object, enumerate the (w1, w2/r2) pairs
    vector<PolyEvent*>::iterator wit;
    for (wit = obj->write_evs.begin(); wit != obj->write_evs.end(); wit++) {
      PolyEvent* w1 = (*wit);
      //for each (w1), find (rw2)
      vector<PolyEvent*>::iterator ait;
      for (ait = obj->all_evs.begin(); ait != obj->all_evs.end(); ait++) {
        PolyEvent* rw2 = (*ait);
        if (w1->thread_id != rw2->thread_id) {
          if ( (rw2->eid <= w1->eid) && (rw2->type == OBJ_WRITE) ) {
            //we've processed it before
            continue;
          }
          PolyEvent* src = (w1->eid < rw2->eid)? w1: rw2;
          PolyEvent* tgt = (w1->eid < rw2->eid)? rw2: w1;
          //
          // find all locks that are held by both (src) and (tgt)
          //
          set<MutexId> locks = w1->lockset.intersect(rw2->lockset);
          for(set<MutexId>::iterator it=locks.begin(); it!=locks.end(); it++) {
            PolyMutex* m = id_to_mutex[*it];
            vector<PolyEventPair>& pairs = m->acq_rel_pairs;
            //
            // for each lock, find all pairs
            //    (acq1 => src => rel1),  (acq2 => tgt => rel2)
            // add induced edge
            //    g(rel1) && (rel1 => acq2)
            //
            vector<PolyEventPair>::iterator pit1;
            vector<PolyEventPair>::iterator pit2;
            for (pit1 = pairs.begin(); pit1 != pairs.end(); pit1++) {
              PolyEvent* acq1 = pit1->first;
              PolyEvent* rel1 = pit1->second;
              for (pit2 = pairs.begin(); pit2 != pairs.end(); pit2++) {
                if (pit1 == pit2)  continue;
                PolyEvent* acq2 = pit2->first;
                PolyEvent* rel2 = pit2->second;
                if ( acq1->thread_id == src->thread_id && 
                     acq1->eid < src->eid && src->eid < rel1->eid ) {
                  if ( acq2->thread_id == tgt->thread_id && 
                       acq2->eid < tgt->eid && tgt->eid < rel2->eid ) {
                    PolyEventPair cp(rel1,acq2);
                    cout << __FUNCTION__ << " : " << cp.toString() << endl;
                    graph.addEdge(rel1->eid, acq2->eid, false);
                    graph.addReachableCond(rel1->eid, false);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}


