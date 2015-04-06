#include <pthread.h>
#include <assert.h>

int isIdling = 0;
int hasWork = 0;
int __unbuffered_condVariable = 0;
/*
#define obtain_lock(c) \
{ \
  __CPROVER_atomic_begin(); \
  __CPROVER_assume(c==0 || c==2); \
  ++c; \
  __CPROVER_atomic_end(); \
}
#define release_lock(c) c=0

#define Wait(c) \
{ \
  __CPROVER_atomic_begin(); \
  __CPROVER_assume(c==1); \
  c=2; \
  __CPROVER_atomic_end(); \
  __CPROVER_assume(c==4); \
  __CPROVER_assume(c==0); \
  c=1; \
}
#define Pulse(c) \
{ \
  __CPROVER_assume(c==2); \
  c=4; \
}

*/
//  __sync_add_and_fetch(&(c),1);			
#define obtain_lock(c) \
{ \
    if((c==0) ||(c==2))					\
	c=1; \
}
#define release_lock(c) c=0
// __sync_bool_compare_and_swap((&(c)),1,2);	
#define Wait(c) \
{ \
if(c==1)\
    c=2; \
if(c==4 && c==0)\
  c=1; \
}
#define Pulse(c) \
{ \
if(c==2)\
  c=4; \
}

int dummy; void MFENCE(){ __sync_fetch_and_add (&dummy,0);}
// Consumer
void * BlockOnIdle(void * arg)
{
    obtain_lock(__unbuffered_condVariable);
    isIdling = 1;
    //fence;
    MFENCE();
    if(!hasWork)
	Wait(__unbuffered_condVariable);
    isIdling = 0;
    release_lock(__unbuffered_condVariable);
}

_Bool __unbuffered_prod_done=0;

// Producer
void * NotifyPotentialWork(void * arg)
{
    hasWork = 1;
    //fence;
    MFENCE();
    if(isIdling)
    {
	obtain_lock(__unbuffered_condVariable);
	Pulse(__unbuffered_condVariable);
	release_lock(__unbuffered_condVariable);
    }
    __unbuffered_prod_done=1;
}



int main()
{

    pthread_t t1, t2;

    pthread_create(&t1, NULL, BlockOnIdle, NULL);
    pthread_create(&t2, NULL, NotifyPotentialWork, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    assert(!__unbuffered_prod_done || __unbuffered_condVariable != 2);
}
