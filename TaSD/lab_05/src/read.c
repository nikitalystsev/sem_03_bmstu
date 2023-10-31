#include "read.h"

int read_menu_item(int8_t *const item)
{
    if (scanf("%hhd", item) != 1)
    {
        puts(RED "[-] Некорректный ввод пункта меню! "
                 "Пункт меню - целое число от 0 до 11" RESET);
        return ERR_READ_ITEM;
    }

    if (*item < 0 || *item > 13)
    {
        puts(RED "[-] Неверный ввод пункта меню! "
                 "Пункт меню - целое число от 0 до 13" RESET);
        return ERR_ITEM;
    }

    return EXIT_SUCCESS;
}

int read_size_queue_array(int *const size)
{
    puts("Введите размер очереди как массива (целое число от 1 до 10000):");

    if (scanf("%d", size) != 1)
    {
        puts(RED "[-] Некорректный ввод размера очереди!" RESET);
        return ERR_READ_SIZE;
    }

    if (*size < 1 || *size > MAX_INPUT_SIZE)
    {
        puts(RED "[-] Неверный ввод размера очереди! "
                 "Размер очереди - целое число от 1 до 10000" RESET);
        return ERR_SIZE;
    }

    return EXIT_SUCCESS;
}

int read_queue_elem(int *const num)
{
    puts("Введите элемент очереди - целое число:");

    if (scanf("%d", num) != 1)
    {
        puts(RED "[-] Некорректный ввод элемента очереди!" RESET);
        return ERR_QUEUE_ELEM;
    }

    return EXIT_SUCCESS;
}

int read_work_num(int *const number)
{
    puts(TURQ "Программа для работы с очередью. \n"
              "Позволяет смоделировать СМО, "
              "а также работать с очередью вручную\n");

    puts("\nВведите значение 0,"
         " если хотите решить задачу моделирования СМО "
         ", или введите значение 1, "
         "если хотите работать с очередью в ручном режиме:\n" RESET);

    if (scanf("%d", number) != 1)
    {
        puts(RED "[-] Некорректный ввод значения! "
                 "Выбор - целое число от 0 до 1" RESET);
        return ERR_READ_WORK;
    }

    if (*number < 0 || *number > 1)
    {
        puts(RED "[-] Неверный ввод значения! "
                 "Выбор - целое число от 0 до 1" RESET);
        return ERR_WORK;
    }

    return EXIT_SUCCESS;
}

int read_task_menu_item(int8_t *const item)
{
    if (scanf("%hhd", item) != 1)
    {
        puts(RED "[-] Некорректный ввод пункта меню! "
                 "Пункт меню - целое число от 0 до 5" RESET);
        return ERR_READ_ITEM;
    }

    if (*item < 0 || *item > 5)
    {
        puts(RED "[-] Неверный ввод пункта меню! "
                 "Пункт меню - целое число от 0 до 5" RESET);
        return ERR_ITEM;
    }

    return EXIT_SUCCESS;
}

int read_range_time(double *const min, double *const max)
{
    puts("\nВведите минимальное значение времени:");

    if (scanf("%lf", min) != 1)
    {
        puts(RED "[-] Некорректный ввод минимального времени!" RESET);
        return ERR_READ_TIME;
    }

    puts("\nВведите максимальное значение времени:");

    if (scanf("%lf", max) != 1)
    {
        puts(RED "[-] Некорректный ввод максимального времени!" RESET);
        return ERR_READ_TIME;
    }

    if (*min >= *max)
    {
        puts(RED "[-] Неверный ввод! "
                   "Минимум не дожен быть больше максимума!" RESET);
        return ERR_TIME;
    }

    if (*min < 0 || *max < 0)
    {
        puts(RED "[-] Неверный ввод! "
                   "Значения не могут быть отрицательными!" RESET);
        return ERR_TIME;
    }

    return EXIT_SUCCESS;
}
