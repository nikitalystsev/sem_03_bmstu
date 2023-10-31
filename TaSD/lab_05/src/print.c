#include "print.h"

void print_task_menu(const param_t *const param)
{
    printf(TURQ "\n--------------------------------------------------------|\n");
    printf("Параметры обработки и добавления по умолчанию:\n");
    printf("Добавление: от 0 до 6 е.в.\n");
    printf("Обработка:  от 0 до 1 е.в.\n");

    printf("Текущие параметры обработки и добавления:\n");
    printf("Добавление: от %10.6lf до %10.6lf е.в.\n",
           param->min_add_time, param->max_add_time);
    printf("Обработка:  от %10.6lf до %10.6lf е.в.\n",
           param->min_process_time, param->max_process_time);

    printf("1 - Изменить время обработки;\n");
    printf("2 - Изменить время добавления;\n");
    printf("3 - Cмоделировать СМО, используя очередь в виде списка;\n");
    printf("4 - Cмоделировать СМО, используя очередь в виде массива;\n");
    printf("5 - Вывести информацию об использованных и освобожденных \n");
    printf("    адресах при моделировании очереди в виде списка. \n");
    printf("\n0 - Выйти из программы.\n");
    printf("--------------------------------------------------------|\n");
    printf("\nВыберите пункт меню:\n" RESET);
}

void print_menu(void)
{
    printf(
        TURQ "\n----------------------------------------------------------|\n"
             "Очередь реализована двумя способами:\n"
             "а) массивом;\n"
             "б) списком.\n"

             "\nОперации с очередью в виде массива:\n"
             "1  - создать очередь;\n"
             "2  - добавить элемент в очередь;\n"
             "3  - удалить элемент из очереди;\n"
             "4  - вывести текущее состояние очереди;\n"
             "5  - очистить очередь;\n"

             "\nОперации с очередью в виде односвязного линейного списка:\n"
             "6  - создать очередь;\n"
             "7  - добавить элемент в очередь;\n"
             "8  - удалить элемент из очереди;\n"
             "9  - вывести текущее состояние очереди;\n"
             "10 - очистить очередь;\n"
             "11 - вывести массив ранее освобожденных адресов;\n"
             "12 - вывести сравнение времен работы различных функции\n"
             "     для работы с очередью\n"
             "13 - вывести сравнение представления по памяти\n"
             "     очереди как списка и очереди как массива\n"
             "\n0  - выйти из программы.\n"
             "\n----------------------------------------------------------|\n"
             "Выберите пункт меню:\n" RESET);
}

void print_intermediate(const model_t *const model)
{
    printf(GREEN "\n\n|--------------------------------------------|------------|\n");
    printf("│    Количество вышедших заявок заявок       │ %10d │\n", model->count_output);
    printf("|--------------------------------------------|------------|\n");
    printf("│          Текушая длина очереди             │ %10d |\n", model->curr_len_queue);
    printf("|--------------------------------------------|------------|\n");
    printf("│          Средняя длина очереди             │  %9.6lf │\n", model->av_len_queue);
    printf("|--------------------------------------------|------------|\n" RESET);
}

void print_result(const model_t *const model, const param_t *const param)
{
    double theor_input_time = ((param->max_add_time + param->min_add_time) / 2) * param->count_appl;
    double theor_output_time = ((param->max_process_time + param->min_process_time) / 2) * param->count_appl * COUNT_PROCESS;
    double theor_model_time = max_double(theor_input_time, theor_output_time);
    double theor_downtime = theor_input_time - theor_output_time;
    // int16_t theor_count_calls_machine = param->count_appl * COUNT_PROCESS;

    double fault_input = (100 * fabs(model->input_time - theor_input_time)) / theor_input_time;
    double fault_output = (100 * fabs(model->output_time - theor_output_time)) / theor_output_time;
    double fault_model = (100 * fabs(model->model_time - theor_model_time)) / theor_model_time;

    printf(YELLOW "\n|-------------------------------------------------------------------------------|\n");
    printf("│             Название                │    Практические    │    Теоретические   │\n");
    printf("|-------------------------------------|--------------------|--------------------|\n");
    printf("│     Общее время моделирования       │ %13.6lf е.в. │ %10.0lf е.в.    │\n", model->model_time, theor_model_time);
    printf("|-------------------------------------|--------------------|--------------------|\n");
    printf("│   Общее время добавления заявок     │ %13.6lf е.в. │ %10.0lf е.в.    │\n", model->input_time, theor_input_time);
    printf("|-------------------------------------|--------------------|--------------------|\n");
    printf("│   Общее время обработки заявок      │ %13.6lf е.в. │ %10.0lf е.в.    │\n", model->output_time, theor_output_time);
    printf("|-------------------------------------|--------------------|--------------------|\n");
    if (model->downtime >= 0)
    {
        printf("│         Время простоя ОА            │ %13.6lf е.в. │ %10.0lf е.в.    │\n", model->downtime, theor_downtime);
        printf("|-------------------------------------|--------------------|--------------------|\n");
    }
    printf("│      Количество срабатываний        │             %10d                  │\n", model->count_calls_machine);
    printf("|-------------------------------------|-----------------------------------------|\n");
    printf("│     Количество вошедших заявок      │             %10d                  │\n", model->count_input);
    printf("|-------------------------------------|-----------------------------------------|\n");
    printf("│     Количество вышедших заявок      │             %10d                  │\n", model->count_output);
    printf("|-------------------------------------|-----------------------------------------|\n");
    printf("│    Время работы программы (мкс)     │               %15.6Lf           │\n", model->work_time);
    printf("|-------------------------------------|-----------------------------------------|\n");
    printf("│   Требуемый обьем памяти (байты)    │             %10d                  │\n", model->memory_size);
    printf("|-------------------------------------------------------------------------------|\n");
    printf("│                  Расчет погрешности                      │     Результат      │\n");
    printf("|----------------------------------------------------------|--------------------|\n");
    printf("│           -------Погрешность по входу--------            │                    │\n");
    printf("│     100 * |Практ. время добавл. - Теорит.| / Теорет.     │ %10.6lf процент │\n", fault_input);
    printf("|----------------------------------------------------------|--------------------|\n");
    printf("│           -------Погрешность по выходу--------           │                    │\n");
    printf("│     100 * |Практ. время обр. - Теорит. | / Теорет.       │ %10.6lf процент │\n", fault_output);
    printf("|-------------------------------------------------------------------------------|\n");
    printf("│       -------Погрешность моделирования--------           │                    │\n");
    printf("│     100 * |Практ. время модел. - Теорит. | / Теорет.     │ %10.6lf процент │\n", fault_model);
    printf("|-------------------------------------------------------------------------------|\n" RESET);
}

