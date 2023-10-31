#include <stddef.h>
#include "stack_0.h"


#define STACK_SIZE 10


int content[STACK_SIZE];
size_t top;


void make_empty(void)
{
    top = 0;
}


bool is_empty(void)
{
    return top == 0;
}


bool is_full(void)
{
    return top >= STACK_SIZE;
}


int push(int i)
{
    if (is_full())
        return 1;

    content[top++] = i;

    return 0;
}


int pop(int *i)
{
    if (is_empty())
        return 1;

    *i = content[--top];

    return 0;
}
