#include "stack_list.h"

stack_list_t *create_stack_list(data_t data)
{
    stack_list_t *head = malloc(sizeof(stack_list_t));

    if (head)
    {
        head->data = data;
        head->next = NULL;
    }

    return head;
}

stack_list_t *stack_list_push(stack_list_t *head, stack_list_t *element)
{
    element->next = head;
    return element;
}

stack_list_t *stack_list_pop(stack_list_t *head)
{
    stack_list_t *tmp_head = head->next;

    free(head);

    return tmp_head;
}

void stack_list_clean(stack_list_t **head)
{
    stack_list_t *next;

    for (; *head; *head = next)
    {
        next = (*head)->next;
        free(*head);
    }

    head = NULL;
}

bool isempty_stack_list(stack_list_t *head)
{
    if (head != NULL)
    {
        return false;
    }

    return true;
}

bool check_unique_address(free_addr_t *const free_addr,
                          stack_list_t *const addr)
{
    for (int i = 0; i < free_addr->top + 1; i++)
        if ((size_t *)addr == free_addr->array_free_addr[i])
            return false;

    return true;
}

void print_stack_list(stack_list_t *head)
{

    if (isempty_stack_list(head))
    {
        return;
    }

    stack_list_t *tmp_head = head;

    printf("\nCтек как список:\n");

    while (tmp_head != NULL)
    {
        printf("\n[+] address: %p\n", (void *)tmp_head);
        printf("[+] data: %c\n", tmp_head->data.symbol);
        tmp_head = tmp_head->next;
    }
}

void print_free_address(free_addr_t *const free_addr)
{
    if (free_addr->top == -1)
    {
        printf(VIOLET "\n[-] Массив свободных адресов пустой!\n" RESET);
        return;
    }

    printf("\nМассив высвобожденных адресов:\n\n");

    for (int i = 0; i < free_addr->top + 1; i++)
    {
        printf("[+] free address: %p\n",
               (void *)free_addr->array_free_addr[i]);
    }
}
