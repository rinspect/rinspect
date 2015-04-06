#include <pthread.h>
#include <assert.h>

#define N1 1
#define N2 1
#define vars(i) \
int latch##i; \
int flag##i
typedef enum {false=0, true=1} bool;

//vars(1);
int latch1 = 1;
int flag1 = 1;
int latch2 = 0;
int flag2 = 0;
//vars(2);
//vars(3);
//vars(4);
//vars(5);
//vars(6);

bool __unbuffered_tmp2;
int dummy;
void MFENCE(){ __sync_fetch_and_add (&dummy,0);}

#define worker(i, n) \
void worker_##i() \
{ \
  _Bool llatch, lflag; \
  llatch = latch##i; \
  while(!llatch) { llatch = latch##i; } \
  for(;;) \
  { \
    llatch = latch##i; \
    lflag = flag##i; \
    assert(!llatch || lflag); \
    latch##i = 0; \
    lflag = flag##i; \
    if(lflag) \
    { \
      flag##i = 0; \
      flag##n = 1; \
      latch##n = 1; \
    } \
\
    llatch = latch##i; \
    while(!llatch) { llatch = latch##i; } \
  } \
\
}

void* worker_1(void* arg) 
{  
    //while(!latch1) {}
    int n1=0;int n2=0,n3=0;
    for(;;) 
    { 
	while(!latch1) {}//if(n1++>= N1)break;}
	//if(!latch1){	   
	//    break;
	//}
	//assert("in worker1" &&(!latch1 || flag1)); 	
	if(!latch1==0 && flag1==0) {printf("worker1"); return NULL;}
	latch1 = 0;
	if(flag1) 
	{ 
	    flag1 = 0; 
	    flag2 = 1;
	    latch2 = 1; 
	    
	} 
	if(n2++ >= N2)break;
	//while(!latch1) {} 
    } 
}

void* worker_2(void* arg)
{
  //while(!latch2) {}
    int n1=0;int n2=0,n3=0;
    for(;;)
    {
	while(!latch2) {}//if(n1++ >= N1)break;}
	//if(!latch2){ 
	//    break;
	//}
	//assert("in worker2" && ( !latch2 || flag2));
	if(!latch2==0 && flag2==0) {printf("worker2"); return NULL;}
	latch2 = 0;
	//fence;
	__unbuffered_tmp2 = latch2 ^ latch2; // dp
	if(flag2 | __unbuffered_tmp2)
	{
	    flag2 = 0;
	    flag1 = 1;
      
	    MFENCE();
	    latch1 = 1;
	}
	if(n2++ >= N2)break;
	//while(!latch2) {}
    }
}

//worker(1,2);
//worker(2,1);
//worker(2,3);
//worker(3,1);
/*
worker(3,4);
worker(4,5);
worker(5,6);
worker(6,1);
*/

int main()
{
    //flag1 = 1;
    //latch1 = 1;
    pthread_t t1, t2;

    pthread_create(&t1, NULL, worker_1, NULL);
    pthread_create(&t2, NULL, worker_2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

//__CPROVER_ASYNC_3: worker_3();
    /*
//__CPROVER_ASYNC_4: worker_4();
//__CPROVER_ASYNC_5: worker_5();
//__CPROVER_ASYNC_6: worker_6();
*/
    return 0;
}
