#include <stdlib.h>
#include <assert.h>
#include "stack_2.h"


#define STACK_SIZE 10


struct stack_type
{
    int content[STACK_SIZE];
    size_t top;
};


stack_t create(void)
{
    stack_t s = malloc(sizeof(struct stack_type));

    if (s)
        make_empty(s);

    return s;
}


void destroy(stack_t s)
{
    free(s);
}


void make_empty(stack_t s)
{
	assert(s);
	
    s->top = 0;
}


bool is_empty(const stack_t s)
{
	assert(s);
	
    return s->top == 0;
}


bool is_full(const stack_t s)
{
	assert(s);
	
    return s->top == STACK_SIZE;
}


int push(stack_t s, int i)
{
	assert(s);
	
    if (is_full(s))
        return 1;

    s->content[(s->top)++] = i;

    return 0;
}


int pop(stack_t s, int *i)
{
	assert(s);
	
    if (is_empty(s))
        return 1;

    *i = s->content[--(s->top)];

    return 0;
}
