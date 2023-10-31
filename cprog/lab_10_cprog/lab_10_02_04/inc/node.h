#ifndef __NODE_H__
#define __NODE_H__

#include "defines.h"

typedef struct node node_t;

struct node
{
    int factor;
    int power;
    node_t *next;
};

node_t *create_node(int factor, int power);

node_t *push_front(node_t *head, node_t *node);

node_t *push_back(node_t *head, node_t *node);

int add_node_to_end(node_t **head, int factor, int power);

node_t *pop_front(node_t *head);

node_t *get_last_but_one(node_t *head);

void pop_back(node_t **head);

node_t *reverse(node_t *head);

void free_node(node_t *node);

void free_list(node_t *head);

int get_count_node(node_t *head);

void print_node(node_t *node);

void print_list(node_t *head);

#endif
