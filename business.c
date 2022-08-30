#include "business.h"

/* Formats and prints all fields of the given business struct */
void *print_business(void *business_, void * print_arg_)
{
    business_t *business =  (business_t*) business_;
    struct print_arg *args = (struct print_arg*) print_arg_;
    fprintf(args->outfile,
            "%s --> "
            "Census year: %d || "
            "Block ID: %d || "
            "Property ID: %d || "
            "Base property ID: %d || "
            "CLUE small area: %s || "
            "Trading Name: %s || "
            "Industry (ANZSIC4) code: %d || "
            "Industry (ANZSIC4) description: %s || "
            "x coordinate: %."COORD_PRECISION"f || "
            "y coordinate: %."COORD_PRECISION"f || "
            "Location: %s || \n",
            args->query,
            business->census_year,
            business->block_id,
            business->property_id,
            business->base_property_id,
            business->clue_small_area,
            business->trading_name,
            business->industry_code,
            business->industry_description,
            business->x_coord,
            business->y_coord,
            business->location);
    return business;
}

/* Free's all dynamic memory allocated to the 
 * fields of the given business struct, and the 
 * memory taken by the struct itself. */
void *free_business(void *business_, void *_)
{
    business_t *business = (business_t*) business_;

    /* The dynamic memory associated with a struct is
     * the memory allocated for the string fields, and
     * the memory to hold the struct itself */

    free(business->clue_small_area);
    business->clue_small_area = NULL;
    
    free(business->trading_name);
    business->trading_name = NULL;
    
    free(business->industry_description);
    business->industry_description = NULL;
    
    free(business->location);
    business->location = NULL;

    free(business);
    return NULL;
}

/* Compares businesses to a query by matching
 * trading name */
int cmp_trading_name(void * business_, void *query)
{
    business_t *business = (business_t*) business_;
    return strcmp(business->trading_name, query);
}

/* Creates a mapping from 
 * indexed tokens in a csv line to members of the business struct */
void parse_csv_token(business_t *business, char *token, int index)
{
    switch(index){
        case 0:
            business->census_year = atoi(token);
            break;
        case 1:
            business->block_id = atoi(token);
            break;
        case 2:
            business->property_id = atoi(token);
            break;
        case 3:
            business->base_property_id = atoi(token);
            break;
        case 4:
            business->clue_small_area = strdup(token);
            break;
        case 5:
            business->trading_name = strdup(token);
            break;
        case 6:
            business->industry_code = atoi(token);
            break;
        case 7:
            business->industry_description = strdup(token);
            break;
        case 8:
            business->x_coord = strtod(token, NULL);
            break;
        case 9:
            business->y_coord = strtod(token, NULL);
            break;
        case 10:
            business->location = strdup(token);
            break;
    }
}
