#ifndef _PQUEUE_H
#define _PQUEUE_H

#include <stdbool.h>

/**
 * @brief Struct that defines pointer to min-node, pthread lock,
 *        and del_f that knows how to delete custom void*
 */
typedef struct priority_queue pqueue_t;

/**
 * @brief User provided function to delete void* without memory leaks
 */
typedef void (*del_f)(void *data);

/**
 * @brief Creates a priority queue
 * 
 * Provides user with the option of a custom delete function pending what
 * datatype is stored within the queue.
 *  - Built-in datatype : NULL
 *  - "Simple" alloc'd  : free()
 *  - Custom Structure  : User Provided Function
 * 
 * The purpose of this option, is so the library does not need to know
 * anything about the user defined data structure to successfully delete
 *
 * @param capacity Maximum amount of elemnts that can be held in queue 
 * @param del Function to delete void*. Pass NULL if not wanted
 * @return pqueue_t* On success, NULL on failure
 */
pqueue_t *pqueue_create(int capacity, del_f del);

/**
 * @brief delete priority queue
 * 
 * @param pq priority queue to delete
 */
void pqueue_delete(pqueue_t *pq);

/**
 * @brief insert *void of specified priority into the queue
 * 
 * @param pq priority queue
 * @param item void* element to insert
 * @param priority of item to insert (0 is top)
 */
void pqueue_insert(pqueue_t *pq, void *item, int priority);

/**
 * @brief removes the lowest-priority value out of the queue
 * 
 * @param pq priority queue
 * @return address of stored value
 */
void *pqueue_extract(pqueue_t *pq);

/**
 * @brief Check if pqueue_t is empty
 * 
 * @param pq priority queue
 * @return true on empty, else false
 */
bool pqueue_empty(pqueue_t *pq);

/**
 * @brief Check if pqueue_t is full
 * 
 * @param pq priority queue
 * @return true on full, else false
 */
bool pqueue_full(pqueue_t *pq);

void pqueue_print(pqueue_t *pq);

#endif