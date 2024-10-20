#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

#define MAX_CHARS 100

char Input[MAX_CHARS];
char Output[MAX_CHARS];
int thread_count;
int current_index = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *convert_case(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);
    if (current_index >= strlen(Input)) {
      pthread_mutex_unlock(&mutex);
      break;
    }
    int index = current_index++;
    char ch = Input[index];

    if (islower(ch)) {
      Output[index] = toupper(ch);
    } else if (isupper(ch)) {
      Output[index] = tolower(ch);
    } else {
      Output[index] = ch;
    }
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main() {
  printf("Enter a sentence (max %d characters): ", MAX_CHARS - 1);
  fgets(Input, MAX_CHARS, stdin);

  printf("Enter the number of threads: ");
  scanf("%d", &thread_count);

  pthread_t threads[thread_count];

  for (int i = 0; i < thread_count; i++) {
    if (pthread_create(&threads[i], NULL, convert_case, NULL) != 0) {
      perror("Failed to create thread");
      return 1;
    }
  }

  for (int i = 0; i < thread_count; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("Failed to join thread");
      return 1;
    }
  }

  printf("Converted sentence: %s\n", Output);

  pthread_mutex_destroy(&mutex);
  return 0;
}
