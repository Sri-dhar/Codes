#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 10
#define N 9999999999

// Shared data
long long result = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function executed by each thread
void* partial_sum(void* arg) {
    long long thread_id = (long long)arg;
    long long start = (thread_id * N) / NUM_THREADS + 1;
    long long end = ((thread_id + 1) * N) / NUM_THREADS;

    long long partial_result = 0;

    for (long long i = start; i <= end; ++i) {
        partial_result += i;
    }

    // Acquire the mutex before updating the shared result variable
    pthread_mutex_lock(&mutex);
    result += partial_result;
    // Release the mutex after updating the shared result variable
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    // Without threads
    clock_t start_time = clock();

    for (long long i = 1; i <= N; ++i) {
        result += i;
    }

    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Without threads: Sum = %lld, Time taken: %f seconds\n", result, time_taken);

    // Reset the result for the threaded version
    result = 0;

    // With threads
    pthread_t threads[NUM_THREADS];

    start_time = clock();

    // Create threads
    for (long long i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, partial_sum, (void*)i) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    // Wait for threads to finish
    for (long long i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return 1;
        }
    }

    end_time = clock();
    time_taken = ((double)(end_time - start_time)) / (CLOCKS_PER_SEC*NUM_THREADS);

    printf("With threads: Sum = %lld, Time taken: %f seconds\n", result, time_taken);

    return 0;
}
