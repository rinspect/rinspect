#include <pthread.h>
#include <assert.h>
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
int isIdling = 0;
int hasWork = 0;
int __unbuffered_condVariable = 0;


#define obtain_lock(c) \
{						\
    if((c==0) ||(c==2))				\
	__sync_add_and_fetch(&(c),1);		\
}
#define release_lock(c) c=0

#define Wait(c)						\
{							\
    if(c==1)						\
	__sync_bool_compare_and_swap((&(c)),1,2);	\
    if(c==4 )						\
	c=1;						\
}
#define Pulse(c)				\
{						\
    if(c==2)					\
	c=4;					\
}

// Consumer
void * BlockOnIdle(void * arg)
{
    //obtain_lock();
    if((__unbuffered_condVariable==0) ||(__unbuffered_condVariable==2))		//__sync_add_and_fetch(&(__unbuffered_condVariable),1);	 
    {__unbuffered_condVariable=1;  }
     
    isIdling = 1;
    if(!hasWork){
	//Wait(__unbuffered_condVariable);
	if(__unbuffered_condVariable==1)			       
	    //__sync_bool_compare_and_swap((&(__unbuffered_condVariable)),1,2);
	    __unbuffered_condVariable=2;
	if(__unbuffered_condVariable==4 )			       
	    __unbuffered_condVariable=1;
    }
    isIdling = 0;
    //release_lock(__unbuffered_condVariable);
    __unbuffered_condVariable=0;
}

int __unbuffered_prod_done=0;

// Producer
void * NotifyPotentialWork(void * arg)
{
    hasWork = 1;
    if(isIdling)
    {
	//obtain_lock(__unbuffered_condVariable);
	if((__unbuffered_condVariable==0) ||(__unbuffered_condVariable==2))			       
	    // __sync_add_and_fetch(&(__unbuffered_condVariable),1);
	{__unbuffered_condVariable=1;  }
	//Pulse(__unbuffered_condVariable);
	if(__unbuffered_condVariable==2) __unbuffered_condVariable=4;
	//release_lock(__unbuffered_condVariable);
	__unbuffered_condVariable=0;
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

    printf("prod is %d, var is %d \n",__unbuffered_prod_done ,__unbuffered_condVariable);
    assert(!__unbuffered_prod_done || __unbuffered_condVariable != 2);
}
