#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *task(void *_args) { return NULL; }

int main(void) {
  pthread_t threads[2];

  pthread_create(&threads[0], NULL, task, NULL);
  pthread_create(&threads[1], NULL, task, NULL);
  pthread_join(threads[0], NULL); // Aguarda a finalização das threads
  pthread_join(threads[1], NULL);
}
