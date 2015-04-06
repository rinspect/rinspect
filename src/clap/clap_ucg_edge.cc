#include "clap_ucg_edge.hh"
#include "clap_ucg_graph.hh"

vector<vector<event_t> > rw_event_containers,
  sync_event_containers,
  mutex_event_containers;

//map<unsigned, edge_t> edges;
vector<edge_t> edges;

vector<edge_t> prop_seed_edges;

PolyGraph graph;

bool prop_hold = true,
  search_end = false,
  poly_edge_added = false,
  atomic_edge_added = false,
  write_flag = false;

unsigned idx_i = 0,
  idx_j = 0;


void add_ucg_edge(map<unsigned, vector<event_t> > thread_routine,
                  property_t prop)
{
  unsigned p, q, i, j;

  add_sequential_edge(thread_routine, false);
  add_sync_seed_edge(FORK_JOIN, wait_notify_pair/* 0 */, fork_join_list, 0, 0, cond_list);
    
  for (p = 0; p < thread_id.size() - 1; ++p) {
    for (q = p + 1; q < thread_id.size(); ++q) {
      add_sync_seed_edge(WAIT_NOTIFY, wait_notify_pair, fork_join_list/* 0 */, thread_id[p], thread_id[q], cond_list);
      add_poly_edge(locks_log, thread_id[p], thread_id[q]);
    }
  }

  add_atomic_edge(event_list, atomic_obj_list);

  map<int *, int>::iterator obj_it;

  for (obj_it = obj_list.begin();
       obj_it != obj_list.end();
       ++obj_it) {
    for (p = 0; p < thread_id.size() - 1; ++p) {
      for (q = p + 1; q < thread_id.size(); ++q) {
        for (i = 0; i < thread_routine[thread_id[p]].size(); ++i) {
          if (thread_routine[thread_id[p]][i].action != READ
              && thread_routine[thread_id[p]][i].action != WRITE) {
            continue;
          }
          if (thread_routine[thread_id[p]][i].obj_id != obj_it->second) {
            continue;
          }
          for (j = 0; j < thread_routine[thread_id[q]].size(); ++j) {
            if (thread_routine[thread_id[q]][j].action != READ
                && thread_routine[thread_id[q]][j].action != WRITE) {
              continue;
            }
            if (thread_routine[thread_id[q]][j].obj_id != obj_it->second) {
              continue;
            }
            if (thread_routine[thread_id[p]][i].action != WRITE
                && thread_routine[thread_id[q]][j].action != WRITE) {
              continue;
            }
            
            // if two potential events are protected by same locks
            locks_held_t tmp_locks_held;
            insert_iterator<locks_held_t> res_ins(tmp_locks_held, tmp_locks_held.begin());
            set_intersection(thread_routine[thread_id[p]][i].locks_held.begin(),
                             thread_routine[thread_id[p]][i].locks_held.end(),
                             thread_routine[thread_id[q]][j].locks_held.begin(),
                             thread_routine[thread_id[q]][j].locks_held.end(),
                             res_ins);
            if (!tmp_locks_held.empty()) {
              continue;
            }
            create_edge(thread_routine[thread_id[p]][i-1], thread_routine[thread_id[q]][j], PROP_SEED);
            create_edge(thread_routine[thread_id[q]][j-1], thread_routine[thread_id[p]][i], PROP_SEED);

                        add_induced_edge(thread_routine, mutex_list);
            if (!graph.check()) {
              printf("Property does not hold!\n");
            }
            else {
              printf("Property holds!\n");
            }
            while (!prop_seed_edges.empty()) {
              remove_edge(prop_seed_edges.back().source,
                        prop_seed_edges.back().target,
                        PROP_SEED);
              prop_seed_edges.pop_back();
            }
          }
        }
      }
    }
  }
  return;
}

