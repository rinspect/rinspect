#include <pthread.h>
#include <assert.h>

#define COUNT1  1
#define COUNT2  1
#define COUNT3  1

int flag[2];
int sens=0;
int cnt=2;

void* process0(void* tid)
{
   int i = (int) tid;
   int _cnt;
   int _sens;
   int _rel;
   int count1;
   int count2;

    count1 = 0;
    count2 = 0; 
    _cnt=0;
    _sens=0;
    _rel=0;

    while(1) {
	if (count1++ >= COUNT1) break;   	            
        _sens=sens;
	_cnt=cnt;
	//arw(cnt,_cnt,_cnt-1)
	__sync_val_compare_and_swap(&cnt,_cnt,_cnt-1);
	if(_cnt==1){
	    cnt=2;
	    sens=!_sens;
	}
	else{
	    do{
		if (count2++ >= COUNT2) break;
		_rel=sens;
	    }while(_rel == _sens);
	}       
    }
    return 0;
}



int main(void)
{
    pthread_t t0, t1;

    pthread_create(&t0, 0, process0, (void*)0);
    pthread_create(&t1, 0, process0, (void*)1);

    //waiting for the two threads to finish ...

    pthread_join(t0, 0);
    pthread_join(t1, 0);
    return 0;
}

