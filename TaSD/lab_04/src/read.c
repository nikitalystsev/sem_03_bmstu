#include "read.h"

int input_expression_with_bracked(char *const exp)
{
    printf(TURQ "\nВведите выражение, содержащее скобки, без пробелов "
                "(не более 10000 символов):\n" RESET);
    if (scanf("%s", exp) != 1)
    {
        printf(RED "[-] Некорректный ввод выражения, содержащего скобки!\n" RESET);
        return ERR_READ_EXPR;
    }
    if (strlen(exp) > MAX_SIZE_EXP)
    {
        printf(RED "[-] Неверный ввод! Была превышена максимально "
                   "допустимая длина выражения! \n" RESET);
        return ERR_READ_EXPR;
    }

    return EXIT_SUCCESS;
}

int get_expression_with_bracked_from_file(char *const exp,
                                          const char *const file_name)
{
    FILE *file;

    if ((file = fopen(file_name, "r")) == NULL)
        return ERR_OPEN_FILE;

    if (fscanf(file, "%s", exp) != 1)
    {
        printf(RED "[-] Некорректный ввод выражения, содержащего скобки!\n" RESET);
        fclose(file);
        return ERR_READ_EXPR;
    }
    if (strlen(exp) > MAX_SIZE_EXP)
    {
        printf(RED "[-] Неверный ввод! Была превышена максимально "
                   "допустимая длина выражения! \n" RESET);
        fclose(file);
        return ERR_READ_EXPR;
    }

    fclose(file);

    return EXIT_SUCCESS;
}

int input_size_stack_array(int *const count)
{
    printf(TURQ "\nВведите вместимость стека как массива "
                "целое число от 1 до 10000):\n" RESET);

    if (scanf("%d", count) != 1)
    {
        printf(RED "\n[-] Некорректный ввод вместимости стека!\n" RESET);
        return ERR_READ_STACK_SIZE;
    }
    if (*count < MIN_STACK_ARRAY_SIZE ||
        *count > MAX_STACK_ARRAY_SIZE)
    {
        printf(RED "\n[-] Неверный ввод! "
                   "\n[-] Вместимость стека - цело число от 1 до 10000!\n" RESET);
        return ERR_READ_STACK_SIZE;
    }

    return EXIT_SUCCESS;
}

int input_data(data_t *const data)
{
    printf(TURQ "\nВведите символ для добавления его в стек:\n" RESET);

    if (scanf("%s", &data->symbol) != 1)
    {
        printf(RED "\n[-] Некорректный ввод символа!\n" RESET);
        return ERR_READ_SYMBOL;
    }

    return EXIT_SUCCESS;
}