void add_sequential_edge(map<unsigned, vector<event_t> > thread_routine,
                         bool mem_rlx)
{
  map<unsigned, vector<event_t> >::iterator thread_it;
  vector<event_t>::iterator event_it;
  for (thread_it = thread_routine.begin();
       thread_it != thread_routine.end();
       ++thread_it) {
    //    if (thread_it->first != thread_A && thread_it->first != thread_B) {
    //      continue;
    //    }

    if (mem_rlx == true) {
      for (event_it = thread_it->second.begin();
           event_it != thread_it->second.end();
           ++event_it) {
         
        action_t tmp_act = event_it->action;
        vector<event_t>::iterator tmp_ev_it;
        vector<event_t>::reverse_iterator tmp_ev_rit;
        switch(tmp_act) {
        case LOCK:{
          for (tmp_ev_it = event_it+1;
               tmp_ev_it != thread_it->second.end();
               ++tmp_ev_it) {
            create_edge(*event_it, *tmp_ev_it, SQTL_SEED);
          }
        }
          break;
        case UNLOCK:{
          for (tmp_ev_rit = (vector<event_t>::reverse_iterator)event_it;
               tmp_ev_rit != thread_it->second.rend();
               ++tmp_ev_rit) {
            create_edge(*tmp_ev_rit, *event_it, SQTL_SEED);
          }
        }
          break;
        case ATOMIC_LOAD:{
          switch(event_it->mem_odr) {
          case memory_order_consume:{
          }
            break;
          case memory_order_acquire:{
            for (tmp_ev_it = event_it+1;
                 tmp_ev_it != thread_it->second.end();
                 ++tmp_ev_it) {
              if (tmp_ev_it->action == ATOMIC_LOAD) {
                create_edge(*event_it, *tmp_ev_it, SQTL_SEED);
              }
            }
          }
            break;
          case memory_order_release:{
          }
            break;
          case memory_order_acq_rel:{
            for (tmp_ev_it = event_it+1;
                 tmp_ev_it != thread_it->second.end();
                 ++tmp_ev_it) {
              if (tmp_ev_it->action == ATOMIC_LOAD) {
                create_edge(*event_it, *tmp_ev_it, SQTL_SEED);
              }
            }
            for (tmp_ev_rit = (vector<event_t>::reverse_iterator)event_it;
                 tmp_ev_rit != thread_it->second.rend();
                 ++tmp_ev_rit) {
              if (tmp_ev_rit->action == ATOMIC_STORE) {
                create_edge(*tmp_ev_rit, *event_it, SQTL_SEED);
              }
            }
          }
            break;
          case memory_order_seq_cst:{
            for (tmp_ev_it = event_it+1;
                 tmp_ev_it != thread_it->second.end();
                 ++tmp_ev_it) {
              create_edge(*event_it, *tmp_ev_it, SQTL_SEED);
            }
            for (tmp_ev_rit = (vector<event_t>::reverse_iterator)event_it;
                 tmp_ev_rit != thread_it->second.rend();
                 ++tmp_ev_rit) {
              create_edge(*tmp_ev_rit, *event_it, SQTL_SEED);
            }
          }
            break;
          default:
            break;
          }
          break;
        }
        case ATOMIC_STORE:{
          switch(event_it->mem_odr) {
          case memory_order_consume:{
          }
            break;
          case memory_order_acquire:{
          }
            break;
          case memory_order_release:{
            for (tmp_ev_rit = (vector<event_t>::reverse_iterator)event_it;
                 tmp_ev_rit != thread_it->second.rend();
                 ++tmp_ev_rit) {
              if (tmp_ev_rit->action == ATOMIC_STORE) {
                create_edge(*tmp_ev_rit, *event_it, SQTL_SEED);
              }
            }
          }
            break;
          case memory_order_acq_rel:{
            for (tmp_ev_it = event_it+1;
                 tmp_ev_it != thread_it->second.end();
                 ++tmp_ev_it) {
              if (tmp_ev_it->action == ATOMIC_LOAD) {
                create_edge(*event_it, *tmp_ev_it, SQTL_SEED);
              }
            }
            for (tmp_ev_rit = (vector<event_t>::reverse_iterator)event_it;
                 tmp_ev_rit != thread_it->second.rend();
                 ++tmp_ev_rit) {
              if (tmp_ev_rit->action == ATOMIC_STORE) {
                create_edge(*tmp_ev_rit, *event_it, SQTL_SEED);
              }
            }
          }
            break;
          case memory_order_seq_cst:{
            for (tmp_ev_it = event_it+1;
                 tmp_ev_it != thread_it->second.end();
                 ++tmp_ev_it) {
              create_edge(*event_it, *tmp_ev_it, SQTL_SEED);
            }
            for (tmp_ev_rit = (vector<event_t>::reverse_iterator)event_it;
                 tmp_ev_rit != thread_it->second.rend();
                 ++tmp_ev_rit) {
              create_edge(*tmp_ev_rit, *event_it, SQTL_SEED);
            }
          }
            break;
          default:
            break;
          }
        }
          break;
        default:
          break;
        }
      }
    }
    else
      for (event_it = thread_it->second.begin();
           (event_it+1) != thread_it->second.end();
           ++event_it) {
        create_edge(*event_it, *(event_it+1), SQTL_SEED);
      }
  }//search_end = true;
}
/*
void ucg_seed_edge(property_t prop,
                   map<unsigned, vector<event_t> > thread_routine,
                   unsigned thread_A,
                   unsigned thread_B,
                   map<int *, int> *obj_list,
                   map<pthread_cond_t *, int> cond_list)
{
  ucg_property_seed_edge(prop, thread_routine, thread_A, thread_B, obj_list);
}
*/
 /*
bool add_property_seed_edge(property_t prop,
                            map<unsigned, vector<event_t> > thread_routine,
                            unsigned thread_A,
                            unsigned thread_B,
                            int obj_id)
{
  switch(prop){
  case DATA_RACE:{
    map<unsigned, vector<event_t> >::iterator thread_it;
    vector<event_t>::iterator event_it;



  } // end_check_date_races
    break;
  case ATOMICITY_VIOLATION:
    break;
  case ORDER_VIOLATION:
    break;
  case DEADLOCK:
    break;
  default:
    break;
  }
}
 */
