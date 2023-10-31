#ifndef _STACK_2_H_

#define _STACK_2_H_

#include <stdbool.h>


typedef struct stack_type* stack_t;


void make_empty(stack_t s);

bool is_empty(const stack_t s);

bool is_full(const stack_t s);

int push(stack_t s, int i);

int pop(stack_t s, int *i);


stack_t create(void);

void destroy(stack_t s);


#endif