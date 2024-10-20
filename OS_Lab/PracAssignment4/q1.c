#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void print_boxed_message(char* message) {
    printf("+----------------------------------+\n");
    printf("| %s\n", message);
    printf("+----------------------------------+\n");
}

void* producer(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        if(count == BUFFER_SIZE) {
            pthread_cond_wait(&cond, &mutex);
        }
        char message[50];
        sprintf(message, "Produced: %d, Buffer Size: %d", buffer[count], count);
        buffer[count++] = rand() % 100;
        print_boxed_message(message);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        for(int i=0;i<1e8;i++);
    }
}

void* consumer(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        if(count == 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        char message[50];
        sprintf(message, "Consumed: %d, Buffer Size: %d", buffer[count-1], count);
        printf("Consumed: %d\n", buffer[--count]);
        print_boxed_message(message);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        for(int i=0;i<1e9;i++);
    }
}
int main() {
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    return 0;
}