void add_sync_seed_edge(sync_prop_t sync,
                        map<unsigned, vector<event_t> > wait_notify_pair,
                        vector<event_t> fork_join_list,
                        unsigned thread_A,
                        unsigned thread_B,
                        map<pthread_cond_t *, int> cond_list)
{
  switch(sync){
  case WAIT_NOTIFY:{
    map<pthread_cond_t *, int>::iterator cond_it;
    map<unsigned, vector<event_t> >::iterator pair_it;
    vector<event_t>::iterator event_it;
    for (cond_it = cond_list.begin(); cond_it != cond_list.end(); ++cond_it) {
      for (pair_it = wait_notify_pair.begin();
           pair_it != wait_notify_pair.end();
           ++pair_it) {
        if (pair_it->first != thread_A && pair_it->first != thread_B) {
          continue;
        }

        vector<event_t> tmp_vector;
        for (event_it = pair_it->second.begin();
             event_it != pair_it->second.end();
             ++event_it) {
          if (cond_it->second == event_it->cond_id) {
            tmp_vector.push_back(*event_it);
          } //end_if
        } //end_iterating_each_event
        sync_event_containers.push_back(tmp_vector);
      } //end_iterating_each_event_vector
      
      int m, n;
      if (sync_event_containers[0][0].action == WAIT_PRE) {
        m = 0;
        n = 1;
      }
      else {
        m = 1;
        n = 0;
      }
    
      unsigned int i, j;

      // 2-thread
      for (i = 0; i < sync_event_containers[m].size(); ++i) {
        if (sync_event_containers[m][i].action == WAIT_PRE) {
          for (j = 0; j < sync_event_containers[n].size(); ++j) {
            if (sync_event_containers[n][j].action == NOTIFY) {
              create_edge(sync_event_containers[m][i], sync_event_containers[n][j], SYNC_SEED);
              for (; i < sync_event_containers[m].size(); ++i) {
                if (sync_event_containers[m][i].action == WAIT_POST) {
                  create_edge(sync_event_containers[n][j], sync_event_containers[m][i], SYNC_SEED);
                  break;
                }
              } //notify-wait_post pair
              break;
            } //wait_pre-notify pair
          } // end_iterating_sync_event_containers[1]
          break;
        }
      } //end_iterating_sync_event_containers[0]
      
    } //end_iterating_each_condition
  }
    break;
  case FORK_JOIN: {
    unsigned i, j;
    for (i = 0; i < fork_join_list.size(); ++i) {
      unsigned temp_tid =  fork_join_list[i].child_id;
      if (fork_join_list[i].action == FORK) {
        for (j = 0; j < thread_routine[temp_tid].size(); ++j) {
          create_edge(fork_join_list[i], thread_routine[temp_tid][j], SYNC_SEED);
        }
      }
      else {
        // all the events from child threads should appear before join although
        // join actually happens before all those events
        for (j = 0; j < thread_routine[temp_tid].size(); ++j) {
          create_edge(thread_routine[temp_tid][j], fork_join_list[i], SYNC_SEED);
        }
      }
    }
  }
    break;
  default:
    break;
  }
  
  restore_event_containers(sync_event_containers);
 
}

