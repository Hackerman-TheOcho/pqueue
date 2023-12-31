#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pqueue.h"

#define TEST 10

int main()
{
	srand(time(NULL));
	printf("\ninsert %d random numbers with random priority\n", TEST);

	pqueue_t *queue = pqueue_create(TEST, free);
	if (!queue) {
		fprintf(stderr, "Could not create queue");
		return 1;
	}

	for (int i = 0; i < 5; i++) {
		char *key = malloc(sizeof(char));
		int priority = rand() % 128;
		*key = rand() % 26 + 64;

		pqueue_insert(queue, key, priority);
	}

	for (int i = 0; i < 5; i++) {
		char *key = malloc(sizeof(char));
		int priority = rand() % 128;
		*key = rand() % 26 + 64;
		fprintf(stderr, "%c", *key);
		pqueue_insert(queue, key, priority);
	}

	fprintf(stderr, "\n");

	while (!pqueue_empty(queue)) {
		pqueue_print(queue);
		int *key = pqueue_extract(queue);
		free(key);
	}

	pqueue_delete(queue);
}