#include <stdio.h>
#include <pthread.h>

int x=0, y=0;

void* thread1(void* arg)
{ 
    x=1;
    int local1=y;
    printf(">>>>>>>>>> local1= %d\n",local1);
    return NULL;
}


void* thread2(void* arg)
{ 
    y=1;
    int local2=x;
    printf(">>>>>>>>> local2= %d\n", local2);
    return NULL;
}


int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}


