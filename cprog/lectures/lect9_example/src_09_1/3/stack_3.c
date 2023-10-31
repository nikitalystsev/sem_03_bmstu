#include <stdlib.h>
#include <assert.h>
#include "stack_3.h"


struct stack_type
{
    int *content;
    size_t top;
    size_t size;

};


stack_t create(void)
{
    return create_ex(10);
}


stack_t create_ex(size_t size)
{
    stack_t s = malloc(sizeof(struct stack_type));

    if (s)
    {
        s->content = malloc(size * sizeof(int));

        if (s->content)
        {
            s->size = size;

            make_empty(s);
        }
        else
        {
            free(s);

            s = NULL;
        }
    }

    return s;
}


void destroy(stack_t s)
{
	assert(s);
	
    free(s->content);
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
	
    return s->top == s->size;
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
