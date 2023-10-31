#ifndef __LINKED_LIST_OPERATIONS__
#define __LINKED_LIST_OPERATIONS__

#include "defines.h"

list_t *create_linked_list(const int data);

int add_element_end(int data, list_t *head);

void free_linked_list(list_t *head);

void print_linked_list(const list_t *const head);

#endif
