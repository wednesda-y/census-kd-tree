#include "kd_tree.h"

kd_node_t *kd_insert(kd_node_t *tree, void *data, double *key)
{
    int i;

    /* Base case: Tree is empty */
    if(tree == NULL){
        kd_node_t *new = (kd_node_t*) malloc(sizeof(kd_node_t));
        assert(new != NULL);

        /* Store key by value, not reference */
        for(i = 0; i < N_DIMENSIONS; i++){
            new->key[i] = key[i];
        }
        new->record= ll_insert(NULL, data);
        new->left = new->right = NULL;
        new->cmp_index = DEFAULT_CMP_INDEX;
        return new;
    }

    /* Inductive Step: Compare and insert into left or
     * right subtree */
    int cmp_index = tree->cmp_index;

    /* Case 1: Exact match */
    for(i = 0; i < N_DIMENSIONS && key[i] == tree->key[i]; i++);
    if(i == N_DIMENSIONS){
        tree->record = ll_insert(tree->record, data);
    }

    /* Case 2: Node goes left */
    else if(key[cmp_index] < tree->key[cmp_index]){
        tree->left = kd_insert(tree->left, data, key);
        tree->left->cmp_index = (tree->cmp_index + 1) % N_DIMENSIONS;
    } 
    /* Case 3: Node goes right */
    else{
        tree->right = kd_insert(tree->right, data, key);
        tree->right->cmp_index = (tree->cmp_index + 1) % N_DIMENSIONS;
    }

    return tree;
}

double dist(double *point_x, double *point_y)
{
    int i;
    double dist = 0.0;
    for(i = 0; i < N_DIMENSIONS; i++){
        dist += pow(point_x[i] - point_y[i], 2.0);
    }

    return sqrt(dist);
}

/* Returns node with key that is closest to the given query key.
 * Metric is Euclidean metric
 * Return value is number of key comparisons */
int nearest_node(kd_node_t *tree, kd_node_t **candidate, double *query)
{
    double candidate_dist;
    int key_comparisons = 0;

    /* Base case: Empty tree */ 
    if(tree == NULL){
        return key_comparisons;
    }

    /* Inductive Step */
    /* Check if we're closer to the query than the current candidate */
    if(*candidate == NULL){
        *candidate = tree;
    }
    candidate_dist = dist((*candidate)->key, query);
    if(dist(tree->key, query) < candidate_dist){
        *candidate = tree;
    }
    key_comparisons++;

    /* Search down one, or both of the branches depending on if
     * we're closer or not */
    int cmp_index = tree->cmp_index;
    if(fabs(query[cmp_index] - tree->key[cmp_index]) < candidate_dist){
        key_comparisons += nearest_node(tree->left, candidate, query);
        key_comparisons += nearest_node(tree->right, candidate, query);
    } else if(query[cmp_index] < tree->key[cmp_index]){
        key_comparisons += nearest_node(tree->left, candidate, query);
    } else {
        key_comparisons += nearest_node(tree->right, candidate, query);
    }

    return key_comparisons;
}

/* Return value is number of key comparisons */
int radius_search(kd_node_t *tree, double *query, double radius, 
                   ll_node_t **results)
{
    int key_comparisons = 0;

    /* Base case: empty tree */    
    if(tree == NULL){
        return key_comparisons;
    }

    /* Inductive Step: Traverse down the tree. */
    /* If current node is inside radius, add it to results list */
    if(dist(tree->key, query) < radius){
        *results = ll_insert(*results, tree->record);
    }
    key_comparisons++;

    int cmp_index = tree->cmp_index;
    /* Traverse down one, or both sides of tree */
    if(fabs(query[cmp_index] - tree->key[cmp_index]) < radius){
        key_comparisons += radius_search(tree->left, query, radius, results);
        key_comparisons += radius_search(tree->right, query, radius, results);
    } else if(query[cmp_index] < tree->key[cmp_index]){
        key_comparisons += radius_search(tree->left, query, radius, results);
    } else {
        key_comparisons += radius_search(tree->right, query, radius, results);
    }

    return key_comparisons;
}

void preorder_traverse(kd_node_t *tree, kd_node_t *(*visit)(kd_node_t *, void *), void *arg)
{
    /* Base case: empty tree */
    if(tree == NULL){
        return;
    }

    tree = visit(tree, arg);
    preorder_traverse(tree->left, visit, arg);
    preorder_traverse(tree->right, visit, arg);
}

void postorder_traverse(kd_node_t *tree, kd_node_t *(*visit)(kd_node_t *, void *), void *arg)
{
    /* Base case: empty tree */
    if(tree == NULL){
        return;
    }
    postorder_traverse(tree->left, visit, arg);
    postorder_traverse(tree->right, visit, arg);
    tree = visit(tree, arg);
}

