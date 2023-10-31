#include <stdio.h>
#include <stdlib.h>
#include "list_node.h"


struct person_t* person_create(const char *name, int born_year)
{
    struct person_t *pers = malloc(sizeof(struct person_t));

    if (pers)
    {
        pers->name = name;
        pers->born_year = born_year;
        pers->next = NULL;        
    }
        
    return pers;
}


void person_free(struct person_t *pers)
{
    free(pers);
}


void person_print(struct person_t *pers, void *arg)
{
    const char *fmt = arg;

    printf(fmt, pers->name, pers->born_year);
}


void person_count(struct person_t *pers, void *arg)
{
    int *counter = arg;

    (*counter)++;
}