void add_poly_edge(map<unsigned, map<int, map<action_t, map<int, int, less<int> > >, less<int> > > locks_log,
                   unsigned thread_A,
                   unsigned thread_B)
{
  map<pthread_mutex_t *, int>::iterator it;
  map<int, int, less<int> >::iterator it_A, it_B;
  for (it = mutex_list.begin(); it != mutex_list.end(); ++it) {
    if (locks_log[thread_A].find(it->second) != locks_log[thread_A].end()
        && locks_log[thread_B].find(it->second) != locks_log[thread_B].end()) {
      for (it_A = locks_log[thread_A][it->second][LOCK].begin();
           it_A != locks_log[thread_A][it->second][LOCK].end();
           ++it_A) {
        for (it_B = locks_log[thread_B][it->second][LOCK].begin();
             it_B != locks_log[thread_B][it->second][LOCK].end();
             ++it_B) {
          graph.addPolyEdge(it_A->second,
                            it_B->first,
                            it_B->second,
                            it_A->first,
                            true);
        }
      }
    }
  }
}

void add_atomic_edge(map<int, event_t> event_list, map<int *, int> atomic_obj_list)
{
  map<int *, int>::iterator atomic_obj_it;
  map<int, event_t>::iterator event_it;

  //  if (atomic_edge_added)
  //    return;

  for (atomic_obj_it = atomic_obj_list.begin();
       atomic_obj_it != atomic_obj_list.end();
       ++atomic_obj_it) {
    bool store_flag = false;
    int store_idx;
    vector<vector<event_t> > atomic_event_pair;

    for (event_it = event_list.begin();
         event_it != event_list.end();
         ++event_it) {
      if (event_it->second.obj_id == atomic_obj_it->second) {
        if (event_it->second.action == ATOMIC_STORE) {
          store_idx = event_it->first;
          store_flag = true;
        }
        if (event_it->second.action == ATOMIC_LOAD) {
          if (store_flag == true) {
            vector<event_t> tmp_pair;
            tmp_pair.push_back(event_list[store_idx]);
            tmp_pair.push_back(event_it->second);
            if (tmp_pair[0].tid != tmp_pair[1].tid) {
              create_edge(tmp_pair[0], tmp_pair[1], ATOMIC);
            }
            atomic_event_pair.push_back(tmp_pair);
          }
        }
      }
    } // end_event_loop

    int i, j,
      size = atomic_event_pair.size();
    for (i = 0; i < size - 1; ++i) {
      for (j = i + 1; j < size; ++j) {
        if (atomic_event_pair[i][0].tid != atomic_event_pair[j][0].tid) {
          graph.addPolyEdge(atomic_event_pair[i][1].eid,
                            atomic_event_pair[j][0].eid,
                            atomic_event_pair[j][1].eid,
                            atomic_event_pair[i][0].eid,
                            true);
        }
      }
    }
  } // end_atomic_obj_loop
  //  atomic_edge_added = true;
}

void add_induced_edge(map<unsigned, vector<event_t> > thread_routine,
                      map<pthread_mutex_t *, int> mutex_list)
{
  map<pthread_mutex_t *, int>::iterator mutex_it;
  //  vector<edge_t>::iterator edges_it;
  map<unsigned, edge_t>::iterator edges_it;
  list<edge_t> worklist;
  /*
  for (edges_it = edges.begin(); edges_it != edges.end(); ++edges_it) {
    if (edges_it->second.type == SQTL_SEED)
      continue;
    worklist.push_back(edges_it->second);
  }
*/
  for (unsigned i = 0; i < edges.size(); ++i) {
    if (edges[i].type == SQTL_SEED)
      continue;
    worklist.push_back(edges[i]);
  }

  list<edge_t>::iterator list_it = worklist.begin();

  while (!worklist.empty()) {
    for (mutex_it = mutex_list.begin();
         mutex_it != mutex_list.end();
         ++mutex_it) {
      event_t tmp_target, tmp_source, tmp_acq, tmp_rel;
      if (lock_held(list_it->source, mutex_it->second)
          && lock_held(list_it->target, mutex_it->second)) {
        prop_hold = false;
        //          printf("Property does not hold!\n");
        return;
      }

      if (lock_held(list_it->source, mutex_it->second)) {
        tmp_target = find_last(LOCK, list_it->source, mutex_it->second);
        tmp_source = find_last(UNLOCK, list_it->target, mutex_it->second);
        if (tmp_target.eid != -1 && tmp_source.eid != -1) {
          create_edge(tmp_source, tmp_target, INDUCED);
          worklist.push_back(edges.back());
        }
      }

      if (lock_held(list_it->source, mutex_it->second)
          || lock_held(list_it->target, mutex_it->second)) {
        tmp_acq = find_last(LOCK, list_it->source, mutex_it->second);
        tmp_rel = find_first(UNLOCK, list_it->target, mutex_it->second);
        tmp_source = find_matching(tmp_acq, mutex_it->second);
        tmp_target = find_matching(tmp_rel, mutex_it->second);
        if (tmp_acq.eid != -1
            && tmp_rel.eid != -1
            && tmp_source.eid != -1
            && tmp_target.eid != -1) {
          create_edge(tmp_source, tmp_target, INDUCED);
          //find_last(LOCK, list_it->source, mutex_it->second);
          worklist.push_back(edges.back());
        }
      }
    } //end_iterating_all_locks
    list_it = worklist.erase(list_it);
  }
}

