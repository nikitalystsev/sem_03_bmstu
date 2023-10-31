#include "processing.h"

int main(void)
{
    int rc = 0;
    int8_t menu_item = 0;

    stack_array_t stack_array;
    stack_list_t *stack_list = NULL;

    free_addr_t free_addr;
    free_addr.top = -1;

    bool check_stack_array = false, add_first_elem = false;

    int size_stack_list = 0;
    while (true)
    {
        print_menu();
        if (scanf("%hhd", &menu_item) != 1)
        {
            printf(RED "\n[-] Некорректный ввод пункта меню!\n" RESET);
            return ERR_MENU_ITEM;
        }

        if (menu_item == 0)
        {
            break;
        }

        if ((rc = execute_menu_item(menu_item,
                                    &stack_array,
                                    &check_stack_array,
                                    &stack_list,
                                    &add_first_elem,
                                    &free_addr,
                                    &size_stack_list)) != 0)
        {
            return rc;
        }
    }

    return rc;
}
