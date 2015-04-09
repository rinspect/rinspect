/*X86 rfi001
"PodRR Fre PodWW Wse PodWW Rfi"
Cycle=Rfi PodRR Fre PodWW Wse PodWW
Relax=Rfi
Safe=Fre Wse PodWW PodRR
{
}
 P0         | P1          ;
 MOV [x],$1 | MOV [y],$2  ;
 MOV [y],$1 | MOV [z],$1  ;
            | MOV EAX,[z] ;
            | MOV EBX,[x] ;
exists
(y=2 /\ 1:EAX=1 /\ 1:EBX=0)*/

#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int x=0;
int y=0;
int z=0;
void* P0()
{ 
   x=1;  
   y=1;
   return 0;
}
void* P1()
{
    int EAX=0;
    int EBX=0;
    typedef struct tmp_ex{
    long int eax;
    long int ebx;
    }Values;

    Values *t=malloc(sizeof(Values));

    y=2;
    z=1;
    t->eax=z;
    t->ebx=x;
   
return (void*)&t;
}


int main(void)
{
    pthread_t t1, t2;//,t3;
    long int EAX;
    long int EBX;
 typedef struct tmp_ex{
    long int eax;
    long int ebx;
    }Values;

 Values *tmp;
    
    pthread_create(&t1, 0, P0, 0);
    pthread_create(&t2, 0, P1, 0);
  
    pthread_join(t1, 0);
    pthread_join(t2, &tmp);
    
    EAX=tmp->eax;
    EBX=tmp->ebx;
    if(y==2 && EAX==1 && EBX==0){
	 printf("\n@@@CLAP: There is a SC violation! \n");
	 printf("\033[1;31m  SC Violation!!!  \033[0m\n");
    }
    printf("\n%%%%%%%% EAX0=%ld, EBX=%ld,  %%%%%%%% \n", EAX,EBX);

    return 0;
}
