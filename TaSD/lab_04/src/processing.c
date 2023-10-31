#include "processing.h"

int execute_menu_item(int8_t menu_item,
                      stack_array_t *stack_array,
                      bool *const check_stack_array,
                      stack_list_t **stack_list,
                      bool *const add_first_elem,
                      free_addr_t *const free_addr,
                      int *const size_stack_list)
{
    int rc = 0;
    data_t data;
    stack_list_t *tmp_elem_free;
    char exp[MAX_SIZE_EXP + 2];
    data_t *ptr;
    int capacity;

    switch (menu_item)
    {
    case 1:
        if (*check_stack_array)
        {
            printf(YELLOW "\n[+] Стек как массив уже был создан ранее!\n" RESET);
            return 0;
        }
        if ((rc = input_size_stack_array(&stack_array->capacity)) != 0)
            return rc;
        if ((rc = create_stack_array(stack_array)) != 0)
            return rc;
        printf(GREEN "\n[+] Cтек как массив успешно создан!\n" RESET);
        *check_stack_array = true;
        break;
    case 2:
        if (!*check_stack_array)
        {
            printf(VIOLET "\n[-] Стек как массив еще не создан!\n" VIOLET);
            return 0;
        }
        if (stack_array->top + 1 + 1 > stack_array->capacity)
        {
            printf(VIOLET "\n[-] Стек как массив переполнен!\n" RESET);
            return 0;
        }
        if ((rc = input_data(&data)) != 0)
            return rc;
        stack_array_push(stack_array, data);
        printf(GREEN "\n[+] Элемент успешно добавлен в стек!\n" RESET);
        break;
    case 3:
        if (!*check_stack_array)
        {
            printf(VIOLET "\n[-] Стек как массив еще не создан!\n" RESET);
            return 0;
        }
        if (isempty_stack_array(stack_array))
        {
            printf(VIOLET "\n[-] Стек как массив пустой! Удалять нечего!\n" RESET);
            return 0;
        }
        ptr = &stack_array->array_data[stack_array->top];
        stack_array_pop(stack_array);
        printf(GREEN "\n[+] Элемент c адресом %p был успешно удален из стека!\n" RESET,
               (void *)ptr);
        break;
    case 4:
        if (!*check_stack_array)
        {
            printf(VIOLET "\n[-] Стек как массив еще не создан!\n" RESET);
            return 0;
        }
        if (isempty_stack_array(stack_array))
        {
            printf(VIOLET "\n[-] Стек как массив пустой!\n" RESET);
            return 0;
        }
        print_stack_array(stack_array);
        break;
    case 5:
        if (!*check_stack_array)
        {
            printf(VIOLET "\n[-] Стек как массив еще не создан!\n" RESET);
            return 0;
        }
        if (stack_array->top + 1 + 1 > stack_array->capacity)
        {
            printf(VIOLET "\n[-] Стек как массив переполнен!\n" RESET);
            return 0;
        }
        if ((rc = input_expression_with_bracked(exp)) != 0)
            return rc;
        if ((int)strlen(exp) > stack_array->capacity)
        {
            printf(VIOLET "\n[-] Размеров стека недостаточно "
                          "для анализа введенного выражения!\n" RESET);
            return 0;
        }

        capacity = stack_array->capacity;
        stack_array_clean(stack_array);
        stack_array->capacity = capacity;
        create_stack_array(stack_array);

        if (balanced_parentheses_stack_array(stack_array, exp))
        {
            printf(GREEN "\n[+] Скобки в введенном выражении "
                         "сбалансированны!\n" RESET);
            return 0;
        }
        else
        {
            printf(VIOLET "\n[-] Скобки в введенном выражении "
                          "не сбалансированны!\n" RESET);
            return 0;
        }
        
        break;
    case 6:
        if (!*check_stack_array)
        {
            printf(VIOLET "\n[-] Стек как массив еще не создан! "
                          "Очищать нечего!\n" RESET);
            return 0;
        }
        stack_array_clean(stack_array);
        *check_stack_array = false;
        printf(GREEN "\n[+] Стек как массив был успешно очищен! "
                     "\n[+] Создайте стек, чтобы продолжить работу!\n" RESET);
        break;
    case 7:
        if (*stack_list != NULL)
        {
            printf(YELLOW "\n[+] Стек как список уже был создан ранее!\n" RESET);
            return 0;
        }
        data.symbol = 'a'; // любой может быть символ; нужен для того, чтобы создать стек
        if ((*stack_list = create_stack_list(data)) == NULL)
        {
            printf(RED "[-] Ошибка создания стека как списка!\n" RESET);
            return ERR_MEM_ALLOC;
        }
        printf(GREEN "\n[+] Cтек как список успешно создан!\n" RESET);
        break;
    case 8:
        if (*stack_list == NULL)
        {
            printf(VIOLET "\n[-] Стек как список еще не создан!\n" RESET);
            return 0;
        }
        if (*size_stack_list + 1 > MAX_STACK_LIST_SIZE)
        {
            printf(VIOLET "\n[-] Стек как список переполнен!\n" RESET);
            return 0;
        }
        if ((rc = input_data(&data)) != 0)
            return rc;
        if (!*add_first_elem)
        {
            (*stack_list)->data = data;
            *add_first_elem = true;
        }
        else
        {
            stack_list_t *elem = create_stack_list(data);
            if (elem)
                *stack_list = stack_list_push(*stack_list, elem);
            else
            {
                printf(RED "[-] Ошибка добавления элемента в стек!\n" RESET);
                return ERR_MEM_ALLOC;
            }
        }
        printf(GREEN "\n[+] Элемент успешно добавлен в стек!\n" RESET);
        (*size_stack_list)++;
        break;
    case 9:
        if (*stack_list == NULL)
        {
            printf(VIOLET "\n[-] Стек как список еще не создан!\n" RESET);
            return 0;
        }

        if (*add_first_elem)
        {
            if (isempty_stack_list(*stack_list))
            {
                printf(VIOLET "\n[-] Стек как список пустой! Удалять нечего!\n" RESET);
                return 0;
            }
        }
        else
        {
            if (isempty_stack_list((*stack_list)->next))
            {
                printf(VIOLET "\n[-] Стек как список пустой! Удалять нечего!\n" RESET);
                return 0;
            }
        }

        tmp_elem_free = *stack_list;

        *stack_list = stack_list_pop(*stack_list);

        if (check_unique_address(free_addr, tmp_elem_free))
        {
            if (free_addr->top + 1 >= MAX_FREE_ADDR_SIZE)
                printf(VIOLET "\n[-] Массив свободных адресов переполнен!\n"
                              "[-] Освобожденный адрес не будет добавлен в массив!\n" RESET);
            else
                free_addr->array_free_addr[++free_addr->top] = (size_t *)tmp_elem_free;
        }
        (*size_stack_list)--;

        if (*stack_list != NULL)
            printf(GREEN "\n[+] Элемент c адресом (%p) "
                         "был успешно удален из стека!\n" RESET,
                   (void *)tmp_elem_free);
        else
        {
            printf(YELLOW "\n[+] Из стека был удален последний элемент. Его адрес - (%p)"
                          "\n[+] Создайте стек, чтобы продолжить работу!\n" RESET,
                   (void *)tmp_elem_free);
            *add_first_elem = false;
        }
        break;
    case 10:
        print_free_address(free_addr);
        if (*stack_list == NULL)
        {
            printf(VIOLET "\n[-] Стек как список еще не создан!\n" RESET);
            return 0;
        }

        if (*add_first_elem)
        {
            if (isempty_stack_list(*stack_list))
            {
                printf(VIOLET "\n[-] Стек как список пустой!\n" RESET);
                return 0;
            }
        }
        else
        {
            if (isempty_stack_list((*stack_list)->next))
            {
                printf(VIOLET "\n[-] Стек как список пустой!\n" RESET);
                return 0;
            }
        }
        print_stack_list(*stack_list);
        break;
    case 11:
        if (*stack_list == NULL)
        {
            printf(VIOLET "\n[-] Стек как список еще не создан!\n" RESET);
            return 0;
        }
        if ((rc = input_expression_with_bracked(exp)) != 0)
            return rc;

        stack_list_clean(stack_list);
        *add_first_elem = false;
        *size_stack_list = 0;

        data.symbol = 'a'; // любой может быть символ; нужен для того, чтобы создать стек
        if ((*stack_list = create_stack_list(data)) == NULL)
        {
            printf(RED "[-] Ошибка создания стека как списка!\n" RESET);
            return ERR_MEM_ALLOC;
        }
        if (balanced_parentheses_stack_list(stack_list, exp))
        {
            printf(GREEN "\n[+] Скобки в введенном выражении "
                         "сбалансированны!\n" RESET);
            return 0;
        }
        else
        {
            printf(VIOLET "\n[-] Скобки в введенном выражении "
                          "не сбалансированны!\n" RESET);
            return 0;
        }

        *add_first_elem = false;
        *size_stack_list = 0;

        break;
    case 12:
        if (*stack_list == NULL)
        {
            printf(VIOLET "\n[-] Стек как список еще не создан! "
                          "Очищать нечего!\n" RESET);
            return 0;
        }

        tmp_elem_free = *stack_list;

        while (tmp_elem_free != NULL)
        {
            if (check_unique_address(free_addr, tmp_elem_free))
            {
                if (free_addr->top + 1 >= MAX_FREE_ADDR_SIZE)
                {
                    printf(VIOLET "\n[-] Массив свободных адресов переполнен!\n"
                                  "[-] Оставшиеся свободные адреса не будут добавлены в массив!\n" RESET);
                    break;
                }

                free_addr->array_free_addr[++free_addr->top] = (size_t *)tmp_elem_free;
            }

            tmp_elem_free = tmp_elem_free->next;
        }

        stack_list_clean(stack_list);

        *add_first_elem = false;
        *size_stack_list = 0;

        printf(GREEN "\n[+] Стек как список был успешно очищен! "
                     "\n[+] Создайте стек, чтобы продолжить работу!\n" RESET);
        break;
    case 13:
        if ((rc = get_expression_with_bracked_from_file(exp, DATA)) != 0)
            return rc;

        printf(GREEN "\n[+] Выражение было успешно получено из файла!\n" RESET);

        if (!*check_stack_array)
        {
            printf(VIOLET "\n[-] Стек как массив еще не создан!\n" RESET);
            return 0;
        }
        if (stack_array->top + 1 + 1 > stack_array->capacity)
        {
            printf(VIOLET "\n[-] Стек как массив переполнен!\n" RESET);
            return 0;
        }

        if ((int)strlen(exp) > stack_array->capacity)
        {
            printf(VIOLET "\n[-] Размеров стека как массива недостаточно "
                          "для анализа введенного выражения!\n" RESET);
            return 0;
        }

        if (*stack_list == NULL)
        {
            printf(VIOLET "\n[-] Стек как список еще не создан!\n" RESET);
            return 0;
        }
        if (*size_stack_list + 1 > MAX_STACK_LIST_SIZE)
        {
            printf(VIOLET "\n[-] Стек как список переполнен!\n" RESET);
            return 0;
        }
        if ((int)strlen(exp) > MAX_STACK_LIST_SIZE)
        {
            printf(VIOLET "\n[-] Размеров стека как списка недостаточно "
                          "для анализа введенного выражения!\n" RESET);
            return 0;
        }

        print_result(exp, stack_array, stack_list);

        break;
    default:
        printf(RED "\n[-] Неверный пункт меню! "
                   "\n[-] Hомер пункта меню - цело число от 1 до 6.\n" RESET);
        return ERR_MENU_ITEM;
    }

    /*
    при удалении последнего элемента из стека как списка
    и при попытке последующего вывода стека пишет, что стек еще не создан
    - проверить то, что в выражении нет никаких скобок
    - адреса для реализации массивом
    */

    return rc;
}
