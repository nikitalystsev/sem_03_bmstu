#ifndef __HASH_H__
#define __HASH_H__

#include "defines.h"

typedef int (*hash_func_t)(int, int);
typedef struct hash_t hash_t;
typedef struct data_t data_t;
typedef struct hash_table_t hash_table_t;

struct data_t
{
    int data; // данные
    data_t *next;
};

struct hash_t
{
    data_t *head;
    int hash;
    int collision;
    bool is_full;
};

struct hash_table_t
{
    hash_t *data;
    int size; // количество элементов
};

int hash(int data, int size);

int other_hash(int data, int size);

data_t *create_data(int data);

data_t *push_front(data_t *head, data_t *node);

int create_hash_table(hash_table_t *table);

void default_hash_table(hash_table_t *table);

void free_hash(data_t **head_next);

void free_table(hash_table_t *table);

void print_list(data_t *head);

void print_hash(hash_t *hash, int index);

void print_hash_table(hash_table_t *table);

#endif
