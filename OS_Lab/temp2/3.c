#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100

// Structure to hold the arguments for each thread
typedef struct {
    int* arr;
    int start;
    int end;
} ThreadArgs;

// Function to sort a given array using bubble sort algorithm
void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Thread function to sort a given range of numbers
void* sortThread(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    bubbleSort(args->arr, args->end - args->start + 1);
    pthread_exit(NULL);
}

int main() {
    int size;
    int numbers[MAX_SIZE];

    printf("Enter the number of elements: ");
    scanf("%d", &size);

    if (size <= 0 || size > MAX_SIZE) {
        printf("Invalid size\n");
        return 1;
    }

    printf("Enter the elements: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &numbers[i]);
    }

    // Divide the array into two halves
    int mid = size / 2;

    // Create thread arguments for the first half
    ThreadArgs args1;
    args1.arr = numbers;
    args1.start = 0;
    args1.end = mid - 1;

    // Create thread arguments for the second half
    ThreadArgs args2;
    args2.arr = numbers;
    args2.start = mid;
    args2.end = size - 1;

    // Create two threads to sort the two halves
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, sortThread, (void*)&args1);
    pthread_create(&thread2, NULL, sortThread, (void*)&args2);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Merge the two sorted halves
    int merged[MAX_SIZE];
    int i = 0, j = mid, k = 0;
    while (i < mid && j < size) {
        if (numbers[i] <= numbers[j]) {
            merged[k++] = numbers[i++];
        } else {
            merged[k++] = numbers[j++];
        }
    }
    while (i < mid) {
        merged[k++] = numbers[i++];
    }
    while (j < size) {
        merged[k++] = numbers[j++];
    }

    // Display the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", merged[i]);
    }
    printf("\n");

    return 0;
}
