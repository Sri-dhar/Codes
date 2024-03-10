#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define K 2
#define N 3

int A[M][K] = {{1, 4}, {2, 5}, {3, 6}};
int B[K][N] = {{8, 7, 6}, {5, 4, 3}};
int C[M][N];
pthread_t threads[M*N];

struct v {
    int i;
    int j;
};

void* worker(void* arg) {
    struct v* data = arg;
    int sum = 0;
    for(int n = 0; n < K; n++) {
        sum += A[data->i][n] * B[n][data->j];
    }
    C[data->i][data->j] = sum;
    pthread_exit(0);
}

int main() {
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            struct v* data = (struct v*) malloc(sizeof(struct v));
            data->i = i;
            data->j = j;
            pthread_create(&threads[i*N + j], NULL, worker, data);
        }
    }
    for(int i = 0; i < M*N; i++) {
        pthread_join(threads[i], NULL);
    }
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}