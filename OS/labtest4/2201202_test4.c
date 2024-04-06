#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1000

char input[MAX_INPUT_LENGTH];
char intermediate[MAX_INPUT_LENGTH];
char output[MAX_INPUT_LENGTH];

int GLOBAL_THREAD_COUNT;
pthread_mutex_t lock;

char caseFlipper(char c)
{
    if (isupper(c))
        return tolower(c);
    else
        return toupper(c);
}

int globalCounter = 0;

void *convert(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        if (globalCounter >= strlen(input))
        {
            pthread_mutex_unlock(&lock);
            break;
        }
        printf("Thread No. %ld is getting called \n", (long)arg + 1);
        intermediate[globalCounter] = caseFlipper(input[globalCounter]);
        output[globalCounter] = caseFlipper(input[globalCounter]);
        globalCounter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    char* input_t = (char*) calloc(sizeof(char),1000);
    char* output_t = (char*) calloc(sizeof(char),1000);

    printf("Enter a sentence: ");
    fgets(input, 1000, stdin);

    int n;
    printf("Enter the number of threads: ");
    scanf("%d", &n);

    GLOBAL_THREAD_COUNT = n;

    pthread_t pthread_arr[n];

    for (long i = 0; i < n; i++)
    {
        pthread_create(&pthread_arr[i], NULL, convert, (void *)i);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(pthread_arr[i], NULL);
    }

    printf("\nThe FINAL OUTPUT IS : \n");
    puts(output);

    fflush(stdin);
    free(input_t);
    free(output_t);
    pthread_mutex_destroy(&lock);

    return 0;
}

// test input
// Hello How Are You I Am Fine What About You Doing Good 