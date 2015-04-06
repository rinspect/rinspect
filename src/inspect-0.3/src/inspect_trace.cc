#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "scheduler.hh"
#include "inspect_event.hh"
#include <unistd.h>

using namespace std;

extern int verboseLevel;

void Scheduler::read_replay_file() {
	
  if (verboseLevel >= 2) {
    cout << "=============== start reading replay file ================" << endl;
  }

  assert( setting.replay_file != "");
  char *fileName = (char *) setting.replay_file.c_str();
  ifstream fromTrace(fileName);
  if (fromTrace.fail()) {
    cerr << "error: fail to open trace file '" << fileName << "'\n";
    return;
  }

  InspectEvent event;
  while (!fromTrace.eof()) {
    string s;
    fromTrace >> s;
    if (s == "<ExecutionStep") {
      string s1, s2, s3;
      fromTrace >> s1 >> s2 >> s3;
      assert( s1 == "id");
      assert( s2 == "=");
      //unsigned int size = atoi(s3.c_str() + 1);
      event.init();
    } else if (s == "</ExecutionStep>") {
      error_trace.push_back(event);
      event.init();
    } else if (s == "<threadId>") {
      string s1, s2;
      fromTrace >> s1 >> s2;
      assert( s2 == "</threadId>");
      event.thread_id = atoi(s1.c_str());
    } else if (s == "<eventType>") {
      string s1, s2;
      fromTrace >> s1 >> s2;
      assert( s2 == "</eventType>");
      event.type = string_to_event_type(s1);
    } else if (s == "<mutexId>") {
      string s1, s2;
      fromTrace >> s1 >> s2;
      assert( s2 == "</mutexId>");
      event.mutex_id = atoi(s1.c_str());
    } else if (s == "<rwlockId>") {
      string s1, s2;
      fromTrace >> s1 >> s2;
      assert( s2 == "</rwlockId>");
      event.rwlock_id = atoi(s1.c_str());
    } else if (s == "<objId>") {
      string s1, s2;
      fromTrace >> s1 >> s2;
      assert( s2 == "</objId>");
      event.obj_id = atoi(s1.c_str());
    } else if (s == "<semId>") {
      string s1, s2;
      fromTrace >> s1 >> s2;
      assert( s2 == "</semId>");
      event.sem_id = atoi(s1.c_str());
    } else if (s == "<condId>") {
      string s1, s2;
      fromTrace >> s1 >> s2;
      assert( s2 == "</condId>");
      event.cond_id = atoi(s1.c_str());
    } else if (s == "<childThreadId>") {
      string s1, s2;
      fromTrace >> s1 >> s2;
      assert( s2 == "</childThreadId>");
      event.child_id = atoi(s1.c_str());
    } else if (s == "<locInfoId>") {
      string s1, s2;
      fromTrace >> s1 >> s2;
      assert( s2 == "</locInfoId>");
    } else if (s == "<objVal>") {
      string s1, s2;
      fromTrace >> s1 >> s2;
      assert( s2 == "</objVal>");
      event.obj_value = atoi(s1.c_str());
    } else if (s != "") {
      cerr << "unknown token in trace '" << s << "'\n";
    }

  }



  if (verboseLevel >= 2) {
    for (unsigned int i = 0; i < error_trace.size(); i++) {
      cout << "read trace[" << i << "]: " << error_trace[i].toString()  << endl;
    }
    cout << "=============== end   reading replay file ================\n";
  }
}

