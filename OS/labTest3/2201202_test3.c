#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// using bubble sort for sorting the array
void bubble_sort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// custom sort calling function
void *sort(void *arg)
{
    int *arr = (int *)arg;
    int n = arr[0];
    bubble_sort(arr + 1, n);
    pthread_exit(NULL);
    // exiting thread
}

int main()
{
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    // Array creation
    int *arr = (int *)calloc(n + 1, sizeof(int));
    arr[0] = n;

    printf("Enter the elements of the array: ");
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Creating two halves of the array
    int *arr1 = (int *)calloc((n / 2) + 2, sizeof(int));
    int *arr2 = (int *)calloc((n - n / 2) + 1, sizeof(int));

    arr1[0] = n / 2;
    arr2[0] = n - n / 2;

    // Splitting the array
    for (int i = 1; i <= n; i++)
    {
        if (i <= n / 2)
        {
            arr1[i] = arr[i];
        }
        else
        {
            arr2[i - n / 2] = arr[i];
        }
    }

    // Creating two threads to sort the two halves
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, sort, (void *)arr1);
    pthread_create(&thread2, NULL, sort, (void *)arr2);

    // wating for the threads to complete their tasks
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // joining into the final array
    int i = 1, j = 1, k = 1;
    while (i <= n)
    {
        if (j <= n / 2 && (k > n - n / 2 || arr1[j] <= arr2[k]))
        {
            arr[i] = arr1[j];
            i++;
            j++;
        }
        else
        {
            arr[i] = arr2[k];
            i++;
            k++;
        }
    }

    printf("The final sorted array is: ");
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // freeing the arrays (dynamic memory allocation)
    free(arr);
    free(arr1);
    free(arr2);

    return 0;
}