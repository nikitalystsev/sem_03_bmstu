#include "../inc/get_info.h"

/// @brief определение знака введенного числа,
/// заполнение переменной структурного типа
/// @param number - указатель на строку, содержащую число
/// @param real_number - указатель на структуру,
/// в которой определены основные элементы  введенного числа
void get_sign(char *const number,
              real_number_t *const real_number)
{
    if (number[0] == PLUS || number[0] == MINUS)
        real_number->sing_num = number[0];
}

/// @brief получение идексов точки и символа 'E' в числе,
/// заполение полей структуры
/// @param number - указатель на строку, содержащую число
/// @param len - длина строки, содержащей число
/// @param real_number -  указатель на структуру,
/// в которой определены основные элементы  введенного числа
void get_point_and_exp_pos(const char *const number,
                           int len,
                           real_number_t *const real_number)
{
    int index_point = get_pos_point(number, len);
    int index_exp = get_pos_exp(number, len);

    if ((number[0] == PLUS || number[0] == MINUS) && index_point != NO_INDEX)
        index_point--;

    real_number->point_pos = index_point;
    real_number->e_pos = index_exp;
}

/// @brief получение порядка числа,
/// заполнение соответствующего поля структуры
/// @param number - указатель на строку, содержащую число
/// @param len - длина строки, содержащей число
/// @param real_number -  указатель на структуру,
/// в которой определены основные элементы  введенного числа
void get_order(char *const number,
               int len,
               real_number_t *const real_number)
{
    if (real_number->e_pos == -100)
        real_number->power = 0;
    else
    {
        int begin = real_number->e_pos + 1,
            end = len;

        char power[MAX_LEN_POWER];
        int i = 0;
        for (; i < MAX_LEN_POWER && begin < end; i++, begin++)
            power[i] = number[begin];
        power[i] = '\0';
        real_number->power = atoi(power);
    }
}

/// @brief получение мантиссы числа,
/// заполнение соответствующего поля структуры
/// @param number - указатель на строку, содержащую число
/// @param len - длина строки, содержащей число
/// @param real_number -  указатель на структуру,
/// в которой определены основные элементы  введенного числа
void get_mantissa(char *const number,
                  int len,
                  real_number_t *const real_number)
{
    int begin = 1, end;

    if (real_number->e_pos == NO_INDEX)
        end = len;
    else
        end = real_number->e_pos;

    int i = 0;
    for (; i < MAX_LEN_MANTISSA - 1 && begin < end; i++, begin++)
        if (number[begin] == POINT)
            real_number->mantissa[i] = 0;
        else
            real_number->mantissa[i] = number[begin] - '0';

    real_number->len_mantissa = i;
}

/// @brief Функция для сбора всей информации о введенном числе
/// @param number - указатель на строку, содержащую число
/// @param len - длина строки, содержащей число
/// @param real_number - указатель на структуру,
/// в которой определены основные элементы  введенного числа
void get_info_about_number(char *const number,
                           int len,
                           real_number_t *const real_number)
{
    get_sign(number, real_number);
    get_point_and_exp_pos(number, len, real_number);
    get_mantissa(number, len, real_number);
    get_order(number, len, real_number);
}
