#include <pthread.h>
#include <assert.h>

#define COUNT1  1
#define COUNT2  1
#define COUNT3  1

int flag[3];
int turn=0;
int x=0;
//int error = 0;

void* process1(void* tid)
{
    int i = (int) tid;
    int _flag;
    int _turn;

    int count1;
    int count2;
    int count3;

    _flag=0;
    _turn=0;
    count1 = 0;
    count2 = 0; 
    count3=0;
    while(1) {   
	if (count1++ >= COUNT1) break;
        
    L2:
	if (count2++ >= COUNT2) break;
        flag[i] = 1;
	_turn = turn;
        //fence
	while(_turn != i){
            if(count3++ >= COUNT3) break;
	    _flag = flag[ _turn ];
	    if(_flag == 0)
		turn = i;
	    _turn = turn;
	}
	flag[i] = 2;
        //fence
	_flag = flag[3-i];
	if(_flag == 2)
	    goto L2;
        //CS starts
	x=1;
	//if(x>1) printf("error");
        //CS ends
        flag[i] = 0;
    }
    return 0;
}


void* process2(void* tid)
{
    int i = (int) tid;
    int _flag;
    int _turn;

    int count1;
    int count2;
    int count3;

    _flag=0;
    _turn=0;
    count1 = 0;
    while(1) {   
	if (count1++ >= COUNT1) break;
        count2 = 0;  
    L2:
	if (count2++ >= COUNT2) break;
        flag[i] = 1;
	_turn = turn;
        //fence
        count3=0;
	while(_turn != i){
            if(count3++ >= COUNT3) break;
	    _flag = flag[ _turn ];
	    if(_flag == 0)
		turn = i;
	    _turn = turn;
	}
	flag[i] = 2;
        //fence
	_flag = flag[3-i];
	if(_flag == 2)
	    goto L2;
        //CS starts
       	x=2;
	//if(x<2) printf("error");
        //CS ends
        flag[i] = 0;
    }
    return 0;
}


int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, 0, process1, (void*)1);
    pthread_create(&t2, 0, process2, (void*)2);

    //waiting for the two threads to finish ...

    pthread_join(t1, 0);
    pthread_join(t2, 0);


    return 0;
}

