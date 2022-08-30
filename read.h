#ifndef READ_H_INCLUDED
#define READ_H_INCLUDED

#include "kd_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "business.h"

#define DATA_DELIM ',' 
#define COMMA_ESCAPE '"'
#define COMMA_ESCAPE_STR "\""

/* Breaks a csv line into a sequence of tokens */
char *tokenize_csv(char *line, char delim);

/* Reads a csv file and constructs a linked list
 * of businesses */
kd_node_t *read_data(char *filename);

#endif
