#ifndef __MY_NODE_H__
#define __MY_NODE_H__

#include "defines.h"

typedef int (*cmp_t)(const void *, const void *);

typedef struct node node_t;
typedef struct data data_t;

struct node
{
    void *data;
    node_t *next;
};

struct data
{
    int number;
};

node_t *create_node(void *data);

node_t *push_back(node_t *head, node_t *node);

int add_node_to_end(node_t **head, data_t *data);

node_t *get_last_but_one(node_t *head);

void free_node(node_t *node);

void free_list(node_t *head);

int get_count_node(node_t *head);

void front_back_split(node_t *head, node_t **front, node_t **back);

int compare(const void *a, const void *b);

node_t *sorted_merge(node_t **head_a, node_t **head_b,
cmp_t comparator);

node_t *sort(node_t *head, cmp_t comparator);

void print_node(node_t *node);

void print_list(node_t *head);

void write_node_to_file(node_t *node, FILE *file);

int write_list_to_file(node_t *head, const char *file_name);

int read_numbers(data_t **arr_data, 
int *const count_elements,
node_t **head, 
FILE *file);

#endif
