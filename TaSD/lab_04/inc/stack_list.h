#ifndef __STACK_LIST_H__
#define __STACK_LIST_H__

#include "defines.h"

typedef struct stack_list_t stack_list_t;
typedef struct free_addr_t free_addr_t;

struct stack_list_t
{
    data_t data;
    stack_list_t *next;
};

struct free_addr_t
{
    size_t *array_free_addr[MAX_FREE_ADDR_SIZE];
    int top;
};

stack_list_t *create_stack_list(data_t data);

stack_list_t *stack_list_push(stack_list_t *head, stack_list_t *element);

stack_list_t *stack_list_pop(stack_list_t *head);

bool isempty_stack_list(stack_list_t *head);

void stack_list_clean(stack_list_t **head);

bool check_unique_address(free_addr_t *const free_addr,
                          stack_list_t *const addr);
                          
void print_stack_list(stack_list_t *head);

void print_free_address(free_addr_t *const free_addr);

#endif
