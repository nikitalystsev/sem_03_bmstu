#include "linked_list_operations.h"

list_t *create_linked_list(const int data)
{
    list_t *head = calloc(1, sizeof(list_t));

    if (!head)
    {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    head->index_start_row = data;
    head->next_elem = NULL;

    return head;
}

int add_element_end(int data, list_t *head)
{
    list_t *tmp = calloc(1, sizeof(list_t));

    if (!tmp)
    {
        printf("Ошибка выделения памяти!\n");
        return ERR_ALLOC_MEMORY;
    }

    tmp->index_start_row = data;
    tmp->next_elem = NULL;

    list_t *tmp_ptr = head;

    while (tmp_ptr->next_elem != NULL)
    {
        tmp_ptr = tmp_ptr->next_elem;
    }

    tmp_ptr->next_elem = tmp;

    return EXIT_SUCCESS;
}

void free_linked_list(list_t *head)
{
    list_t *tmp_ptr = head;

    while (tmp_ptr->next_elem != NULL)
    {
        list_t *next_addr = tmp_ptr->next_elem;

        free(tmp_ptr);

        tmp_ptr = next_addr;
    }

    free(tmp_ptr);
}

void print_linked_list(const list_t *const head)
{
    const list_t *tmp_ptr = head;

    if (tmp_ptr == NULL)
    {
        printf("Односвязный список пуст.\n");
        return;
    }

    int count = 0;
    
    while (tmp_ptr->next_elem != NULL)
    {
        printf("%d ", tmp_ptr->index_start_row);
        count++;
        tmp_ptr = tmp_ptr->next_elem;
    }

    printf("%d ", tmp_ptr->index_start_row);
    count++;
}
