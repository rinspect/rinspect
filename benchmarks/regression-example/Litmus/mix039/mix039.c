/*
 * This is a C program that implements the following Litmus test
 * http://www.cprover.org/wmm/esop13/x86_litmus//mix039.litmus
 *

X86 mix039
"Fre PodWR Fre PodWW Wse PodWR Fre PodWW Rfi PodRR"
Cycle=Rfi PodRR Fre PodWR Fre PodWW Wse PodWR Fre PodWW
Relax=[Rfi,PodRR] PodWR
Safe=Fre Wse PodWW
{
}
 P0          | P1         | P2          | P3          ;
 MOV [b],$1  | MOV [x],$1 | MOV [y],$2  | MOV [z],$1  ;
 MOV EAX,[x] | MOV [y],$1 | MOV EAX,[z] | MOV [a],$1  ;
             |            |             | MOV EAX,[a] ;
             |            |             | MOV EBX,[b] ;
exists
(y=2 /\ 0:EAX=0 /\ 2:EAX=0 /\ 3:EAX=1 /\ 3:EBX=0)

 * TSO violation expected.
 *
 * PSO violation expected.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

long int a, b, x, y, z;

void *P0(void *arg)
{
  long int EAX, EBX;
  b = 1;
  EAX = x;
  printf("\n %%%% (EAX0=%d) %%%%\n", EAX);
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
  y = 2;
  EAX = z;
  printf("\n %%%% (EAX2=%d) %%%%\n", EAX);
  return (void*)(EAX==0);
}

void *P3(void *arg)
{
  long int EAX, EBX;
  z = 1;
  a = 1;
  EAX = a;
  EBX = b;
  printf("\n %%%% (EAX3=%d, EBX3=%d) %%%%\n", EAX, EBX);
  return (void*)(EAX==1 && EBX==0);
}

int main(void) 
{
  pthread_t t0, t1, t2, t3;
  long int cond0, cond1, cond2, cond3;

  pthread_create(&t0, 0, P0, 0);
  pthread_create(&t1, 0, P1, 0);
  pthread_create(&t2, 0, P2, 0);
  pthread_create(&t3, 0, P3, 0);

  pthread_join(t0, (void**)&cond0);
  pthread_join(t1, (void**)&cond1);
  pthread_join(t2, (void**)&cond2);
  pthread_join(t3, (void**)&cond3);

  //assert( ! (y==2 && cond0 && cond2 && cond3) );
  if (y==2 && cond0 && cond2 && cond3) {
    printf("\n@@@CLAP: There is a SC violation! \n");
    printf("\033[1;31m SC Violation!!! \033[0m\n");
  }

  return 0;
}
