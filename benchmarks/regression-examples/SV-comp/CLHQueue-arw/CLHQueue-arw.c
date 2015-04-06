#include <pthread.h>
#include <assert.h>

#define COUNT1  1
#define COUNT2  2

int mem[2];
int lock=0;

void* process(void* tid)
{
    int _lock;
    int _p;
    int _i;
    int _mp;
    int count1;
    int count2;
    _i=0;
    _p=0;
    _mp=0;
    _lock=0;
    count1=0;
    count2=0;
    while(1) {
	if (count1++ >= COUNT1) break;
        mem[_i]= 1;
	_lock=lock;
        //arw(lock,_lock,_p)
	__sync_val_compare_and_swap(&lock,_lock,_p);
	_p=_lock;
	do{
	    if (count2++ >= COUNT2) break;
	    _mp=mem[_p];
	}while(_mp !=0);
	if(_mp==0){
	mem[_i] = 0;
	_i=_p;
	}
    }
    return 0;
}



int main(void)
{
    pthread_t t1, t0;

    pthread_create(&t0, 0, process, (void*)0);
    pthread_create(&t1, 0, process, (void*)1);

    //waiting for the two threads to finish ...

    pthread_join(t0, 0);
    pthread_join(t1, 0);


    return 0;
}

