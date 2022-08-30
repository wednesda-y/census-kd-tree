#include "read.h"

/* Reads data from csv file of business information 
 * and constructs an unsorted linked list to store the information.
 * Return value is a pointer to the created list.
 */
kd_node_t *read_data(char *filename)
{
    FILE *fp = fopen(filename, "r");
    assert(fp != NULL);

    char *line = NULL;
    size_t line_size = 0;
    kd_node_t *tree = NULL;
    int i;

    /* Ignore the first line, which has header information */
    getline(&line, &line_size, fp);

    /* Read through each line */
    while(getline(&line, &line_size, fp) != EOF){
        business_t *new = (business_t*) malloc(sizeof(business_t));
        assert(new != NULL);

        /* Parse line and build up the struct from the given data 
         * token by token. */
        char *token = tokenize_csv(line, DATA_DELIM);
        for(i = 0; token != NULL; i++, token = tokenize_csv(NULL, DATA_DELIM)){
            parse_csv_token(new, token, i);
        }
        //double key[2] = {new->x_coord, new->y_coord};
        double key[2];
        key[0] = new->x_coord;
        key[1] = new->y_coord;
        tree = kd_insert(tree, new, key);
    }

    free(line);
    fclose(fp);
    return tree;
}

/* Breaks a csv line into a sequence of zero or more
 * tokens. The tokens are deliminated by the character
 * specified in the delim argument, except in the case
 * where the delimiter is surrounded by the pre-defined escape
 * character.
 * 
 * The first call to tokenize_csv should pass in a pointer 
 * to the csv line. Subsequent calls acting on the same line should
 * pass in the NULL pointer. See strtok(3).
 *
 * Returns a null terminated string containing the next token
 * parsed from the csv line.
 */
char *tokenize_csv(char *line, char delim)
{
    /* Save a pointer to how far we have parsed in the current
     * line so far. */
    static char *token_start; 
    int i, in_quotes = 0;

    /* If line is not null, we are parsing a new line */
    if(line != NULL){
        token_start = line;
    }

    /* Traverse the line until we reach one of
     * (1): the end of the string or
     * (2a): the next delimiter AND
     * (2b): the current traversal point is not surrounded by escape chars. 
     */
    i = 0;
    while(token_start[i] != '\0' && (token_start[i] != delim || in_quotes)){
        if(token_start[i] == COMMA_ESCAPE){
            in_quotes = !in_quotes;
            
            /* If entering quotes, remove the quote */
            /* This acts as an increment on i, so we have to offset it */
            if(in_quotes){
                memmove(&token_start[i], &token_start[i + 1], 
                        strlen(token_start) - i);
                i--;
            }
        } 
        i++;
    }

    /* If the traversed token is empty, there are no more tokens
     * left, so return NULL */
    if(i == 0){
        return NULL;
    } 

    /* Otherwise, null terminate the current token and prepare to return it, 
     * storing the position to search from at the start of the next call. */
    char *token = token_start;
    if(token_start[i] != '\0'){
        token_start[i] = '\0';
        token_start = (token_start + i + 1);
    } else {
        token_start = (token_start + i);
    }
    
    /* Before returning the token, strip any trailing quotes from it */
    if(strrchr(token, COMMA_ESCAPE) != NULL){
        *strrchr(token, COMMA_ESCAPE)  = '\0';
    }
    
    return token;
}


