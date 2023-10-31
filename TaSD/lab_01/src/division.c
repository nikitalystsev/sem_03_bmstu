#include "../inc/division.h"
#include "../inc/normalization.h"
#include "../inc/print.h"

/// @brief проерка на то, является ли первое число больше части второго числа
/// @param float1 - указатель на структуру,
/// в которой определены основные элементы первого введенного числа
/// @param float2 - указатель на структуру,
/// в которой определены основные элементы второго введенного числа
/// @return  true - если первого число больше части второго
/// false - инача
bool float1_bigger_float2(real_number_t *const float1,
                          real_number_t *const float2)
{
    for (int i = 0; i < float1->len_mantissa; i++)
        if (float1->mantissa[i] > float2->mantissa[i])
            return true;
        else if (float1->mantissa[i] < float2->mantissa[i])
            return false;

    return true;
}

/// @brief сдвиг мантиссы влево на один порядок
/// @param number - указатель на структуру,
/// в которой определены основные элементы  введенного числа
void shift_mantissa_to_left(real_number_t *const number)
{
    for (int i = 0; i < number->len_mantissa - 1; i++)
        number->mantissa[i] = number->mantissa[i + 1];

    for (int i = number->len_mantissa - 1; i < MAX_LEN_MANTISSA; i++)
        number->mantissa[i] = 0;
}

/// @brief вычитание при условие что первое число больше второго
/// @param float1 - указатель на структуру,
/// в которой определены основные элементы первого введенного числа
/// @param float2 - указатель на структуру,
/// в которой определены основные элементы втрого введенного числа 
/// @return 0 - если первое число больше втрого, иначе - 106
int substraction(real_number_t *const float1,
                 real_number_t *const float2)
{
    if (!float1_bigger_float2(float1, float2))
        return FLOAT2_BIGGER_FLOAT1;

    int len_float2 = float2->len_mantissa;

    for (int i = len_float2 - 1; i >= 0; i--)
        if (float1->mantissa[i] - float2->mantissa[i] >= 0)
            float1->mantissa[i] -= float2->mantissa[i];
        else
        {
            int j = i - 1;

            while (float1->mantissa[j] == 0)
                j--;

            float1->mantissa[j]--;

            j++;

            for (; j < i; j++)
                float1->mantissa[j] = 9;

            float1->mantissa[i] += 10 - float2->mantissa[i];
        }

    return EXIT_SUCCESS;
}

/// @brief функция округления
/// @param float1 - указатель на структуру,
/// в которой определены основные элементы первого введенного числа
/// @param float2 - указатель на структуру,
/// в которой определены основные элементы втрого введенного числа
/// @param result - указатель на структуру,
/// в которой будет содержаться результат деления
/// @param div_step - шаг деления
/// @return целое число - пересчет порядка
int rouding(real_number_t *const float1,
            real_number_t *const float2,
            real_number_t *const result,
            int div_step)
{
    int digit = 0;

    while (substraction(float1, float2) == 0)
        digit++;

    shift_mantissa_to_left(float1);

    // если в доп разряде числа цифра больше 5, то округляем,
    // тобишь прибавляем к позади идущей цифре разряд
    if (div_step == MAX_LEN_MANTISSA - 1 && digit >= 5)
        result->mantissa[MAX_LEN_MANTISSA - 2] += 1;

    for (; div_step < MAX_LEN_MANTISSA - 1; div_step++)
    {
        result->mantissa[div_step] = 0;
        result->len_mantissa++;
    }

    // поразрядый перенос из младшего разряда в старший с коррекцией порядка
    int order_recalculation = 0;
    for (int i = MAX_LEN_MANTISSA - 2; i >= 0; i--)
    {
        result->mantissa[i] += order_recalculation;

        if (result->mantissa[i] >= 10)
        {
            result->mantissa[i] = 0;
            order_recalculation = 1;
        }
        else
            break;
    }

    if (result->mantissa[0] == 1)
    {
        for (int i = MAX_LEN_MANTISSA - 2; i > 0; i++)
            result->mantissa[i] = result->mantissa[i - 1];

        result->mantissa[0] = 0;
    }
    else
        order_recalculation = 0;

    return order_recalculation;
}

/// @brief Деление
/// @param float1 - делимое
/// @param float2 - делитеть
/// @param result - результат
/// @return 0 - если деление прошло успешно,
/// иначе - ненулевой код возврата
int division(real_number_t *const float1,
             real_number_t *const float2,
             real_number_t *const result)
{
    if (isnull(float2))
    {
        printf("ERROR: division by zero!\n");
        return ERR_DIV_BY_ZERO;
    }

    if (isnull(float1))
    {
        result->sing_num = PLUS;
        result->mantissa[0] = 0;
        result->mantissa[1] = 0;
        result->power = 0;
        result->len_mantissa = 2;

        return EXIT_SUCCESS;
    }

    if (!float1_bigger_float2(float1, float2))
    {
        shift_mantissa_to_left(float1);
        float1->power--;
    }

    result->mantissa[0] = 0;
    int digit = 0;

    while (substraction(float1, float2) == 0)
        digit++;

    shift_mantissa_to_left(float1);

    result->mantissa[1] = digit;

    int i = 2;

    for (; i < MAX_LEN_MANTISSA - 1; i++)
    {
        if (isnull(float1))
        {
            result->len_mantissa = i + 1;
            digit = 0;
            break;
        }
        if (!float1_bigger_float2(float1, float2))
        {
            shift_mantissa_to_left(float1);
            result->mantissa[i] = 0;
        }
        else
        {
            digit = 0;

            while (substraction(float1, float2) == 0)
                digit++;

            shift_mantissa_to_left(float1);

            result->mantissa[i] = digit;
        }
    }

    int order_recalculation = rouding(float1, float2, result, i);

    // printf("%d\n", order_recalculation);
    
    result->sing_num = PLUS;
    if (float1->sing_num != float2->sing_num)
        result->sing_num = MINUS;

    result->power = float1->power - float2->power + order_recalculation + 1;
    
    if (result->power > MAX_ORDER || result->power < -MAX_ORDER)
    {
        printf("ERROR: power was overflow!\n");
        return ERR_OVERLFOW;
    }

    result->len_mantissa = MAX_LEN_MANTISSA - 1;

    return EXIT_SUCCESS;
}
