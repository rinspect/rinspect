#ifndef __INSPECTOR_MUTEX_H__
#define __INSPECOTR_MUTEX_H__

class InspectMutex
{
public:
  InspectMutex();
  ~InspectMutex();
  
public:
  bool available;
  vector<int>  waiting_list;
};




class InspectCond
{
public:
  InspectCond();
  ~InspectCond();
  
public:
  InspectMutex * mutex;
  vector<int> waiting_list;
};


#endif

