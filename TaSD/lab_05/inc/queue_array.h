#ifndef __QUEUE_ARRAY_H__
#define __QUEUE_ARRAY_H__

#include "defines.h"

typedef struct queue_arr_t queue_arr_t;

/// @brief очередь как массив
struct queue_arr_t
{
    elem_t *queue; // массив заявок
    int p_in;      // индекс очередного добавленного элемента
    int p_out;     // индекс очередного исключающего элемента
    int size;      // размер массива заявок
};

int create_queue_arr(queue_arr_t *const queue);

int push_queue_arr(queue_arr_t *const queue, const elem_t *const data);

void shift(queue_arr_t *const queue);

int pop_queue_arr(queue_arr_t *const queue, elem_t *const elem);

void print_queue_arr(const queue_arr_t *const queue);

/* Функции для выполнения пунктов меню */
int make_queue_arr(queue_arr_t *const queue);

int add_elem_in_arr(queue_arr_t *const queue, elem_t *const elem);

void del_elem_from_arr(queue_arr_t *const queue);

void free_arr(queue_arr_t *const queue);

#endif