void create_edge(event_t source, event_t target, ucg_edge_t type)
{
  edge_t new_edge;
  new_edge.source = source;
  new_edge.target = target;
  new_edge.type = type;
  if (!ucg_edge_found(edges, new_edge)) {
    edges.push_back(new_edge);
    if (type == PROP_SEED) {
      prop_seed_edges.push_back(new_edge);
    }
    graph.addEdge(source.eid, target.eid, true);
  }
}

void remove_edge(event_t source, event_t target, ucg_edge_t type)
{
  for (vector<edge_t>::iterator it = edges.begin(); it != edges.end(); ++it) {
    if (it->source.eid == source.eid
        && it->target.eid == target.eid
        && it->type == type) {
      edges.erase(it);
      graph.removeEdge(source.eid, target.eid);
      return;
    }
  }
}
/*
bool find_edge(event_t source, event_t target)
{
  for (unsigned int i = 0; i < edges.size(); ++i) {
    if (edges[i].source.eid == source.eid
        && edges[i].target.eid == target.eid) {
      return true;
    }
  }
  return false;
}
*/
void restore_event_containers(vector<vector<event_t> > &event_containers)
{
  for (unsigned int i = 0; i < event_containers.size(); ++i) {
    if (!event_containers[i].empty())
      event_containers[i].clear();
  }

  if (!event_containers.empty())
    event_containers.clear();

}

bool lock_held(event_t event, int mutex_id)
{
  return event.locks_held.find(mutex_id) != event.locks_held.end();
}

event_t find_last(action_t action, event_t event, int mutex_id)
{
  map<int, int, less<int> >::iterator it;
  map<int, int, less<int> >::reverse_iterator rit;
  it = locks_log[event.tid][mutex_id][action].lower_bound(event.eid);
  event_t new_event = event_create();
  new_event.eid = -1;

  if (it == locks_log[event.tid][mutex_id][action].end()) {
    return new_event;
  }
  else {
    for (rit = (map<int, int, less<int> >::reverse_iterator)it;
         rit != locks_log[event.tid][mutex_id][action].rend();
         ++rit) {
      if (rit->first == event.eid) {
        continue;
      }
      else {
        return event_list[rit->first];
      }
    }
    return new_event;
  }
}

event_t find_first(action_t action, event_t event, int mutex_id)
{
  map<int, int, less<int> >::iterator it;
  it = locks_log[event.tid][mutex_id][action].upper_bound(event.eid);
  if (it != locks_log[event.tid][mutex_id][action].end()) {
    return event_list[it->first];
  }
  else {
    event_t new_event = event_create();
    new_event.eid = -1;
    return new_event;
  }
}

event_t find_matching(event_t event, int mutex_id)
{
  int eid = locks_log[event.tid][mutex_id][event.action][event.eid];
  return event_list[eid];
}

bool ucg_edge_found(vector<edge_t> edges, edge_t edge)
{
  for (vector<edge_t>::iterator it = edges.begin(); it != edges.end(); ++it) {
    if (it->source.eid == edge.source.eid
        && it->target.eid == edge.target.eid) {
      return true;
    }
  }
  return false;
}
