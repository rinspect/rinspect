/*
 * This is a C program that implements the following Litmus test
 * http://www.cprover.org/wmm/esop13/x86_litmus//safe022.litmus
 *

X86 safe022
"Fre PodWW Rfe PodRR"
Cycle=Rfe PodRR Fre PodWW
Relax=
Safe=Rfe Fre PodWW PodRR
{
}
 P0         | P1          ;
 MOV [y],$1 | MOV EAX,[x] ;
 MOV [x],$1 | MOV EBX,[y] ;
exists
(1:EAX=1 /\ 1:EBX=0)

 * TSO violation not expected.
 *
 * PSO violation not expected.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

long int x, y, z;

void MFENCE(){}

void *P0(void *arg)
{
  long int EAX, EBX;
  y = 1;
  x = 1;
  return (void*)1;
}

void *P1(void *arg)
{
  long int EAX, EBX;
  EAX = x;
  EBX = y;
  printf("\n (EAX1=%d, EBX1=%d) \n", EAX, EBX); 
  return (void*)(EAX==1 && EBX==0);
}

int main(void) 
{
  pthread_t t0, t1, t2, t3;
  long int cond0, cond1, cond2, cond3;

  x = y = 0;

  pthread_create(&t0, 0, P0, 0);
  pthread_create(&t1, 0, P1, 0);

  pthread_join(t0, (void**)&cond0);
  pthread_join(t1, (void**)&cond1);

  //assert( ! (cond1) );
  if ( cond1 ) {
    printf("\n@@@CLAP: There is a SC violation! \n");
    printf("\033[1;31m SC Violation!!! \033[0m\n");
  }

  return 0;
}
