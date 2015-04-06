#include <pthread.h>
#define assert(e) if (!(e)) ERROR: goto ERROR;
#define COUNT1 1
#define COUNT2 1
#define COUNT3 1
#define COUNT4 1

int x, y;
int b1, b2; // boolean flags
int X; // boolean variable to test mutual exclusion

void *thr1() {
    int count1;
    int count2;
    int count3;
    int count4;

    count1=0;
    count2=0;
    count3=0;
    count4=0;
  while (1) {
      if(count1++ >= COUNT1) break;
      b1 = 1;
      x = 1;
      if (y != 0) {
	  b1 = 0;
	  while (y != 0) {
	      if(count2++ >= COUNT2)break;
	  }
	 
	  continue;
      }
      y = 1;
      if (x != 1) {
	  b1 = 0;
	  while (b2 >= 1) {
	      if(count3++ >= COUNT3)break;
	  }
	
	  if (y != 1) {
	      while (y != 0) {
		  if(count4++ >= COUNT4) break;
	      }
	     
	      continue;
	  }
	 
      }
      break;
  }
  // begin: critical section
  X = 0;
  //assert(X <= 0);
  // end: critical section
  y = 0;
  b1 = 0;

}

void *thr2() {
    int count1;
    int count2;
    int count3;
    int count4;

    count1=0;
    count2=0;
    count3=0;
    count4=0;
    while (1) {
	if(count1++ >= COUNT1)break;
	b2 = 1;
	x = 2;
	if (y != 0) {
	    b2 = 0;
	    while (y != 0) {
		if(count2++ >= COUNT2) break;
	    }
	  
	    continue;
	}
	y = 2;
	if (x != 2) {
	    b2 = 0;
	    while (b1 >= 1) {
		if(count3++ >= COUNT3)break;
	    }
	   
	    if (y != 2) {
		while (y != 0) {
		    if(count4++ >= COUNT4) break;
		}
		   
		continue;
	    }
	    
	}
	break;
    }

    // begin: critical section
    X = 1;
    //assert(X >= 1);
    //if(X<1) printf("error");
    // end: critical section
    y = 0;
    b2 = 0;
   
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  return 0;
}
