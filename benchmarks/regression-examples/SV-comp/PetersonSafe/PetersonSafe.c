#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#define assert(e) if (!(e)) ERROR: goto ERROR;
#define COUNT 1
int flag1 = 0, flag2 = 0; // boolean flags
int turn=0;; // integer variable to hold the ID of the thread whose turn is it
int x=0; // boolean variable to test mutual exclusion

void *thr1() {
    int count;
    int local;
    local=0;
    count=0;
    flag1 = 1;
    turn = 1;

  while (flag2==1 && turn==1) {
      if (count++ >= COUNT) break;
  }
 
  // begin: critical section
  x = 0;
  //assert(x <= 0);
  // end: critical section
  flag1 = 0;
  return NULL;
}

void *thr2() {
    int count=0;
    int local;
    local=0;
  flag2 = 1;
  turn = 0;
  while (flag1==1 && turn==0) { 
	if(count++ >= COUNT) break;
  }
  // begin: critical section
  x = 1;
  //assert(x >= 1);
  // end: critical section
  flag2 = 0;

  return NULL;
}
  
int main() {
  pthread_t t1, t2;
  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  return 0;
}
