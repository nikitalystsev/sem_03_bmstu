#ifndef _STACK_3_H_

#define _STACK_3_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct stack_type* stack_t;

stack_t create(void);

stack_t create_ex(size_t size);

void destroy(stack_t s);

void make_empty(stack_t s);

bool is_empty(const stack_t s);

bool is_full(const stack_t s);

int push(stack_t s, int i);

int pop(stack_t s, int *i);

#endif