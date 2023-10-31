#ifndef _STACK_1_H_

#define _STACK_1_H_

#include <stddef.h>
#include <stdbool.h>


#define STACK_SIZE 10


typedef struct
{
    int content[STACK_SIZE];
    size_t top;

} stack_t;


void make_empty(stack_t *s);

bool is_empty(const stack_t *s);

bool is_full(const stack_t *s);

int push(stack_t *s, int i);

int pop(stack_t *s, int *i);

#endif
