#include <stdio.h>
#include <stdlib.h>

#include "pqueue.h"

typedef struct pqueue_node {
	void *node;
	int priority;
} node_t;

struct priority_queue {
	del_f del;
	node_t *back;
	node_t *heap;
	int count;
	int capacity;
}; 

pqueue_t *pqueue_create(int capacity, del_f del)
{
	pqueue_t *pq = malloc(sizeof(pqueue_t));
	if (!pq) {
		fprintf(stderr, "cannot allocate priority queue");
		return NULL;
	}

	pq->heap = calloc(capacity, sizeof(node_t));
	if(!pq->heap) {
		fprintf(stderr, "Could not create heap. Try smaller.");
		free(pq);
		return NULL;
	}

	pq->count = 0;
	pq->del = del;
	pq->back = pq->heap;
	pq->capacity = capacity;

	return pq;
}

void pqueue_delete(pqueue_t *pq)
{
	if (!pq) {
		fprintf(stderr, "Error destroying priority queue");
		return;
	}

	if (!pqueue_empty(pq)) {
		node_t *temp = pq->heap;
		while (temp != pq->back) {
			pq->del(temp->node);
			temp->node = NULL;
			temp++;
		}
	}
	free(pq->heap);
	free(pq);
}

static void heap_up(int position, node_t *heap) 
{
	int parent = (position - 1) / 2;
	if (parent < 0) {
		return;
	}

	node_t temp;
	if (heap[parent].priority > heap[position].priority) {
		temp = heap[parent];
		heap[parent] = heap[position];
		heap[position] = temp;
		heap_up(parent, heap);
	}
}

void pqueue_insert(pqueue_t *pq, void *item, int priority)
{
	if (!pq || !pq->heap) {
		fprintf(stderr, "Cannot open priority queue");
		return;
	}

	if (pqueue_full(pq)) {
		fprintf(stderr, "Queue is full");
		return;
	}

	pq->heap[pq->count].node = item;
	pq->heap[pq->count].priority = priority;
	heap_up(pq->count, pq->heap);
	pq->back++;
	pq->count++;
}

static void heap_down(int position, int size, node_t *heap)
{
	// use after extraction to reoganize queue
	int l_child = 2 * position + 1;
	int r_child = 2 * position + 2;

	if (l_child >= size) {
		return;
	}

	int swap_idx = heap[l_child].priority < 
			heap[r_child].priority ? l_child : r_child;

	if (heap[position].priority > heap[swap_idx].priority) {
		node_t temp = heap[swap_idx];
		heap[swap_idx] = heap[position];
		heap[position] = temp;

		heap_down(swap_idx, size, heap);
	}
}

void *pqueue_extract(pqueue_t *pq)
{
	if (!pq || !pq->heap) {
		return NULL;
	}

	void *temp;

	if (pqueue_empty(pq)) {
		fprintf(stderr, "Could not extract, queue is empty");
		return NULL;
	}

	temp = pq->heap[0].node;
	pq->count--;
	pq->back--;
	pq->heap[0] = pq->heap[pq->count];
	heap_down(0, pq->count, pq->heap);

	return temp;
}

bool pqueue_empty(pqueue_t *pq)
{
	return !pq || pq->count == 0;
}

bool pqueue_full(pqueue_t *pq)
{
	return pq->capacity == pq->count;
}

void pqueue_print(pqueue_t *pq)
{
	node_t p = pq->heap[0];
	char *c = p.node;
	fprintf(stderr, "%d:%c\n", p.priority, *c);
}