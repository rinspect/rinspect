#include <pthread.h>
#define assert(e) if (!(e)) ERROR: goto ERROR;
#define COUNT1 1
#define COUNT2 1

int flag1 = 0, flag2 = 0; // boolean flags
int turn; // integer variable to hold the ID of the thread whose turn is it
int x; // boolean variable to test mutual exclusion

void *thr1() {
  int count1=0;
  int count2=0;  
  int local=0;
  flag1 = 1;
  while (flag2 >= 1) {
      if(count1++ > COUNT1) break;
      if (turn != 0) {
	  flag1 = 0;
	  while (turn != 0) {
	      if(count2++ > COUNT2) break;
	  }
	 
	  flag1 = 1;
      }
  }
  // begin: critical section
  x = 0;
  //assert(x<=0);
  // end: critical section
  turn = 1;
  flag1 = 0;
  
}

void *thr2() {
    int count1=0;
    int count2=0;
    int local=0;
  flag2 = 1;
  while (flag1 >= 1) {
      if(count1++ > COUNT1)break;
    if (turn != 1) {
      flag2 = 0;
      while (turn != 1) {
	  if(count2++ > COUNT2) break;
      }
     
      flag2 = 1;
    }
  }
 
  // begin: critical section
  x = 1;
  //assert(x>=1);
  // end: critical section
  turn = 1;
  flag2 = 0;
 
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  return 0;
}
