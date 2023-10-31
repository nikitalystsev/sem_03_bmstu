#ifndef __DIVISION_H__
#define __DIVISION_H__

#include "defines.h"
#include "check.h"

bool float1_bigger_float2(real_number_t *const float1,
                          real_number_t *const float2);

void shift_mantissa_to_left(real_number_t *const number);

int substraction(real_number_t *const float1,
                 real_number_t *const float2);

int rouding(real_number_t *const float1,
            real_number_t *const float2,
            real_number_t *const result,
            int div_step);
            
int division(real_number_t *const number1,
             real_number_t *const number2,
             real_number_t *const result);

#endif
