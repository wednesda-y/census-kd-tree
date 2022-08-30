#ifndef BUSINESS_H_INCLUDED
#define BUSINESS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define COORD_PRECISION "5"

/* Container struct for information associated
 * with a business */
typedef struct{
    int census_year;
    int block_id;
    int property_id;
    int base_property_id;
    char *clue_small_area;
    char *trading_name;
    int industry_code;
    char *industry_description;
    double x_coord;
    double y_coord;
    char *location;
} business_t;

struct print_arg{
    char *query;
    FILE *outfile;
};

/* Formats and prints all members of the given business struct */
void *print_business(void *business_, void *outfile_);

/* Frees all dynamic memory allocated to the business struct,
 * and the memory taken by the struct itself. */
void *free_business(void *business_, void *_);

/* Compares businesses to a query by matching trading names */
int cmp_trading_name(void *business_, void *query);

/* Creates a mapping from indexed tokens 
 * in a csv line to members of the business struct */
void parse_csv_token(business_t *business, char *token, int index);
#endif

