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
#define N2 1
void * thr1(void * arg);

void * thr2(void * arg);

int flag1 = 0;

int flag2 = 0;

int turn = 0;

int x;

int main()
{
  pthread_t t1, t2;
  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
}

// c::thr1
// file dekker.c line 10
void * thr1(void * arg)
{
  int n1=0;
  int n2=0;
  flag1 = 1;
  while(flag2 >= 1){
    if(n2++ > N2)break;
    if(!(turn == 0))
      {
        flag1 = 0;
        while(!(turn == 0)){if(n1++> N1) break;}
          
        flag1 = 1;
      }
  }	
  //x = 0;
  //assert(x <= 0);
  turn = 1;
  flag1 = 0;
}

// c::thr2
// file dekker.c line 27
void * thr2(void * arg)
{
int n1=0;
int n2=0;
  flag2 = 1;
  while(flag1 >= 1){
    if(n2++ > N2)break;
    if(!(turn == 1))
      {
        flag2 = 0;
        while(!(turn == 1)){if(n1++> N1) break;}
         
        flag2 = 1;
      }

  }
  //x = 1;
  //assert(x >= 1);
  turn = 1;
  flag2 = 0;
}

