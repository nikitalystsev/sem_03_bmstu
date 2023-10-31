#include "print.h"

void print_menu(void)
{
    printf(
        TURQ "\n-----------------------------------------------------------------------|\n"
             "Программа для проверки правильности скобок в выражении c помощью стека.\n"
             "Стек реализован двумя способами:\n"
             "а) массивом;\n"
             "б) списком.\n"

             "\nОперации со с стеком в виде массива:\n"
             "1  - создать стек;\n"
             "2  - добавить элемент в стек;\n"
             "3  - удалить элемент из стека;\n"
             "4  - вывести текущее состояние стека;\n"
             "5  - проверить правильность расстановки скобок в выражении;\n"
             "6  - очистить стек;\n"

             "\nОперации со с стеком в виде односвязного линейного списка:\n"
             "7  - создать стек;\n"
             "8  - добавить элемент в стек;\n"
             "9  - удалить элемент из стека;\n"
             "10 - вывести текущее состояние стека;\n"
             "11 - проверить правильность расстановки скобок в выражении;\n"
             "12 - очистить стек;\n"
             "\n13 - вывод времени работы программы и\n"
             "     различных функций для работы со стеком;\n"
             "\n0  - выйти из программы.\n"
             "-----------------------------------------------------------------------|\n"
             "Выберите пункт меню:\n" RESET);
}

void print_timing(const char *const exp,
                  stack_array_t *stack_array,
                  stack_list_t **stack_list)
{
    long double beg, end;
    long double sum_arr = 0, sum_list = 0;

    beg = microseconds_now();
    balanced_parentheses_stack_array(stack_array, exp);
    end = microseconds_now() - beg;
    sum_arr += end;

    beg = microseconds_now();
    balanced_parentheses_stack_list(stack_list, exp);
    end = microseconds_now() - beg;
    sum_list += end;

    printf("\n[+] Количество символов в считанном выражении: %lu\n", strlen(exp));
    printf("\n[+] Время работы программы, "
           "использующей стек как массив (микросекунды): %Lf\n",
           sum_arr);
    printf("[+] Время работы программы, "
           "использующей стек как список (микросекунды): %Lf\n",
           sum_list);

    printf("\n[+] Объем занимаемой памяти стека как массива (байты): % ld\n",
           strlen(exp) * sizeof(data_t) + 2 * sizeof(int));
    printf("[+] Объем занимаемой памяти стека как списка (байты): % ld\n",
           strlen(exp) * (sizeof(data_t) + sizeof(stack_list_t *)));
}

void print_func_time(void)
{
    long double beg, end;

    long double cr_sum_arr = 0, cr_sum_list = 0;
    long double sum_push_arr = 0, sum_push_list = 0;
    long double sum_pop_arr = 0, sum_pop_list = 0;
    long double sum_clean_arr = 0, sum_clean_list = 0;

    data_t data = {.symbol = 'a'};

    for (int i = 0; i < N_REPS; i++)
    {
        stack_array_t stack_array;
        stack_array.capacity = 2;

        beg = microseconds_now();
        create_stack_array(&stack_array);
        end = microseconds_now() - beg;
        cr_sum_arr += end;

        beg = microseconds_now();
        stack_list_t *stack_list = create_stack_list(data);
        end = microseconds_now() - beg;
        cr_sum_list += end;

        beg = microseconds_now();
        stack_array_push(&stack_array, data);
        end = microseconds_now() - beg;
        sum_push_arr += end;

        stack_list_t *list_elem = create_stack_list(data);
        beg = microseconds_now();
        stack_list = stack_list_push(stack_list, list_elem);
        end = microseconds_now() - beg;
        sum_push_list += end;

        beg = microseconds_now();
        stack_array_pop(&stack_array);
        end = microseconds_now() - beg;
        sum_pop_arr += end;

        beg = microseconds_now();
        stack_list = stack_list_pop(stack_list);
        end = microseconds_now() - beg;
        sum_pop_list += end;

        beg = microseconds_now();
        stack_array_clean(&stack_array);
        end = microseconds_now() - beg;
        sum_clean_arr += end;

        beg = microseconds_now();
        stack_list_clean(&stack_list);
        end = microseconds_now() - beg;
        sum_clean_list += end;
    }

    cr_sum_arr /= N_REPS;
    cr_sum_list /= N_REPS;

    sum_push_arr /= N_REPS;
    sum_push_list /= N_REPS;

    sum_pop_arr /= N_REPS;
    sum_pop_list /= N_REPS;

    sum_clean_arr /= N_REPS;
    sum_clean_list /= N_REPS;

    printf("\n[+] Время работы функции создания стека как массива (микросекунды): %Lf\n", cr_sum_arr);
    printf("[+] Время работы функции создания стека как списка (микросекунды): %Lf\n", cr_sum_list);

    printf("\n[+] Время работы функции добавления элемента в стек как массив (микросекунды): %Lf\n", sum_push_arr);
    printf("[+] Время работы функции добавления элемента в стек как список (микросекунды): %Lf\n", sum_push_list);

    printf("\n[+] Время работы функции удаления элемента из стека как массива (микросекунды): %Lf\n", sum_pop_arr);
    printf("[+] Время работы функции удаления элемента из стека как списка (микросекунды): %Lf\n", sum_pop_list);

    printf("\n[+] Время работы функции очистки стека как массива (микросекунды): %Lf\n", sum_clean_arr);
    printf("[+] Время работы функции очистки стека как списка (микросекунды): %Lf\n" , sum_clean_list);
}

void print_result(const char *const exp,
                  stack_array_t *stack_array,
                  stack_list_t **stack_list)
{
    printf(YELLOW "\n----------------------------------------------------------------------------------------|\n");
    printf("Время работы программы по функций для работы со стеком:\n");

    print_timing(exp, stack_array, stack_list);
    print_func_time();

    printf(YELLOW "----------------------------------------------------------------------------------------|\n"RESET);
}
