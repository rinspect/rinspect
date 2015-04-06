/*rewrite from http://www.cprover.org/wmm/esop13/x86_litmus//rfi000.litmus
X86 rfi000
"PosRR Fre PodWW Wse PodWW Rfi"
Cycle=Rfi PosRR Fre PodWW Wse PodWW
Relax=Rfi
Safe=Fre Wse PosRR PodWW
{
}
 P0         | P1          ;
 MOV [y],$2 | MOV [x],$2  ;
 MOV [x],$1 | MOV [y],$1  ;
            | MOV EAX,[y] ;
            | MOV EBX,[y] ;
exists
(x=2 /\ y=2 /\ 1:EAX=1 /\ 1:EBX=1)
*/


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
long int x;
long int y;

void* P0()
{  
    long int EAX0;
   y=2;  
   x=1;
   //printf("EAX0 = %i\n",EAX0);
   return 0;
}
void* P1()
{
    long int EAX;
    long int EBX;
    typedef struct tmp_ex{
    long int eax;
    long int ebx;
    }Values;

    Values *t=malloc(sizeof(Values));

    x=2;
    y=1;
    
    t->eax=y;
    t->ebx=y;
   
    return t;
}


int main(void)
{
    pthread_t t1, t2;//,t3;
    long int EAX, EBX;
   
    typedef struct tmp_ex{
    long int eax;
    long int ebx;
    }Values;

    Values *tmp_num;

    pthread_create(&t1, 0, P0, 0);
    pthread_create(&t2, 0, P1, 0);
    //pthread_create(&t3, 0, process3, 0);
    //waiting for the two threads to finish ...

    pthread_join(t1, 0);
    pthread_join(t2, &tmp_num);
   
    EAX=tmp_num->eax;
    EBX=tmp_num->ebx;
    if(x==2 && y==2 && EAX==1 && EBX==1){
	 printf("@@@CLAP: There is a SC violation! \n");
	 printf("\033[1;31m  SC Violation!!!  \033[0m\n");
    }
    printf("\n%%%%%%%% EAX0=%ld, EBX=%ld,  %%%%%%%% \n", EAX,EBX);
    return 0;
}



