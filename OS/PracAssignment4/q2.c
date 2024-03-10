#include <pthread.h>
#include <stdio.h>

pthread_rwlock_t lock;
int shared = 0;

void* reader(void* arg) {
    while(1) {
        pthread_rwlock_rdlock(&lock);
        printf("Read: %d\n", shared);
        pthread_rwlock_unlock(&lock);
    }
}

void* writer(void* arg) {
    while(1) {
        pthread_rwlock_wrlock(&lock);
        shared = rand() % 100;
        printf("Wrote: %d\n", shared);
        pthread_rwlock_unlock(&lock);
    }
}

int main() {
    pthread_t r, w;
    pthread_rwlock_init(&lock, NULL);
    pthread_create(&r, NULL, reader, NULL);
    pthread_create(&w, NULL, writer, NULL);
    pthread_join(r, NULL);
    pthread_join(w, NULL);
    pthread_rwlock_destroy(&lock);
    return 0;
}