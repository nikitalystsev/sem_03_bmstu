#include <stdlib.h>
#include <assert.h>
#include "stack.h"


struct node
{
    int item;
    struct node *next;
};


struct stack_type
{
    struct node *top;

};


stack_t create(void)
{
    stack_t s = malloc(sizeof(struct stack_type));

    if (s)
        s->top = NULL;

    return s;
}


void destroy(stack_t s)
{
	assert(s);
	
    int item;

    while (!is_empty(s))
        (void) pop(s, &item);

    free(s);
}


bool is_empty(const stack_t s)
{
	assert(s);
	
    return s->top == NULL;
}


bool is_full(const stack_t s)
{
	assert(s);
	
    return false;
}


int push(stack_t s, int i)
{
	assert(s);
	
    struct node *node = malloc(sizeof(struct node));

    if (!node)
        return 1;

    node->next = s->top;
    node->item = i;

    s->top = node;

    return 0;
}


int pop(stack_t s, int *i)
{
	assert(s);
	
    struct node *node;

    if (is_empty(s))
        return 1;

    node = s->top;

    *i = node->item;

    s->top = node->next;

    free(node);

    return 0;
}
