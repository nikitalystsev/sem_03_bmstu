#include "queue_array.h"
#include "read.h"

int create_queue_arr(queue_arr_t *const queue)
{
    queue->queue = malloc(queue->size * sizeof(elem_t));

    if (!queue->queue)
    {
        puts(VIOLET "[-] Ошибка выделения памяти!" RESET);
        return ERR_ALLOC_MEM;
    }

    queue->p_in = -1;
    queue->p_out = 0;

    return EXIT_SUCCESS;
}

int push_queue_arr(queue_arr_t *const queue, const elem_t *const data)
{
    if (queue->p_in >= queue->size - 1)
    {
        puts(VIOLET "[-] Очередь как массив заполнена максимально! "
                    "Добавление невозможно" RESET);
        return ERR_QUEUE_OVERFLOW;
    }

    queue->queue[++queue->p_in] = *data;

    return EXIT_SUCCESS;
}

void shift(queue_arr_t *const queue)
{
    for (int i = 0; i < queue->p_in; i++)
        queue->queue[i] = queue->queue[i + 1];

    queue->p_in--;
}

int pop_queue_arr(queue_arr_t *const queue, elem_t *const elem)
{
    int rc = 0;

    if (queue->p_in == -1)
    {
        puts(VIOLET "[-] Очередь как массив пустая! "
                      "Удаление невозможно." RESET);
        return EMPTY_QUEUE;
    }
    else
    {
        *elem = queue->queue[queue->p_out];
        shift(queue);
    }

    return rc;
}

void print_queue_arr(const queue_arr_t *const queue)
{
    if (!queue->queue)
    {
        puts(VIOLET "[-] Очередь как массив не создана!" RESET);
        return;
    }

    if (queue->p_in == -1)
    {
        puts(VIOLET "[+] Очередь как массив пустая!" RESET);
        return;
    }

    puts("Очередь:");

    for (int8_t i = queue->p_out; i <= queue->p_in; i++)
        printf("[+] queue elem: %d\n", queue->queue[i].count_iter);
}

int make_queue_arr(queue_arr_t *const queue)
{
    int rc = 0;

    if (!queue->queue)
    {
        if ((rc = read_size_queue_array(&queue->size)) != 0)
            return rc;
        if ((rc = create_queue_arr(queue)) != 0)
            return rc;

        puts(GREEN "[+] Очередь как массив была успешно создана!" RESET);
    }
    else
        puts(VIOLET "[+] Очередь как массив была создана ранее!" RESET);

    return rc;
}

int add_elem_in_arr(queue_arr_t *const queue, elem_t *const elem)
{
    int rc = 0;

    if (queue->queue)
    {
        if ((rc = read_queue_elem(&elem->count_iter)) != 0)
            return rc;

        if (push_queue_arr(queue, elem) == 0)
            puts(GREEN "[+] Элемент был успешно добавлен "
                       "в хвост очереди!" RESET);
    }
    else
        puts(VIOLET "[-] Очередь как массив не создана!" RESET);

    return rc;
}

void del_elem_from_arr(queue_arr_t *const queue)
{
    elem_t elem;

    if (queue->queue)
    {
        if (pop_queue_arr(queue, &elem) == 0)
            puts(GREEN "[+] Элемент был успешно удален "
                       "из головы очереди!" RESET);
    }
    else
        puts(VIOLET "[-] Очередь как массив не создана!" RESET);
}

void free_arr(queue_arr_t *const queue)
{
    if (queue->queue)
    {
        free(queue->queue);
        queue->queue = NULL;
        puts(GREEN "[+] Очередь как массив была успешно очищена!" RESET);
    }
    else
        puts(VIOLET "[-] Очередь как массив не создана!" RESET);
}
