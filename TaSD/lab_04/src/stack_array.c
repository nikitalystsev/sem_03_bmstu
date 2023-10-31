#include "stack_array.h"

int create_stack_array(stack_array_t *const stack)
{
    stack->array_data = malloc(stack->capacity * sizeof(data_t));
    stack->top = -1;

    if (!stack->array_data)
    {
        return ERR_MEM_ALLOC;
    }

    return EXIT_SUCCESS;
}

void stack_array_push(stack_array_t *const stack, data_t data)
{
    stack->array_data[++stack->top] = data;
}

void stack_array_pop(stack_array_t *const stack)
{
    if (isempty_stack_array(stack))
    {
        return;
    }

    stack->top--;
}

bool isempty_stack_array(stack_array_t *const stack)
{
    if (stack->top + 1 != 0)
    {
        return false;
    }

    return true;
}

void stack_array_clean(stack_array_t *const stack)
{
    free(stack->array_data);
    stack->top = -1;
    stack->capacity = 0;
}

void print_stack_array(stack_array_t *const stack)
{
    if (isempty_stack_array(stack))
    {
        return;
    }

    printf("\nCтек как массив:\n");
    
    for (int i = stack->top; i >= 0; i--)
    {
        printf("[+] data: %c, index: %d\n", stack->array_data[i].symbol, i);
    }
}


