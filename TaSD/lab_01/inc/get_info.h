#ifndef __GET_INFO_H__
#define __GET_INFO_H__

#include "defines.h"
#include "check.h"

void get_sign(char *const number,
              real_number_t *const real_number);

void get_point_and_exp_pos(const char *const number,
                           int len,
                           real_number_t *const real_number);

void get_mantissa(char *const number,
                  int len,
                  real_number_t *const real_number);

void get_order(char *const number,
               int len,
               real_number_t *const real_number);

void get_info_about_number(char *const number,
                           int len,
                           real_number_t *const real_number);

#endif
