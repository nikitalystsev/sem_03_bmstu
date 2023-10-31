#include "../inc/check.h"

/// @brief считает количество точек в числе
/// @param real_number - указатель на строку, содержащую число
/// @return 0 - если всего одна точка в числе,
/// -100 - если точек в числе больше одной
int check_count_index_point(const char *const real_number, int len)
{
    CHECK_COUNT(POINT, real_number, len);
}

/// @brief считает количество символов 'E' в числе
/// @param real_number - указатель на строку, содержащую число
/// @return 0 - если всего один символ 'E' в числе,
/// -100 - если если символов 'E' в числе больше одной
int check_count_index_exp(const char *const real_number, int len)
{
    CHECK_COUNT(EXP, real_number, len);
}

/// @brief получает позицию символа 'E' в числе
/// @param real_number - указатель на строку, содержащую число
/// @param len - длина строки, содержищей число
/// @return позицию символа 'E', если таковая есть, иначе - -100
int get_pos_exp(const char *const real_number, int len)
{
    GET_POS(EXP, real_number, len);
}

/// @brief получает позицию точки в числе
/// @param real_number - указатель на строку, содержащую число
/// @param len - длина строки, содержищей число
/// @return позицию точки, если таковая есть, иначе - -100
int get_pos_point(const char *const real_number, int len)
{
    GET_POS(POINT, real_number, len);
}

/// @brief обощение проверки количества точек и символов 'E' в числе
/// @param real_number - указатель на строку, содержащую число
/// @return 0 - если количество точек <= 1 и количество символов 'E' <= 1
int check_exp_and_point(const char *const real_number, int len)
{
    int rc = check_count_index_point(real_number, len);
    rc += check_count_index_exp(real_number, len);

    if (rc != 0)
    {
        printf("ERROR: a real number is entered in an invalid form!\n");
        return CHECK_ERROR;
    }
    return EXIT_SUCCESS;
}

/// @brief проверка мантиссы введенного числа
/// @param real_number - указатель на строку, содержащую число
/// @param point_pos - позиция точки в числе (если она есть), иначе -100
/// @param end - позиция символа 'E' (если он есть), иначе -100
/// @return 0 - если мантисса валидная, иначе 101 (MANTISSA_ERROR)
int check_mantissa(const char *const real_number, int point_pos, int end)
{
    int count_point = 0;

    // начальный индекс для обработки числа
    // (нулевой может содержать знак)
    int begin = 1;

    if (end == NO_INDEX)
        end = strlen(real_number);

    if (real_number[0] != PLUS && real_number[0] != MINUS)
    {
        printf("ERROR: a real number is entered in an invalid form!\n");
        return MANTISSA_ERROR;
    }

    for (int i = begin; i < end; i++)
    {
        if (real_number[i] == POINT)
            count_point++;

        if ((!isdigit(real_number[i]) &&
             real_number[i] != POINT) ||
            count_point > 1)
        {
            printf("ERROR: a real number is entered in an invalid form!\n");
            return MANTISSA_ERROR;
        }
    }

    if ((point_pos == NO_INDEX &&
         (end - begin) > 30) ||
        (point_pos != NO_INDEX &&
         (end - begin) > 31))
    {
        printf("ERROR: the number of digits in the mantissa must not exceed 30!\n");
        return MANTISSA_ERROR;
    }

    return EXIT_SUCCESS;
}

/// @brief проверка порядка введенного числа
/// @param real_number - указатель на строку, содержащую число
/// @param begin - позиция символа 'E' (если он есть), иначе -100
/// @return 0 - если порядок валидный, иначе 102 (ERROR_ORDER)
int check_power(const char *const real_number, int begin)
{
    if (begin != -100)
    {
        int count_digit = 0;

        if (real_number[begin + 1] != PLUS &&
            real_number[begin + 1] != MINUS)
        {
            printf("ERROR: a real number is entered in an invalid form!\n");
            return ERROR_ORDER;
        }

        int len_number = strlen(real_number);

        for (int i = begin + 2; i < len_number; i++)
        {
            if (!isdigit(real_number[i]))
            {
                printf("ERROR: a real number is entered in an invalid form!\n");
                return ERROR_ORDER;
            }
            count_digit++;
        }

        if (count_digit > 5)
        {
            printf("ERROR: the number of digits in the order must not exceed 5!\n");
            return ERROR_ORDER;
        }
    }

    return EXIT_SUCCESS;
}

/// @brief проверка на то, является ли число нулем
/// @param number - указатель на структуру,
/// в которой определены основные элементы  введенного числа
/// @return true - если числе является нулем, иначе - false
bool isnull(const real_number_t *const number)
{

    for (int i = 0; i < number->len_mantissa; i++)
        if (number->mantissa[i] != 0)
            return false;

    return true;
}

/// @brief главная функция для проверки введенного числа
/// @param real_number - указатель на строку, содержащую число
/// @param len - длина строки, содержищей число
/// @return 0 - если введенное число является валидным,
/// иначе - ненулевой код возврата
int check_real_number(const char *const real_number, int len)
{
    int rc = 0;

    if (((real_number[0] == PLUS || real_number[0] == MINUS) &&
         strlen(real_number) <= 1) ||
        ((real_number[0] != PLUS && real_number[0] != MINUS) &&
         strlen(real_number) < 1))
    {
        printf("ERROR: a real number is entered in an invalid form!\n");
        return LEN_ERROR;
    }

    if ((rc = check_exp_and_point(real_number, len)) != 0)
        return rc;

    int ind_point = get_pos_point(real_number, len);
    int ind_exp = get_pos_exp(real_number, len);

    if (ind_point != NO_INDEX && ind_exp != NO_INDEX &&
        ind_point >= ind_exp)
    {
        printf("ERROR: a real number is entered in an invalid form!\n");
        return CHECK_ERROR;
    }

    if ((rc = check_mantissa(real_number, ind_point, ind_exp)) != 0)
        return rc;

    if ((rc = check_power(real_number, ind_exp)) != 0)
        return rc;

    return rc;
}
