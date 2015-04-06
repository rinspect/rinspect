#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

// the unique id of the given thread 'x', of type pthread_t
#define UTID(x)      unique_thread_get_tid(x)
// the unique id of the calling thread
#define UTID_self()  UTID(pthread_self())
// the unique id of the given object 'x', in the form of by a pointer
#define UOID(x)      unique_obj_get_id((char*)x) 


void unique_thread_add(pthread_t this_thr, pthread_t parent_thr);
int unique_thread_get_tid(pthread_t this_thr);
int unique_obj_get_id(char* ptr);
void remove_tid();
