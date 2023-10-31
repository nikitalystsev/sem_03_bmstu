#ifndef __STACK_ARRAY_H__
#define __STACK_ARRAY_H__

#include "defines.h"

typedef struct stack_array_t stack_array_t;

struct stack_array_t
{
    data_t *array_data;
    int top;               // top - число, количество элементов, а вместе с тем и указатель на вершину, тобишь индекс последнего добавленного элемента
    int capacity;
};

int create_stack_array(stack_array_t *const stack);

void stack_array_push(stack_array_t *const stack, data_t data);

void stack_array_pop(stack_array_t *const stack);

bool isempty_stack_array(stack_array_t *const stack);

void stack_array_clean(stack_array_t *const stack);

void print_stack_array(stack_array_t *const stack);

#endif
