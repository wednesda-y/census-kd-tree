#ifndef KD_TREE_DEFINED
#define KD_TREE_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "list.h"

#define N_DIMENSIONS 2
#define DEFAULT_CMP_INDEX 0

typedef struct kd_node{
    double key[N_DIMENSIONS];
    ll_node_t *record;
    struct kd_node *left;
    struct kd_node *right;
    int cmp_index;
} kd_node_t;

kd_node_t *kd_insert(kd_node_t *tree, void *data, double *key);
int nearest_node(kd_node_t *tree, kd_node_t **candidate, double *query);
int radius_search(kd_node_t *tree, double *query, double radius, 
                   ll_node_t **results);
double dist(double *point_x, double *point_y);

void preorder_traverse(kd_node_t *tree, kd_node_t *(*visit)(kd_node_t *, void *), void *arg);

void postorder_traverse(kd_node_t *tree, kd_node_t *(*visit)(kd_node_t *, void *), void *arg);

#endif
