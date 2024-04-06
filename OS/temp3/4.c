#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

#define MAX_LENGTH 100

char Input[MAX_LENGTH];
char Output[MAX_LENGTH];
int currentIndex = 0;
int n;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* convertCase(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (currentIndex >= MAX_LENGTH || Input[currentIndex] == '\0') {
            pthread_mutex_unlock(&mutex);
            break;
        }
        char letter = Input[currentIndex];
        currentIndex++;
        pthread_mutex_unlock(&mutex);

        if (islower(letter)) {
            letter = toupper(letter);
        } else if (isupper(letter)) {
            letter = tolower(letter);
        }

        pthread_mutex_lock(&mutex);
        Output[currentIndex - 1] = letter;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    printf("Enter a sentence: ");
    fgets(Input, MAX_LENGTH, stdin);

    printf("Enter the number of threads: ");
    scanf("%d", &n);

    pthread_t threads[n];

    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, convertCase, NULL);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Converted sentence: %s\n", Output);

    return 0;
}