static int get_queue_arr_size(const queue_arr_t *const queue)
{
    int size = 0;

    size += sizeof(queue->size);
    size += sizeof(queue->p_in);
    size += sizeof(queue->p_out);
    size += (sizeof(queue->queue[0]) * queue->size);

    return size;
}

int print_size_info(void)
{
    queue_arr_t queue_arr;
    queue_arr.size = 1001;
    queue_arr.queue = NULL;

    queue_list_t queue_list;
    queue_list.queue = NULL;
    queue_list.size = 0;

    int rc = 0;
    if ((rc = create_queue_arr(&queue_arr)) != 0)
        goto free;

    printf(YELLOW "\n|-------------------------------------------------------------------------------------|\n");
    printf("│ Количество элементов │    Размер списка (байты)    │     Размер массива (байты)     │\n");
    printf("|-------------------------------------------------------------------------------------|\n");
    for (int i = 0; i < queue_arr.size; i++)
    {
        elem_t data = {.add_time = 0, .count_iter = 0, .process_time = 0};

        if (i % 100 == 0)
        {
            int size_arr = get_queue_arr_size(&queue_arr);
            int size_list = queue_list_size_in_bytes(&queue_list);

            printf("|      %10d      |         %10d          |           %10d           |\n", i, size_list, size_arr);
            printf("|-------------------------------------------------------------------------------------|\n");
        }

        push_queue_arr(&queue_arr, &data);
        list_t *node = create_node(data);
        queue_list.queue = push_queue_list(queue_list.queue, node);
        queue_list.size++;
    }

    printf(RESET);

free:
    free_list(queue_list.queue);
    free(queue_arr.queue);

    return rc;
}

int print_add_queue_time(void)
{
    int rc = 0;

    queue_arr_t queue_arr;
    queue_arr.size = 1050;
    queue_arr.queue = NULL;

    queue_list_t queue_list;
    queue_list.queue = NULL;
    queue_list.size = 0;

    if ((rc = create_queue_arr(&queue_arr)) != 0)
        goto free;

    printf(YELLOW "\n|-----------------------------------------------------------|\n");
    printf("│                      │     Добавление элемента (мкс)      │\n");
    printf("| Количество элементов |------------------------------------|\n");
    printf("│                      │      Список     │      Массив      │\n");
    printf("|-----------------------------------------------------------|\n");

    for (int i = 0; i < queue_arr.size; i++)
    {
        elem_t data = {.add_time = 0, .count_iter = 0, .process_time = 0};

        long double beg = microseconds_now();
        push_queue_arr(&queue_arr, &data);
        long double end = microseconds_now() - beg;

        list_t *node = create_node(data);

        beg = microseconds_now();
        queue_list.queue = push_queue_list(queue_list.queue, node);
        long double end2 = microseconds_now() - beg;

        queue_list.size++;

        if (i == 10)
        {
            printf("|      %10d      |   %13.6Lf |    %13.6Lf |\n", i, end2, end);
            printf("|-----------------------------------------------------------|\n");
        }
        if (i % 100 == 0 && i != 0)
        {
            printf("|      %10d      |   %13.6Lf |    %13.6Lf |\n", i, end2, end);
            printf("|-----------------------------------------------------------|\n");
        }
    }

    printf(RESET);

free:
    free_list(queue_list.queue);
    free(queue_arr.queue);

    return rc;
}

