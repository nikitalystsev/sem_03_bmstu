#ifndef __GET_PUT_NUMBERS_H__

#define __GET_PUT_NUMBERS_H__

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

int put_number_by_pos(FILE *f, int pos, const int *const number);
int get_number_by_pos(FILE *f, int pos, int *const number);
int get_pos_last_number(FILE *f, int *const pos_last_number);

#endif 
