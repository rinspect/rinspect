/*
 * This is a C program that implements the following Litmus test
 * http://www.cprover.org/wmm/esop13/x86_litmus//podwr000.litmus
 *

 X86 podwr000
 "Fre PodWR Fre PodWR"
 Cycle=Fre PodWR Fre PodWR
 Relax=PodWR
 Safe=Fre
 {
 }
 P0          | P1          ;
 MOV [y],$1  | MOV [x],$1  ;
 MOV EAX,[x] | MOV EAX,[y] ;
 exists
 (0:EAX=0 /\ 1:EAX=0)

*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

long int x, y;

void *P0(void *arg)
{
  long int EAX0;
  y = 1;
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

int main(void) 
{
  pthread_t t0, t1;
  long int EAX0, EAX1;

  pthread_create(&t0, 0, P0, 0);
  pthread_create(&t1, 0, P1, 0);

  pthread_join(t0, (void**)&EAX0);
  pthread_join(t1, (void**)&EAX1);

  //assert( ! (EAX0==0 && EAX1==0) );
  if (EAX0==0 && EAX1==0) {
    printf("@@@CLAP: There is a SC violation !\n");
    printf("\033[1;31m  SC Violation!!!  \033[0m\n");
  }
  printf("\n%%%%%%%% EAX0=%ld, EAX1=%ld %%%%%%%% \n", EAX0, EAX1);

  return 0;
}
