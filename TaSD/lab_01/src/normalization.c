#include "../inc/normalization.h"
#include "../inc/print.h"

/// @brief нормализация мантиссы (доплнение нулями до максимальной длины)
/// @param real_number - указатель на структуру,
/// в которой определены основные элементы  введенного числа
void normalization_mantissa(real_number_t *const real_number)
{

    int len_mantissa = real_number->len_mantissa;

    if (real_number->point_pos == NO_INDEX)
    {
        for (; len_mantissa < MAX_LEN_MANTISSA; len_mantissa++)
        {
            real_number->mantissa[len_mantissa] = 0;
            real_number->power--;
            real_number->len_mantissa++;
        }
    }
    else
    {
        for(int i = real_number->point_pos; i < real_number->len_mantissa - 1; i++)
        {
            real_number->mantissa[i] = real_number->mantissa[i + 1];
            real_number->power--;
        }
        real_number->len_mantissa--;

        for (int i = len_mantissa - 1; i < MAX_LEN_MANTISSA; i++)
        {
            real_number->mantissa[i] = 0;
            real_number->power--;
        }

        real_number->len_mantissa = MAX_LEN_MANTISSA;
    }
}

/// @brief удаление нулей с начала числа
/// @param real_number - указатель на структуру,
/// в которой определены основные элементы  введенного числа
void delete_lead_null(real_number_t *const real_number)
{
    int len_mantissa = real_number->len_mantissa;
    int count = 0;

    while (real_number->mantissa[0] == 0 && count != len_mantissa - 1)
    {
        for (int i = 0; i < len_mantissa - 1; i++)
            SWAP(int, real_number->mantissa[i], real_number->mantissa[i + 1]);
        count++;
        real_number->power--;
    }
    
    for (int pos_num = MAX_LEN_MANTISSA - 1; pos_num > 0; pos_num--)
        real_number->mantissa[pos_num] = real_number->mantissa[pos_num - 1];

    real_number->power++;
    real_number->mantissa[0] = 0;
}

/// @brief нормализация мантиссы результата
/// @param real_number - указатель на структуру,
/// в которой определены основные элементы  введенного числа
void normalization_result(real_number_t *const result)
{
    int count = 0;

    while (result->mantissa[0] == 0 && count != MAX_LEN_MANTISSA - 2)
    {
        for (int i = 0; i < MAX_LEN_MANTISSA - 2; i++)
            result->mantissa[i] = result->mantissa[i + 1];
        result->power--;
        count++;
    }

    for (int pos_num = MAX_LEN_MANTISSA - 1; pos_num > 0; pos_num--)
        result->mantissa[pos_num] = result->mantissa[pos_num - 1];

    result->power++;

    result->mantissa[0] = 0;
}

/// @brief главная функция нормализации
/// @param number1 - указатель на структуру,
/// в которой определены основные элементы  первого введенного числа
/// @param number2 - указатель на структуру,
/// в которой определены основные элементы  второго введенного числа
void normalization(real_number_t *const number1, real_number_t *const number2)
{
    // print_number(number1);
    // print_number(number2);
    // printf("\n");
    normalization_mantissa(number1);
    normalization_mantissa(number2);

    // print_number(number1);
    // print_number(number2);
    // printf("\n");
    delete_lead_null(number1);
    delete_lead_null(number2);

    // print_number(number1);
    // print_number(number2);
}
