#include<stdio.h>
#include<stdlib.h>

#include "kd_tree.h"
#include "list.h"
#include "business.h"
#include "read.h"

#define NEWLINES "\r\n"
#define REQUIRED_ARGS 3
#define OUTFILE_INDEX 2
#define CSVFILE_INDEX 1
#define NOT_FOUND "NOTFOUND\n"

kd_node_t *free_node(kd_node_t *node, void *arg);
void *print_list(void *list, void *arg);
void *free_list2(void *list, void *arg);

int main(int argc, char **argv)
{
    char *line = NULL; 
    size_t line_size = 0; 
    double query[2];
    double radius;
    int num_comparisons = 0;
    ll_node_t *results = NULL;
    FILE *outfile;

    if(argc != REQUIRED_ARGS){
        fprintf(stderr, "Usage: ./map1 csv-file outfile\n");
        exit(EXIT_FAILURE);
    }

    /* Read in csv file */
    kd_node_t *tree = read_data(argv[CSVFILE_INDEX]);

    /* Open outfile for writing */
    outfile = fopen(argv[OUTFILE_INDEX], "w");
    assert(outfile != NULL);

    /* Read in search keys from stdin*/
    while(getline(&line, &line_size, stdin) != EOF &&
            sscanf(line, "%lf %lf %lf", &query[0], &query[1], &radius) == 3){
        struct print_arg args = {.query = line, .outfile = outfile};

        /* Remove any newlines at the end of the query */
        line[strcspn(line, NEWLINES)] = '\0';

        /* Search through k-d tree for nearest node */
        num_comparisons = radius_search(tree, query, radius, &results);

        /* Print out matching results */
        if(results != NULL){
            ll_map(results, print_list, &args);
        } else {
            fprintf(outfile, "%f %f %f-->"
                    NOT_FOUND, query[0], query[1], radius);
        }

        /* Print number of key comparisons */
        printf("%f %f %f--> %d\n", query[0], query[1], radius, num_comparisons);

        /* Free results list for next search */
        free_list(results);
        results = NULL;
    }

    /* Clean up */
    fclose(outfile);
    free(line);
    postorder_traverse(tree, free_node, NULL);
}

void *print_list(void *list, void *arg)
{
    ll_map(list, print_business, arg);
    return list;
}

kd_node_t *free_node(kd_node_t *node, void *arg)
{
    ll_map(node->record, free_business, NULL);
    free_list(node->record);
    free(node);
    return NULL;
}

