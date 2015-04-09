/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader
*/
//for bounded, it seems to have a problem, recheck it. 
// not stop when run under tso
#include <pthread.h>
#define assert(e) if (!(e)) ERROR: goto ERROR; 
#define N1 1
#define N2 1
#define N3 1
#define N4 1
int flag1 = 0, flag2 = 0; // integer flags 
int x; // boolean variable to test mutual exclusion

void *thr1() {
int n1=0;
int n2=0;
int n3=0;
int n4=0;	
  flag1 = 1;
  while (flag2 >= 3){if(n1++ > N1) break;} 
  flag1 = 3;
  if (flag2 == 1) {
    flag1 = 2;
    while (flag2 != 4){if(n2++ > N2) break;}
  }
  flag1 = 4;
  while (flag2 >= 2){if(n3++ >N3) break;}
  // begin critical section
  x = 0;
  assert(x<=0);
  // end critical section
  while (2 <= flag2 && flag2 <= 3){if(n4++ >N4) break;}
  flag1 = 0;
  return NULL;
}

void *thr2() {
int n1=0;
int n2=0;
int n3=0;
int n4=0;
  flag2 = 1;
  while (flag1 >= 3){if(n1++ >N1) break;}
  flag2 = 3;
  if (flag1 == 1) {
    flag2 = 2;
    while (flag1 != 4){if(n2++ >N2) break;}
  }
  flag2 = 4;
  while (flag1 >= 2){if(n3++ >N3) break;}
  // begin critical section
  x = 1;
  assert(x>=1);
  // end critical section
  while (2 <= flag1 && flag1 <= 3){if(n4++ >N4) break;}
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
