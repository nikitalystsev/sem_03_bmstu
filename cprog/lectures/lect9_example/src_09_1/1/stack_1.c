#include <assert.h>
#include "stack_1.h"


void make_empty(stack_t *s)
{
	assert(s);
	
    s->top = 0;
}


bool is_empty(const stack_t *s)
{
	assert(s);
	
    return s->top == 0;
}


bool is_full(const stack_t *s)
{
	assert(s);
	
    return s->top >= STACK_SIZE;
}


int push(stack_t *s, int i)
{
	assert(s);
	
    if (is_full(s))
        return 1;

    s->content[(s->top)++] = i;

    return 0;
}


int pop(stack_t *s, int *i)
{
	assert(s);
	
    if (is_empty(s))
        return 1;

    *i = s->content[--(s->top)];

    return 0;
}
