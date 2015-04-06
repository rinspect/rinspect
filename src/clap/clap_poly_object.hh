#ifndef __CLAP_POLY_OBJECT_HH__
#define __CLAP_POLY_OBJECT_HH__

#include "clap_event.hh"

#include <vector>
#include <cstring> 
#include <cassert>
#include <string> 
#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class PolyEventPair
{
public:
  PolyEventPair(PolyEvent* fst, PolyEvent* snd) { first = fst; second = snd; }
  string toString();

public:
  PolyEvent *first;
  PolyEvent *second;
};


class PolyThread 
{
public: 
  PolyThread(int tid) { id = tid;  entry = NULL; exit = NULL; }
  string toString();

public: 
  int id;
  PolyEvent *entry;
  PolyEvent *exit;
};

class PolyMutex
{
public: 
  PolyMutex(int mid) { id = mid; }
  string toString();

public:
  int id;
  vector<PolyEventPair> acq_rel_pairs;
};

class PolyCondVar
{
public: 
  PolyCondVar(int cid) { id = cid; }
  string toString();

public:
  int id;
  vector<PolyEventPair> signal_wait_pairs;
};

class PolyObject
{
public: 
  PolyObject(int oid) { id = oid; }
  string toString();

public:
  int id;
  vector<PolyEventPair> write_read_pairs;
  vector<PolyEvent*>    write_evs;
  vector<PolyEvent*>    all_evs;
  //vector<PolyEvent*>    read_evs;
};

#endif
