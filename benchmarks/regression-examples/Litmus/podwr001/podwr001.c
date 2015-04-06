/*
 * This is a C program that implements the following Litmus test
 * http://www.cprover.org/wmm/esop13/x86_litmus//podwr001.litmus
 *

X86 podwr001
"Fre PodWR Fre PodWR Fre PodWR"
Cycle=Fre PodWR Fre PodWR Fre PodWR
Relax=PodWR
Safe=Fre
{
}
 P0          | P1          | P2          ;
 MOV [z],$1  | MOV [x],$1  | MOV [y],$1  ;
 MOV EAX,[x] | MOV EAX,[y] | MOV EAX,[z] ;
exists
(0:EAX=0 /\ 1:EAX=0 /\ 2:EAX=0)

*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

long int x, y, z;

void *P0(void *arg)
{
  long int EAX0;
  z = 1;
  EAX0 = x;
  return (void*)EAX0;
}

void *P1(void *arg)
{
  long int EAX1;
  x = 1;
  EAX1 = y;
  return (void*)EAX1;
}

void *P2(void *arg)
{
  long int EAX2;
  y = 1;
  EAX2 = z;
  return (void*)EAX2;
}

int main(void) 
{
  pthread_t t0, t1, t2;
  long int EAX0, EAX1, EAX2;

  pthread_create(&t0, 0, P0, 0);
  pthread_create(&t1, 0, P1, 0);
  pthread_create(&t2, 0, P2, 0);

  pthread_join(t0, (void**)&EAX0);
  pthread_join(t1, (void**)&EAX1);
  pthread_join(t2, (void**)&EAX2);

  //assert( ! (EAX0==0 && EAX1==0) );
  if (EAX0==0 && EAX1==0 && EAX2==0) {
    printf("@@@CLAP: There is a SC violation! \n");
    printf("\033[1;31m  SC Violation!!!  \033[0m\n");
  }
  printf("\n%%%%%%%% EAX0=%ld, EAX1=%ld, EAX2=%ld %%%%%%%% \n", EAX0,EAX1,EAX2);

  return 0;
}
