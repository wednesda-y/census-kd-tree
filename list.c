#include "list.h"

/* Creates a new node holding (*data), and inserts it at
 * start of list pointed to by (*list) */
ll_node_t *ll_insert(ll_node_t *list, void *data)
{    
    /* Create a new node */
    ll_node_t *new = (ll_node_t*) malloc(sizeof(ll_node_t));
    assert(new != NULL);

    /* Initialised node fields*/
    new->data = data;
    new->next = list;

    return new;
}

/* Deletes all instances of nodes containing (*data) from the list */
ll_node_t *ll_delete(ll_node_t *list, void *data)
{
    ll_node_t* current = list;
    ll_node_t* prev = NULL;
    
    /* Advance through the list, keeping track of the preceding node */
    while(current != NULL){
        /* We found a match */
        if(current->data == data){
            /* Case 1: We are at the start of the list */
            if(prev == NULL){
                prev = current;
                current = current->next;
                list = current;
                
                free(prev);
                prev = NULL;
            }
            /* Case 2: We are in the middle of the list */
            else{
                current = current->next;
                free(prev->next);
                prev->next = current;
            }
        }
        /* No match, continue through the list */
        else{
            current = current->next;
        }
    }
    return list;
}

/*
 * Searches through a list and find all nodes with data fields matching
 * the given comparison function and query. The pointer notd_t **results
 * is updated to point to a linked list containing all 
 * matching data points.
 *
 * The return value of the function is number of successful matches found.
 */
int ll_search(ll_node_t *list, int (*cmp)(void *, void *), void *query,
           ll_node_t **results)
{
   ll_node_t* current; 
   int num_matches = 0;

   /* Find and store matches into allocated region */
   for(current = list; current != NULL; current = current->next){
        if(!cmp(current->data, query)){
            *results = ll_insert(*results, current->data);
            num_matches++;
        }
   }

   return num_matches;
}

/* Iterates through the list and applies the function func
 * to the data fields of all nodes in the list 
 * The function func accepts two arguments where the first argument
 * is the data field, the second argument is a pointer to any 
 * paramters required.
 * */
ll_node_t *ll_map(ll_node_t *list, void * (*func)(void *, void *), void *arg)
{
    for(ll_node_t *curr = list; curr != NULL; curr = curr->next){
        curr->data = func(curr->data, arg);
    }
    return list;
}

/* Frees all memory allocated to nodes of a given list */
void free_list(ll_node_t *list)
{
    ll_node_t *prev = NULL;
    ll_node_t *current = list;

    /* Iterate through list and free nodes one by one */
    while(current != NULL){
        prev = current;
        current = current->next;
        free(prev);
    }
}