int print_pop_queue_time(void)
{
    int rc = 0;

    queue_arr_t queue_arr;
    queue_arr.size = 1000;
    queue_arr.queue = NULL;

    queue_list_t queue_list;
    queue_list.queue = NULL;
    queue_list.size = 0;

    if ((rc = create_queue_arr(&queue_arr)) != 0)
        goto free;

    printf(YELLOW "\n|-----------------------------------------------------------|\n");
    printf("│                      │      Удаление элемента (мкс)       │\n");
    printf("| Количество элементов |------------------------------------|\n");
    printf("│                      │      Список     │      Массив      │\n");
    printf("|-----------------------------------------------------------|\n");

    for (int i = 0; i < queue_arr.size; i++)
    {
        elem_t data = {.add_time = 0, .count_iter = 0, .process_time = 0};
        push_queue_arr(&queue_arr, &data);
        list_t *node = create_node(data);
        queue_list.queue = push_queue_list(queue_list.queue, node);
        queue_list.size++;
    }

    for (int i = queue_list.size; i > 0; i--)
    {
        elem_t elem;

        long double beg = microseconds_now();
        pop_queue_arr(&queue_arr, &elem);
        long double end = microseconds_now() - beg;

        beg = microseconds_now();
        queue_list.queue = pop_queue_list(queue_list.queue, &elem);
        long double end2 = microseconds_now() - beg;

        queue_list.size--;

        if (i == 10)
        {
            printf("|      %10d      |   %13.6Lf |    %13.6Lf |\n", i, end2, end);
            printf("|-----------------------------------------------------------|\n");
        }
        if (i % 100 == 0 && i != 0)
        {
            printf("|      %10d      |   %13.6Lf |    %13.6Lf |\n", i, end2, end);
            printf("|-----------------------------------------------------------|\n");
        }
    }

    printf(RESET);

free:
    free_list(queue_list.queue);
    free(queue_arr.queue);

    return rc;
}

int print_clean_queue_time(void)
{
    int rc = 0;

    queue_arr_t queue_arr;
    queue_list_t queue_list;

    printf(YELLOW "\n|-----------------------------------------------------------|\n");
    printf("│                      │       Очистка очереди (мкс)        │\n");
    printf("| Количество элементов |------------------------------------|\n");
    printf("│                      │      Список     │      Массив      │\n");
    printf("|-----------------------------------------------------------|\n");

    int count = 10;

    for (int j = 0; j < 11; j++)
    {
        queue_arr.size = count;
        queue_arr.queue = NULL;

        queue_list.queue = NULL;
        queue_list.size = 0;

        if ((rc = create_queue_arr(&queue_arr)) != 0)
            return rc;

        for (int i = 0; i < queue_arr.size; i++)
        {
            elem_t data = {.add_time = 0, .count_iter = 0, .process_time = 0};
            push_queue_arr(&queue_arr, &data);
            list_t *node = create_node(data);
            queue_list.queue = push_queue_list(queue_list.queue, node);
            queue_list.size++;
        }

        long double beg = microseconds_now();
        free(queue_arr.queue);
        long double end = microseconds_now() - beg;

        beg = microseconds_now();
        free_list(queue_list.queue);
        long double end2 = microseconds_now() - beg;

        if (count == 10)
        {
            printf("|      %10d      |   %13.6Lf |    %13.6Lf |\n", count, end2, end);
            printf("|-----------------------------------------------------------|\n");
        }
        if (count % 100 == 0 && j != 0)
        {
            printf("|      %10d      |   %13.6Lf |    %13.6Lf |\n", count, end2, end);
            printf("|-----------------------------------------------------------|\n");
        }

        if (j == 0)
            count = 100;
        else
            count += 100;
    }

    printf(RESET);

    return rc;
}

int print_create_queue_time(void)
{
    int rc = 0;

    queue_arr_t queue_arr;
    queue_arr.size = 1000;
    queue_list_t queue_list;
    queue_list.queue = NULL;
    queue_list.size = 0;

    printf(YELLOW "\n|-----------------------------------------------------------|\n");
    printf("│                   Cоздание очереди (мкс)                  │\n");
    printf("|-----------------------------------------------------------|\n");
    printf("│          Список          |              Массив            │\n");
    printf("|-----------------------------------------------------------|\n");

    long double beg = microseconds_now();
    create_queue_arr(&queue_arr);
    long double end = microseconds_now() - beg;

    elem_t data = {.add_time = 0, .count_iter = 0, .process_time = 0};
    list_t *node = create_node(data);

    beg = microseconds_now();
    queue_list.queue = push_queue_list(queue_list.queue, node);
    long double end2 = microseconds_now() - beg;

    printf("|   %13.6Lf          |         %13.6Lf          |\n", end2, end);

    printf("|-----------------------------------------------------------|\n" RESET);

    free_list(queue_list.queue);
    free(queue_arr.queue);

    return rc;
}

int print_func_time(void)
{
    int rc = 0;

    if ((rc = print_add_queue_time()) != 0)
        return rc;

    if ((rc = print_pop_queue_time()) != 0)
        return rc;

    if ((rc = print_clean_queue_time()) != 0)
        return rc;

    if ((rc = print_create_queue_time()) != 0)
        return rc;

    return rc;
}
