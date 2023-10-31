#include "balanced_parentheses.h"

bool ismatching_pair(const char character1, const char character2)
{
    if (character1 == '(' && character2 == ')')
        return true;
    else if (character1 == '{' && character2 == '}')
        return true;
    else if (character1 == '[' && character2 == ']')
        return true;

    return false;
}

bool balanced_parentheses_stack_array(stack_array_t *const stack,
                                      const char *const exp)
{
    int len_exp = strlen(exp);

    data_t data;

    for (int i = 0; i < len_exp; i++)
    {
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
        {
            data.symbol = exp[i];
            stack_array_push(stack, data);
        }

        if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']')
        {
            if (stack->top == -1)
                return false;

            // printf("[+] херово считывается дата...\n");
            // printf("[+] индекс указателя на последний элемент: %d\n", stack->top);
            data = stack->array_data[stack->top];

            stack_array_pop(stack);

            if (!ismatching_pair(data.symbol, exp[i]))
                return false;
        }
    }

    if (stack->top != -1)
        return false;

    return true;
}

bool balanced_parentheses_stack_list(stack_list_t **stack,
                                     const char *const exp)
{
    int len_exp = strlen(exp);

    data_t data;

    for (int i = 0; i < len_exp; i++)
    {
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
        {
            data.symbol = exp[i];

            stack_list_t *elem = create_stack_list(data);

            *stack = stack_list_push(*stack, elem);
        }

        if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']')
        {
            if (stack == NULL)
                return false;

            data = (*stack)->data;
            *stack = stack_list_pop(*stack);

            if (!ismatching_pair(data.symbol, exp[i]))
                return false;
        }
    }

    if ((*stack)->next != NULL)
    {
        return false;
    }

    stack_list_clean(stack);

    return true;
}