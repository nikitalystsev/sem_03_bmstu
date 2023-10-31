#ifndef __QUEUE_LIST_H__
#define __QUEUE_LIST_H__

#include "defines.h"

typedef struct list_t list_t;
typedef struct queue_list_t queue_list_t;
typedef struct addr_t addr_t;
typedef struct free_addr_t free_addr_t;

/// @brief односвязный список, содержащий данные
struct list_t
{
    elem_t data;  // данные
    list_t *next; // указатель на следующий элемент
};

/// @brief очередь в виде односвязного списка
struct queue_list_t
{
    list_t *queue; // очередь в виде списка
    int size;      // количество злементов в списке
};

/// @brief адрес
struct addr_t
{
    size_t *addr;
    bool check_free;
    bool check_create;
};

/// @brief массив свободных адресов
struct free_addr_t
{
    // массив ранее высвобожденных адресов
    addr_t *free_addrs;
    int top;  // индекс последнего  добавленного элемента
    int size; // размер массива адресов
};

list_t *create_node(const elem_t data);

int check_node(const list_t *const node);

list_t *push_queue_list(list_t *const head, list_t *node);

list_t *pop_queue_list(list_t *const head, elem_t *const list_elem);

void free_node(list_t *const node);

void free_list(list_t *head);

void print_node(const list_t *const node);

void print_queue_list(list_t *const head);

int create_free_addr(free_addr_t *free_addr);

void init_free_addrs(free_addr_t *free_addr);

void print_free_address(const free_addr_t *const free_addr);

/* Функции для обработки действий пользователя в меню */
void make_queue_list(queue_list_t *const queue, int *const is_create);

int add_elem_in_list(queue_list_t *const queue, const int is_create,
                     elem_t *const elem);

void del_elem_from_list(queue_list_t *const queue, free_addr_t *const addrs,
                        elem_t *const elem, const int is_create);

void print_list(queue_list_t *const queue, const int is_create);

void free_queue_list(queue_list_t *const queue, int *const is_create);

#endif
