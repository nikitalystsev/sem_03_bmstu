#include "my_node.h"

node_t *create_node(void *data)
{
    node_t *node = malloc(sizeof(node_t));

    if (node)
    {
        node->data = data;
        node->next = NULL;
    }

    return node;
}

node_t *push_back(node_t *head, node_t *node)
{
    node_t *tmp_head = head;

    if (!head)
    {
        return node;
    }

    for (; tmp_head->next; tmp_head = tmp_head->next);

    tmp_head->next = node;

    return head;
}

int add_node_to_end(node_t **head, data_t *data)
{
    node_t *node = create_node(data);

    if (!node)
    {
        return ERR_ALLOC_MEM;
    }

    *head = push_back(*head, node);

    return EXIT_SUCCESS;
}

void free_node(node_t *node)
{
    free(node);
}

void free_list(node_t *head)
{
    node_t *tmp_head = head;

    for (; head; head = tmp_head)
    {
        tmp_head = head->next;
        free_node(head);
    }
}

int get_count_node(node_t *head)
{
    node_t *tmp_head = head;

    int c = 0;

    while (tmp_head)
    {
        c++;
        tmp_head = tmp_head->next;
    }

    return c;
}

void front_back_split(node_t *head, node_t **front, node_t **back)
{
    int count_node = get_count_node(head);

    if (!count_node)
    {
        return;
    }

    int range = count_node / 2;

    if (count_node % 2 == 1)
    {
        range++;
    }

    node_t *tmp_head = head;

    *front = tmp_head;

    for (int i = 0;
        i < range - 1 && tmp_head;
        i++, tmp_head = tmp_head->next);

    *back = tmp_head->next;

    tmp_head->next = NULL;
}

int compare(const void *a, const void *b)
{
    return ((data_t *)a)->number - ((data_t *)b)->number;
}

node_t *sorted_merge(node_t **head_a, node_t **head_b,
cmp_t comparator)
{
    node_t *head_res = NULL;
    node_t *tmp_head_a = *head_a, *tmp_head_b = *head_b;

    while (tmp_head_a != NULL && tmp_head_b != NULL)
        if (comparator(tmp_head_a->data, tmp_head_b->data) <= 0)
        {
            if (add_node_to_end(&head_res, tmp_head_a->data) != 0)
            {
                return NULL;
            }

            tmp_head_a = tmp_head_a->next;
        }
        else
        {
            if (add_node_to_end(&head_res, tmp_head_b->data) != 0)
            {
                return NULL;
            }

            tmp_head_b = tmp_head_b->next;
        }

    node_t *tmp_head = tmp_head_a ? tmp_head_a : tmp_head_b;

    while (tmp_head)
    {
        if (add_node_to_end(&head_res, tmp_head->data) != 0)
        {
            return NULL;
        }

        tmp_head = tmp_head->next;
    }

    free_list(*head_a);
    free_list(*head_b);

    *head_a = NULL;
    *head_b = NULL;

    return head_res;
}

node_t *sort(node_t *head, cmp_t comparator)
{
    node_t *front, *back;

    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    front_back_split(head, &front, &back);

    front = sort(front, comparator);
    back = sort(back, comparator);

    head = sorted_merge(&front, &back, comparator);

    return head;
}

void print_node(node_t *node)
{
    printf("%d\n", *(int *)node->data);
}

void print_list(node_t *head)
{
    node_t *tmp_head = head;

    while (tmp_head)
    {
        print_node(tmp_head);
        tmp_head = tmp_head->next;
    }
}

void write_node_to_file(node_t *node, FILE *file)
{
    fprintf(file, "%d\n", ((data_t *)node->data)->number);
}

int write_list_to_file(node_t *head, const char *file_name)
{
    int c = get_count_node(head);

    node_t *tmp_head = head;

    FILE *file = fopen(file_name, "w");

    if (!file)
    {
        return ERR_OPEN_FILE;
    }

    fprintf(file, "%d\n", c);

    while (tmp_head)
    {
        write_node_to_file(tmp_head, file);
        tmp_head = tmp_head->next;
    }

    fclose(file);

    return EXIT_SUCCESS;
}

int read_numbers(data_t **arr_data, 
int *const count_elements,
node_t **head, 
FILE *file)
{
    fscanf(file, "%d", count_elements);

    if ((*arr_data = malloc(*count_elements * sizeof(data_t))) == NULL)
    {
        return ERR_ALLOC_MEM;
    }

    for (int i = 0; i < *count_elements; i++)
    {
        fscanf(file, "%d", &(*arr_data)[i].number);
        node_t *node = create_node(&(*arr_data)[i]);

        if (!node)
        {
            return ERR_ALLOC_MEM;
        }

        *head = push_back(*head, node);
    }

    return EXIT_SUCCESS;
}
