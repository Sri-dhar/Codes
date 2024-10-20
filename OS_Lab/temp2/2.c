#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100

struct ThreadArgs {
    int *arr;
    int start;
    int end;
};

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void *mergeSort(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    int *arr = args->arr;
    int start = args->start;
    int end = args->end;

    if (start < end) {
        int mid = start + (end - start) / 2;
        struct ThreadArgs args1 = {arr, start, mid};

        pthread_t tid1;
        pthread_create(&tid1, NULL, mergeSort, &args1);
        struct ThreadArgs args2 = {arr, mid + 1, end};

        pthread_t tid2;
        pthread_create(&tid2, NULL, mergeSort, &args2);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        merge(arr, start, mid, end);
    }
    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid input size.\n");
        return 1;
    }

    int arr[MAX_SIZE];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct ThreadArgs args = {arr, 0, n - 1};

    pthread_t tid;
    pthread_create(&tid, NULL, mergeSort, &args);
    pthread_join(tid, NULL);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
