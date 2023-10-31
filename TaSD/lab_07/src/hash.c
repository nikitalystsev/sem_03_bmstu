#include "hash.h"

int hash(int data, int size)
{
    return abs(data) % size;
}

int other_hash(int data, int size)
{
    int sum_digit = 0;

    while (data)
    {
        sum_digit += data % 10;
        data /= 10;
    }

    return sum_digit % size;
}

data_t *create_data(int data)
{
    data_t *node = malloc(sizeof(data_t));

    if (node)
    {
        node->data = data;
        node->next = NULL;
    }

    return node;
}

data_t *push_front(data_t *head, data_t *node)
{
    node->next = head;
    return node;
}

int create_hash_table(hash_table_t *table)
{
    table->data = malloc(sizeof(hash_t) * table->size);

    if (!table->data)
        return ERR_MEM_ALLOC;

    return EXIT_SUCCESS;
}

void default_hash_table(hash_table_t *table)
{
    for (int i = 0; i < table->size; i++)
    {
        table->data[i].collision = 0;
        table->data[i].is_full = false;
        table->data[i].head = NULL;
        table->data[i].hash = 0;
    }
}

void free_hash(data_t **head)
{
    data_t *next;

    for (; *head; *head = next)
    {
        next = (*head)->next;
        free(*head);
    }

    head = NULL;
}

void free_table(hash_table_t *table)
{
    for (int i = 0; i < table->size; i++)
        free_hash(&table->data[i].head);

    free(table->data);
}

void print_list(data_t *head)
{

    data_t *tmp_head = head;

    while (tmp_head)
    {
        printf(" %10d |", tmp_head->data);
        tmp_head = tmp_head->next;
    }

    printf("\n");
}

void print_hash(hash_t *hash, int index)
{
    printf("| %10d | %10d |", index, hash->hash);

    data_t *tmp_data = hash->head;
    print_list(tmp_data);
    puts("----------------------------------------");
}

void print_hash_table(hash_table_t *table)
{
    puts("\n----------------------------------------");
    puts("|   Индекс   |     Хеш    |  Значение  |");
    puts("----------------------------------------");

    for (int i = 0; i < table->size; i++)
        print_hash(&table->data[i], i);
}
