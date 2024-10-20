#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

char Input[1000];
char Output[1000];
int n;

pthread_mutex_t mutex; 
int index = 0; 

char convertCase(char c) {
    if (isupper(c))
        return tolower(c);
    else
        return toupper(c);
}

void *threadFunction(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex); 
        if (index >= strlen(Input)) {
            pthread_mutex_unlock(&mutex); 
            break; 
        }
        char c = Input[index]; 
        Output[index] = convertCase(c); 
        index++; 
        pthread_mutex_unlock(&mutex); 
    }
    return NULL;
}

int main() {
    printf("Enter a sentence: ");
    fgets(Input, sizeof(Input), stdin); 
    printf("Enter the number of threads: ");
    scanf("%d", &n); 

    pthread_t threads[n]; 
    pthread_mutex_init(&mutex, NULL); 

    for (int i = 0; i < n; i++)
        pthread_create(&threads[i], NULL, threadFunction, NULL);

    for (int i = 0; i < n; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);

    printf("Converted sentence: %s", Output); 
    return 0;
}

//cla