#ifndef __NORMALIZATION_H__
#define __NORMALIZATION_H__

#include "defines.h"

void normalization_mantissa(real_number_t *const real_number);
void delete_lead_null(real_number_t *const real_number);
void normalization_result(real_number_t *const result);
void normalization(real_number_t *const number1, real_number_t *const number2);

#endif
