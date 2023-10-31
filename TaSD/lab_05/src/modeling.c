#include "modeling.h"
#include "print.h"

void fill_default_param(param_t *const param)
{
    param->min_add_time = MIN_TIME_ADD;
    param->max_add_time = MAX_TIME_ADD;
    param->min_process_time = MIN_TIME_PROCESSING;
    param->max_process_time = MAX_TIME_PROCESSING;
    param->count_appl = COUNT_APPLICATION;
    param->count_print_appl = COUNT_PRINT_APPLICATION;
}

static void fill_default_model(model_t *const data)
{
    data->curr_len_queue = 0;
    data->av_len_queue = 0;
    data->count_calls_machine = 0;
    data->downtime = 0;
    data->count_input = 0;
    data->count_output = 0;
    data->model_time = 0;
    data->input_time = 0;
    data->output_time = 0;
    data->work_time = 0;
    data->memory_size = 0;
}

static void create_new_appl(elem_t *const elem, const param_t *const param)
{
    elem->add_time = random_double(param->min_add_time,
                                   param->max_add_time);
    elem->process_time = random_double(param->min_process_time,
                                       param->max_process_time);
    elem->count_iter = 0;
}

int model_arr(const param_t *const param)
{
    int rc = 0;

    srand(time(NULL));

    queue_arr_t queue;
    queue.size = MAX_SIZE_QUEUE;

    if ((rc = create_queue_arr(&queue)) != 0)
    {
        printf(VIOLET "[-] Ошибка выделения памяти!\n" RESET);
        return rc;
    }

    model_t model;

    fill_default_model(&model);

    bool machine = false;

    elem_t temp_elem, new_elem;

    int i = COUNT_PRINT_APPLICATION;

    int count_len_beetw_print = 0;
    double sum_curr_len = 0;

    int flag = 0;

    int mem_size = 0;
    int size = 0;
    model.work_time = microseconds_now();

    while (model.count_output < param->count_appl)
    {
        if (!machine)
        {
            if (queue.p_in == -1)
            {
                if (!flag)
                    create_new_appl(&new_elem, param), flag = 1;

                if ((rc = push_queue_arr(&queue, &new_elem)) != 0)
                {
                    printf(RED "[-] При моделировании СМО произошло "
                               "переполнение очереди!\n" RESET);
                    goto free;
                }
                flag = 0;
                
                model.count_input++;
                model.input_time += new_elem.add_time;
                model.output_time += new_elem.process_time;
                size++;
                mem_size = queue_arr_size_in_bytes(&queue);
                model.memory_size = max_int(model.memory_size, mem_size);
            }
            else
            {
                pop_queue_arr(&queue, &temp_elem);
                machine = true;
                model.count_calls_machine++;
                size--;
            }
        }
        else
        {
            if (!flag)
                create_new_appl(&new_elem, param), flag = 1;

            if (new_elem.add_time > temp_elem.process_time)
            {
                machine = false;
                temp_elem.count_iter++;

                if (temp_elem.count_iter < COUNT_PROCESS)
                {
                    model.output_time +=
                        random_double(param->min_process_time,
                                      param->max_process_time);

                    if ((rc = push_queue_arr(&queue, &temp_elem)) != 0)
                    {
                        printf(RED "[-] При моделировании СМО произошло "
                                   "переполнение очереди!\n" RESET);
                        goto free;
                    }
                    size++;
                    model.count_input++;

                    mem_size = queue_arr_size_in_bytes(&queue);
                    model.memory_size = max_int(model.memory_size, mem_size);
                }
                else
                    model.count_output++;
            }
            else if (temp_elem.process_time > new_elem.add_time &&
                     param->max_process_time > param->max_add_time)
            {
                temp_elem.process_time -= new_elem.add_time;
                size++;
            }
            else
            {
                temp_elem.process_time -= new_elem.add_time;

                model.input_time += new_elem.add_time;
                model.output_time += new_elem.process_time;

                if ((rc = push_queue_arr(&queue, &new_elem)) != 0)
                {
                    printf(RED "[-] При моделировании СМО произошло "
                               "переполнение очереди!\n" RESET);
                    goto free;
                }
    
                flag = 0;

                model.count_input++;
                size++;
                mem_size = queue_arr_size_in_bytes(&queue);
                model.memory_size = max_int(model.memory_size, mem_size);
            }
        }

        sum_curr_len += size;
        count_len_beetw_print++;

        if (model.count_output == i)
        {
            model.av_len_queue = sum_curr_len / count_len_beetw_print;
            model.curr_len_queue = size;
            print_intermediate(&model);
            sum_curr_len = 0;
            count_len_beetw_print = 0;
            i += COUNT_PRINT_APPLICATION;
        }
    }

    model.work_time = microseconds_now() - model.work_time;

    model.downtime = model.input_time - model.output_time;

    model.model_time = max_double(model.input_time, model.output_time);

    print_result(&model, param);

free:
    free(queue.queue);

    return rc;
}

