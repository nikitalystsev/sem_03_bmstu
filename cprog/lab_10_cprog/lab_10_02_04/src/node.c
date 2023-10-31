#include "node.h"

node_t *create_node(int factor, int power)
{
    node_t *node = malloc(sizeof(node_t));

    if (node)
    {
        node->factor = factor;
        node->power = power;
        node->next = NULL;
    }

    return node;
}

node_t *push_front(node_t *head, node_t *node)
{
    node->next = head;

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

int add_node_to_end(node_t **head, int factor, int power)
{
    node_t *node = create_node(factor, power);

    if (!node)
    {
        return ERR_ALLOC_MEM;
    }

    *head = push_front(*head, node);

    return EXIT_SUCCESS;
}

node_t *pop_front(node_t *head)
{
    node_t *tmp_head = head->next;

    free(head);

    return tmp_head;
}

node_t *get_last_but_one(node_t *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (head->next == NULL)
    {
        return NULL;
    }
    while (head->next->next)
    {
        head = head->next;
    }

    return head;
}

void pop_back(node_t **head)
{
    node_t *last_bn = NULL;

    if (!head || !(*head))
    {
        return;
    }

    last_bn = get_last_but_one(*head);

    if (last_bn == NULL)
    {
        free_node(*head);
        *head = NULL;
    }
    else
    {
        free_node(last_bn->next);
        last_bn->next = NULL;
    }
}

node_t *reverse(node_t *head)
{
    node_t *new_head = NULL;

    node_t *tmp_head = head;

    while (tmp_head)
    {
        if (add_node_to_end(&new_head, tmp_head->factor, tmp_head->power) != 0)
        {
            return NULL;
        }
        
        tmp_head = tmp_head->next;
    }

    free_list(head);

    return new_head;
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

void print_node(node_t *node)
{
    printf("%d %d ", node->factor, node->power);
}

void print_list(node_t *head)
{
    node_t *tmp_head = head;

    while (tmp_head)
    {
        print_node(tmp_head);
        tmp_head = tmp_head->next;
    }

    printf("1\n");
}
