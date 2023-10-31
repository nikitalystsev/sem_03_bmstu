#include "process.h"
#include "print.h"

double random_double(double min, double max)
{
    double x = rand() / (double)RAND_MAX; /* [0, 1.0] */

    return min + x * (max - min);
}

int change_time(double *const min, double *const max)
{
    double tmp_min, tmp_max;

    int rc = 0;

    if ((rc = read_range_time(&tmp_min, &tmp_max)) != 0)
        return rc;

    *min = tmp_min;
    *max = tmp_max;

    return EXIT_SUCCESS;
}

int queue_arr_size_in_bytes(const queue_arr_t *const queue)
{
    int size = 0;

    size += sizeof(queue->size);
    size += sizeof(queue->p_in);
    size += sizeof(queue->p_out);
    size += (sizeof(queue->queue[0]) * (queue->p_in - queue->p_out + 1));

    return size;
}

int queue_list_size_in_bytes(const queue_list_t *const queue)
{
    int size = 0;

    size += sizeof(queue->size);
    size += sizeof(queue->queue);
    size += (sizeof(list_t) * queue->size);

    return size;
}

int max_int(const int a, const int b)
{
    return (a > b) ? a : b;
}

double max_double(const double a, const double b)
{
    if (fabs(a - b) <= EPS)
        return a;
    else if (a < (b - EPS))
        return b;

    return a;
}

static void print_free_addr(const free_addr_t *const free_addr)
{
    if (free_addr->top == -1)
    {
        puts(VIOLET "\n[-] Массив свободных адресов пустой!" RESET);
        return;
    }

    puts("\nМассив ранее высвобожденных адресов:\n");

    for (int i = 0; i <= free_addr->top; i++)
        printf("free address: %p\n", (void *)free_addr->free_addrs[i].addr);
}

int do_modeling(void)
{
    int rc = 0;

    param_t param;
    fill_default_param(&param);

    free_addr_t free_addr;
    free_addr.free_addrs = NULL;
    free_addr.size = MAX_FREE_ADDR_SIZE;

    if ((rc = create_free_addr(&free_addr)) != 0)
        goto free;

    init_free_addrs(&free_addr);

    int8_t menu_item;

    while (true)
    {
        print_task_menu(&param);

        if ((rc = read_task_menu_item(&menu_item)) != 0)
            goto free;

        switch (menu_item)
        {
        case 0:
            free(free_addr.free_addrs);
            exit(0);
            break;
        case 1:
            if ((rc = change_time(&param.min_process_time,
                                  &param.max_process_time)) != 0)
                goto free;
            break;
        case 2:
            if ((rc = change_time(&param.min_add_time,
                                  &param.max_add_time)) != 0)
                goto free;
            break;
        case 3:
            if ((rc = model_list(&param, &free_addr)) != 0)
                goto free;
            break;
        case 4:
            if ((rc = model_arr(&param)) != 0)
                goto free;
            break;
        case 5:
            print_free_address(&free_addr);
            break;
        }
    }

free:
    free(free_addr.free_addrs);

    return rc;
}

int do_action(void)
{
    int rc = 0;

    queue_arr_t queue_array;
    queue_array.queue = NULL;

    queue_list_t queue_list;
    queue_list.size = 0;
    queue_list.queue = NULL;

    elem_t arr_elem, list_elem;

    free_addr_t free_addr;
    free_addr.free_addrs = NULL;
    free_addr.size = MAX_SIZE_QUEUE;

    int8_t menu_item;

    if ((rc = create_free_addr(&free_addr)) != 0)
        goto free;

    init_free_addrs(&free_addr);

    int is_create = 0;

    while (true)
    {
        print_menu();

        if ((rc = read_menu_item(&menu_item)) != 0)
            goto free;

        switch (menu_item)
        {
        case 0:
            free(queue_array.queue);
            free_list(queue_list.queue);
            free(free_addr.free_addrs);
            exit(0);
            break;
        case 1:
            if ((rc = make_queue_arr(&queue_array)) != 0)
                goto free;
            break;
        case 2:
            if ((rc = add_elem_in_arr(&queue_array, &arr_elem)) != 0)
                goto free;
            break;
        case 3:
            del_elem_from_arr(&queue_array);
            break;
        case 4:
            print_queue_arr(&queue_array);
            break;
        case 5:
            free_arr(&queue_array);
            break;
        case 6:
            make_queue_list(&queue_list, &is_create);
            break;
        case 7:
            if ((rc = add_elem_in_list(
                     &queue_list, is_create, &list_elem)) != 0)
                goto free;
            break;
        case 8:
            del_elem_from_list(&queue_list, &free_addr,
                               &list_elem, is_create);
            break;
        case 9:
            print_list(&queue_list, is_create);
            break;
        case 10:
            free_queue_list(&queue_list, &is_create);
            break;
        case 11:
            print_free_addr(&free_addr);
            break;
        case 12:
            print_func_time();
            break;
        case 13:
            print_size_info();
            break;
        }
    }

free:
    free(queue_array.queue);
    free_list(queue_list.queue);
    free(free_addr.free_addrs);

    return rc;
}
