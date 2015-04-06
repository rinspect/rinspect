/*
 * This is a C program that implements the following Litmus test
 *http://www.cprover.org/wmm/esop13/x86_litmus//rfi004.litmus
 *
X86 rfi004
"PodRR Fre MFencedWR Fre PodWW Rfi"
Cycle=Rfi PodRR Fre MFencedWR Fre PodWW
Relax=Rfi
Safe=Fre PodWW PodRR MFencedWR
{
}
 P0          | P1          ;
 MOV [x],$1  | MOV [y],$1  ;
 MFENCE      | MOV [z],$1  ;
 MOV EAX,[y] | MOV EAX,[z] ;
             | MOV EBX,[x] ;
exists
(0:EAX=0 /\ 1:EAX=1 /\ 1:EBX=0)
 * TSO violation expected.
 *
 * PSO violation expected.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

long int  x, y, z;
int k;
void *P0(void *arg)
{
  long int EAX, EBX;
  x = 1;
  //fence
 __sync_fetch_and_add (&k,0);
  EAX = y; 
printf("\n %%%% (EAX1=%d) %%%%", EAX);
  return (void*)(EAX==0);
}

void *P1(void *arg)
{
  long int EAX, EBX;
  y = 1;
  z = 1;
  EAX = z;
  EBX = x;
  printf("\n %%%% (EAX1=%d, EBX1=%d) %%%%", EAX, EBX);
  return (void*)(EAX==1 && EBX==0);
}




int main(void) 
{
  pthread_t t0, t1, t2, t3;
  long int cond0, cond1, cond2, cond3;

  pthread_create(&t0, 0, P0, 0);
  pthread_create(&t1, 0, P1, 0);
 
  pthread_join(t0, (void**)&cond0);
  pthread_join(t1, (void**)&cond1);

  if ( cond0 &&  cond1) {
    printf("\n@@@CLAP: There is a SC violation! \n");
    printf("\033[1;31m SC Violation!!! \033[0m\n");
  }

  return 0;
}
