#include "defines.h"
#include "print.h"
#include "read.h"
#include "operations.h"

int main(void)
{
    key_t arr_keys[MAX_STUDENT];
    student_t arr_students[MAX_STUDENT];
    size_t count_students = 0;

    int rc = 0;
    int8_t menu_item = 0;

    while (true)
    {
        print_menu();
        if (scanf("%hhd", &menu_item) != 1)
        {
            return ERR_MENU_ITEM;
        }

        if (menu_item == 0)
        {
            break;
        }

        if ((rc = execute_menu_item(arr_keys, arr_students, &count_students, menu_item)) != 0)
        {
            return rc;
        }
    }
    
    return rc;
}
