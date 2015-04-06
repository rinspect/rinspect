#include <pthread.h>
#include <assert.h>

int a;

void *thread_1(void *unused) {
    __sync_add_and_fetch(&a, 1);

    return NULL;
}

int main() {
    a = 0;

    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread_1, NULL);
    pthread_create(&t2, NULL, thread_1, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    assert(a == 2);

    return 0;
}
