#ifndef __LIST_H__

#define __LIST_H__


#include "list_node.h"


typedef void (*ptr_action_t)(person_t*, void*);


person_t* list_add_front(person_t *head, person_t *pers);


void list_add_front_usual(person_t **head, person_t *pers);


person_t* list_add_end(person_t *head, person_t *pers);


person_t* list_lookup(person_t *head, const char *name);


void list_apply(person_t *head, ptr_action_t f, void *arg);


void list_free_all(person_t *head);


person_t* list_del_by_name(person_t *head, const char *name);


person_t* list_del_by_name_ex(person_t *head, const char *name);


#endif	// #ifndef __LIST_H__
