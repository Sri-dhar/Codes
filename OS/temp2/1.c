#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100

int numbers[MAX_SIZE];
int n;

void merge(int left[], int left_size, int right[], int right_size) {
    int i = 0, j = 0, k = 0;
    int temp[left_size + right_size]; // Create a temporary array to store the merged result

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            temp[k++] = left[i++];
        } else {
            temp[k++] = right[j++];
        }
    }
    while (i < left_size) {
        temp[k++] = left[i++];
    }
    while (j < right_size) {
        temp[k++] = right[j++];
    }

    // Copy the merged result back to the original array
    for (int m = 0; m < left_size + right_size; m++) {
        numbers[m] = temp[m];
    }
}

void merge_sort(int arr[], int size) {
    if (size > 1) {
        int mid = size / 2;
        int left[mid];
        int right[size - mid];

        for (int i = 0; i < mid; i++) {
            left[i] = arr[i];
        }
        for (int i = mid; i < size; i++) {
            right[i - mid] = arr[i];
        }

        merge_sort(left, mid);
        merge_sort(right, size - mid);

        merge(left, mid, right, size - mid);
    }
}

void *sort_thread(void *arg) {
    int *half = (int *)arg;
    int size = n / 2;
    if (half == numbers) {
        size = n - size;
    }
    merge_sort(half, size);
    pthread_exit(NULL);
}

int main() {
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, sort_thread, (void *)numbers);
    pthread_create(&thread2, NULL, sort_thread, (void *)(numbers + n / 2));

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    merge(numbers, n / 2, numbers + n / 2, n - n / 2);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
