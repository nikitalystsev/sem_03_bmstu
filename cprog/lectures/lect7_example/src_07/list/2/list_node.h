#ifndef __LIST_NODE_H__

#define __LIST_NODE_H__


typedef struct person_t person_t; 


struct person_t
{
    const char *name;
    int born_year;

    person_t *next;
};


person_t* person_create(const char *name, int born_year);


void person_free(person_t *pers);


void person_print(person_t *pers, void *arg);


void person_count(person_t *pers, void *arg);


#endif	// #ifndef __LIST_NODE_H__
