/*
 * This is a C program that implements the following Litmus test
 *http://www.cprover.org/wmm/esop13/x86_litmus//thin002.litmus
 *
X86 thin002
"PodRW Rfe PodRW Rfe PodRW Rfe PodRW Rfe"
Cycle=Rfe PodRW Rfe PodRW Rfe PodRW Rfe PodRW
Relax=
Safe=Rfe PodRW
{
}
 P0          | P1          | P2          | P3          ;
 MOV EAX,[a] | MOV EAX,[x] | MOV EAX,[y] | MOV EAX,[z] ;
 MOV [x],$1  | MOV [y],$1  | MOV [z],$1  | MOV [a],$1  ;
exists
(0:EAX=1 /\ 1:EAX=1 /\ 2:EAX=1 /\ 3:EAX=1)
 * TSO OK.
 *
 * PSO OK.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

long int a, x, y, z;

void *P0(void *arg)
{
  long int EAX, EBX;
  EAX = a;
  x = 1;
  printf("\n %%%% (EAX=%d) %%%%", EAX);
  return (void*)(EAX==1);
}

void *P1(void *arg)
{
  long int EAX, EBX;
  EAX = x;
  y = 1;
  printf("\n %%%% (EAX=%d) %%%%", EAX);
  return (void*)(EAX==1);
}
void *P2(void *arg)
{
 long int EAX, EBX;
  EAX = y;
  z = 1;
  printf("\n %%%% (EAX=%d) %%%%", EAX);
  return (void*)(EAX==1);
}

void *P3(void *arg)
{
  long int EAX, EBX;
  EAX = z;
  a = 1;
  printf("\n %%%% (EAX=%d) %%%%", EAX);
  return (void*)(EAX==1);
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

  if ( cond0 &&  cond1 && cond2 && cond3) {
    printf("\n@@@CLAP: There is a SC violation! \n");
    printf("\033[1;31m SC Violation!!! \033[0m\n");
  }

  return 0;
}
