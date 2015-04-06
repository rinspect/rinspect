#include <stdio.h>
#include <pthread.h>

int x=0, y=0, done=0;

void* thread1(void* arg)
{ 
    x=1;
    y=1;
    done=1;
    return NULL;
}


void* thread2(void* arg)
{
    if (done){
	if (x==0) printf("!!!!!!!!!!!!!!!ERROR*******************");
	int local=y;
    }
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


