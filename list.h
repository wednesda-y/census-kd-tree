#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct node{
    void *data;
    struct node *next;
} ll_node_t;

/* Creates a new node holding (*data), and inserts it at
 * start of list pointed to by (*list) */
ll_node_t *ll_insert(ll_node_t *list, void *data);


/* Deletes all instances of nodes containing (*data) from the list */
ll_node_t *ll_delete(ll_node_t *list, void *data);

/* Searches through a list and find all nodes with data fields matching
 * the given comparison function and query. */ 
int ll_search(ll_node_t *list, int (*cmp)(void *, void *), void *query, 
           ll_node_t **results);

/* Iterates through the list and applies the function func
 * to the data fields of all nodes in the list  */
ll_node_t *ll_map(ll_node_t *list, void * (*func)(void *, void *), void *arg);

/* Frees all memory allocated to nodes of a given list */
void free_list(ll_node_t *list);

#endif


