#ifndef __CHECK_H__
#define __CHECK_H__

#include "defines.h"

// считает количество переданного символа в строке 
#define CHECK_COUNT(value, number, len_number) \
    do                                         \
    {                                          \
        int count = 0;                         \
        for (int i = 0; i < len_number; i++)   \
            if (number[i] == value)            \
                count++;                       \
        if (count > 1)                         \
            return -100;                       \
        return 0;                              \
    } while (0)

// получает индекс первого вхождения переданного символа в строку 
#define GET_POS(value, number, len_number)   \
    do                                       \
    {                                        \
        int index_value = -100;              \
        for (int i = 0; i < len_number; i++) \
            if (number[i] == value)          \
            {                                \
                index_value = i;             \
                return index_value;          \
            }                                \
        return index_value;                  \
    } while (0)

int check_count_index_point(const char *const real_number, int len);
int check_count_index_exp(const char *const real_number, int len);
int check_exp_and_point(const char *const real_number, int len);
int get_pos_exp(const char *const real_number, int len);
int get_pos_point(const char *const real_number, int len);
int check_mantissa(const char *const real_number, int point_pos, int end);
int check_power(const char *const real_number, int begin);
bool isnull(const real_number_t *const number);
int check_real_number(const char *const real_number, int len);

#endif
