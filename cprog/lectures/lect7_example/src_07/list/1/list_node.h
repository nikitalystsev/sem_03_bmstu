#ifndef __LIST_NODE_H__

#define __LIST_NODE_H__


struct person_t
{
    const char *name;
    int born_year;

    struct person_t *next;
};


struct person_t* person_create(const char *name, int born_year);


void person_free(struct person_t *pers);


void person_print(struct person_t *pers, void *arg);


void person_count(struct person_t *pers, void *arg);


#endif	// #ifndef __LIST_NODE_H__
