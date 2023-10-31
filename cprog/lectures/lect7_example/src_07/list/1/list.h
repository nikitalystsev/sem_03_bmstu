#ifndef __LIST_H__

#define __LIST_H__


#include "list_node.h"


typedef void (*ptr_action_t)(struct person_t*, void*);


struct person_t* list_add_front(struct person_t *head, struct person_t *pers);


void list_add_front_usual(struct person_t **head, struct person_t *pers);


struct person_t* list_add_end(struct person_t *head, struct person_t *pers);


struct person_t* list_lookup(struct person_t *head, const char *name);


void list_apply(struct person_t *head, ptr_action_t f, void *arg);


void list_free_all(struct person_t *head);


struct person_t* list_del_by_name(struct person_t *head, const char *name);


struct person_t* list_del_by_name_ex(struct person_t *head, const char *name);


#endif	// #ifndef __LIST_H__
