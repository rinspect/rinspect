
#include "clap_poly_object.hh"


string PolyEventPair::toString()
{
  stringstream ss;

  ss << " (e" << first->eid << ", e" << second->eid << ") ";

  return ss.str();
}


string PolyMutex::toString()
{
  stringstream ss;

  ss << " mutex_id= " << setw(4) << id;

  vector<PolyEventPair>::iterator it;
  for (it = acq_rel_pairs.begin(); it != acq_rel_pairs.end(); it++) {
    ss << it->toString();
  }

  return ss.str();
}



string PolyObject::toString()
{
  stringstream ss;

  ss << " obj_id= " << setw(4) << id;

  vector<PolyEventPair>::iterator it;
  for (it = write_read_pairs.begin(); it != write_read_pairs.end(); it++) {
    ss << it->toString();
  }

  return ss.str();
}

string PolyCondVar::toString()
{
  stringstream ss;

  ss << " cond_id= " << setw(4) << id;

  vector<PolyEventPair>::iterator it;
  for (it = signal_wait_pairs.begin(); it != signal_wait_pairs.end(); it++) {
    ss << it->toString();
  }

  return ss.str();
}

string PolyThread::toString()
{
  stringstream ss;

  ss << " thread_id= " << setw(4) << id;
  ss << " ( e" << entry->eid << ", e" << exit->eid << " ) ";

  return ss.str();
}