int model_list(const param_t *const param, free_addr_t *const free_addrs)
{
    int rc = 0;

    srand(time(NULL));

    queue_list_t queue;
    queue.queue = NULL;
    queue.size = 0;

    model_t model;

    fill_default_model(&model);

    bool machine = false;

    elem_t temp_elem, new_elem;

    int i = COUNT_PRINT_APPLICATION;

    int count_len_beetw_print = 0;
    double sum_curr_len = 0;

    int flag = 0;

    int size = 0;

    model.work_time = microseconds_now();

    int mem_size = 0;

    while (model.count_output < param->count_appl)
    {
        if (!machine)
        {
            /* если аппарат не работает */
            if (queue.size == 0)
            {
                /* если в очереди нет элементов */
                if (!flag)
                    create_new_appl(&new_elem, param), flag = 1;

                if (queue.size >= MAX_SIZE_QUEUE)
                {
                    rc = ERR_QUEUE_OVERFLOW;
                    printf(RED "[-] При моделировании СМО произошло "
                               "переполнение очереди!\n" RESET);
                    goto free;
                }

                list_t *node = create_node(new_elem);
                if ((rc = check_node(node)) != 0)
                    goto free;

                free_addrs->free_addrs[++free_addrs->top].addr =
                    (size_t *)node;
                free_addrs->free_addrs[free_addrs->top].check_create = true;

                queue.queue = push_queue_list(queue.queue, node);
                flag = 0;

                queue.size++;
                size++;
                model.count_input++;
                model.input_time += new_elem.add_time;
                model.output_time += new_elem.process_time;

                mem_size = queue_list_size_in_bytes(&queue);
                model.memory_size = max_int(model.memory_size, mem_size);
            }
            else
            {
                /* если в очереди есть элементы */
                free_addrs->free_addrs[++free_addrs->top].addr =
                    (size_t *)queue.queue;
                free_addrs->free_addrs[free_addrs->top].check_free = true;

                queue.queue = pop_queue_list(queue.queue, &temp_elem);
                queue.size--;
                size--;
                machine = true;
                model.count_calls_machine++;
            }
        }
        else
        {
            /* если аппарат работает */
            if (!flag)
                create_new_appl(&new_elem, param), flag = 1;

            if (new_elem.add_time > temp_elem.process_time)
            {
                /*
                если заявка обработается раньше,
                чем другая заявка придет в очередь,
                то аппарат заканчивает работу
                */
                machine = false;
                temp_elem.count_iter++;

                if (temp_elem.count_iter < COUNT_PROCESS)
                {
                    /*
                    если из аппарата вышла заявка,
                    которая проходила очередь меньше 5 раз,
                    добавляем ее обратно
                    */

                    model.output_time +=
                        random_double(param->min_process_time,
                                      param->max_process_time);

                    if (queue.size >= MAX_SIZE_QUEUE)
                    {
                        rc = ERR_QUEUE_OVERFLOW;
                        printf(RED "[-] При моделировании СМО произошло "
                                   "переполнение очереди!\n" RESET);
                        goto free;
                    }

                    list_t *node = create_node(temp_elem);
                    if ((rc = check_node(node)) != 0)
                        goto free;

                    free_addrs->free_addrs[++free_addrs->top].addr =
                        (size_t *)node;
                    free_addrs->free_addrs[free_addrs->top].check_create = true;

                    queue.queue = push_queue_list(queue.queue, node);

                    queue.size++;
                    size++;
                    model.count_input++;

                    mem_size = queue_list_size_in_bytes(&queue);
                    model.memory_size = max_int(model.memory_size, mem_size);
                }
                else
                {
                    /* иначе покидает систему */
                    model.count_output++;
                }
            }
            else if (temp_elem.process_time > new_elem.add_time &&
                     param->max_process_time > param->max_add_time)
            {
                temp_elem.process_time -= new_elem.add_time;
                size++;
            }
            else
            {
                /*
                если заявка обработается позже,
                чем другая заявка придет в очередь, то добавляем другую заявку
                */
                temp_elem.process_time -= new_elem.add_time;

                model.input_time += new_elem.add_time;
                model.output_time += new_elem.process_time;

                if (queue.size >= MAX_SIZE_QUEUE)
                {
                    rc = ERR_QUEUE_OVERFLOW;
                    printf(RED "[-] При моделировании СМО произошло "
                               "переполнение очереди!\n" RESET);
                    goto free;
                }

                list_t *node = create_node(new_elem);
                if ((rc = check_node(node)) != 0)
                    goto free;

                free_addrs->free_addrs[++free_addrs->top].addr =
                    (size_t *)node;
                free_addrs->free_addrs[free_addrs->top].check_create = true;

                queue.queue = push_queue_list(queue.queue, node);
                flag = 0;

                queue.size++;
                size++;
                model.count_input++;

                mem_size = queue_list_size_in_bytes(&queue);
                model.memory_size = max_int(model.memory_size, mem_size);
            }
        }

        sum_curr_len += size;
        count_len_beetw_print++;

        if (model.count_output == i)
        {
            model.av_len_queue = sum_curr_len / count_len_beetw_print;
            model.curr_len_queue = size;
            print_intermediate(&model);
            sum_curr_len = 0;
            count_len_beetw_print = 0;
            i += COUNT_PRINT_APPLICATION;
        }
    }

    model.work_time = microseconds_now() - model.work_time;

    model.downtime = model.input_time - model.output_time;

    model.model_time = max_double(model.input_time, model.output_time);

    print_result(&model, param);

free:
    free_list(queue.queue);

    return rc;
}
