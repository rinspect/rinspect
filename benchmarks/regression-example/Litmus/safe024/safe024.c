/*
 * This is a C program that implements the following Litmus test
 * http://www.cprover.org/wmm/esop13/x86_litmus//safe024.litmus
 *

X86 safe024
"Fre MFencedWR Fre PodWW Rfe PodRR"
Cycle=Rfe PodRR Fre MFencedWR Fre PodWW
Relax=
Safe=Rfe Fre PodWW PodRR MFencedWR
{
}
 P0          | P1         | P2          ;
 MOV [z],$1  | MOV [x],$1 | MOV EAX,[y] ;
 MFENCE      | MOV [y],$1 | MOV EBX,[z] ;
 MOV EAX,[x] |            |             ;
exists
(0:EAX=0 /\ 2:EAX=1 /\ 2:EBX=0)

 * TSO violation not expected.
 *
 * PSO violation not expected.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

long int x, y, z;

//void MFENCE(){}
int dummy; void MFENCE(){ __sync_fetch_and_add (&dummy,0);}


void *P0(void *arg)
{
  long int EAX, EBX;
  z = 1;
  MFENCE();
  EAX = x;
  printf("\n (EAX0=%d) \n", EAX); 
  return (void*)(EAX==0);
}

void *P1(void *arg)
{
  long int EAX, EBX;
  x = 1;
  y = 1;
  return (void*)1;
}

void *P2(void *arg)
{
  long int EAX, EBX;
  EAX = y;
  EBX = z;
  printf("\n (EAX2=%d, EBX2=%d) \n", EAX, EBX); 
  return (void*)(EAX==1 && EBX==0);
}

int main(void) 
{
  pthread_t t0, t1, t2, t3;
  long int cond0, cond1, cond2, cond3;

  x = y = z = 0;

  pthread_create(&t0, 0, P0, 0);
  pthread_create(&t1, 0, P1, 0);
  pthread_create(&t2, 0, P2, 0);

  pthread_join(t0, (void**)&cond0);
  pthread_join(t1, (void**)&cond1);
  pthread_join(t2, (void**)&cond2);

  //assert( ! (cond0 && cond2) );
  if ( cond0 && cond2 ) {
    printf("\n@@@CLAP: There is a SC violation! \n");
    printf("\033[1;31m SC Violation!!! \033[0m\n");
  }

  return 0;
}
