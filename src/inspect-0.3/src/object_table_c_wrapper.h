#ifndef __Thread_OBJ_TABLE_C_WRAPPER_H__
#define __Thread_OBJ_TABLE_C_WRAPPER_H__

int lookup_obj_id(void*);
void register_obj(void*);
void remove_obj(void*);


int  lookup_mutex_id(void* mutex);
void register_mutex(void* mutex);
void remove_mutex(void* mutex);


int lookup_cond_id(void* cond);
void register_cond(void* cond);
void remove_cond(void* cond);


int  lookup_thread_id(void* tid);
void register_thread_id(void* tid);
void remove_thread_id(void* tid);

void register_socket(int tid);
void remove_socket(int tid);

#endif
