#include <pthread.h>
#include <assert.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL ((void*)0)
#endif
#ifndef FENCE
#define FENCE(x) ((void)0)
#endif
#define N1 1
// c::thr1
// file peterson.c line 9
void * thr1(void * arg);
// c::thr2
// file peterson.c line 20
void * thr2(void * arg);


// c::flag1
// file peterson.c line 7
int flag1 = 0;
// c::flag2
// file peterson.c line 7
int flag2 = 0;
// c::turn
// file peterson.c line 5
int turn;
// c::x
// file peterson.c line 6
int x;

int main()
{
  pthread_t t1, t2;
  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
}


void * thr1(void * arg)
{
  int n1=0;
  flag1 = 1;
  turn = 1;

L1:
  if(n1++ >N1) goto L2;

  if(flag2 == 1 && turn == 1 )
    goto L1;

  x = 0;
  assert(x <= 0 && "VIOLATION");
L2:
  flag1 = 0;
}


void * thr2(void * arg)
{
  int n1=0;
  flag2 = 1;
  turn = 0;

L1:
  if(n1++ >N1) goto L2;
  
  if(flag1 == 1 && turn == 0)
	  goto L1;

  x = 1;
  assert(x >= 1 && "VIOLATION");
L2:
  flag2 = 0;
}

