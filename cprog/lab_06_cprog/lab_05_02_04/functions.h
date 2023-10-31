#ifndef __FUNCTOINS_H__

#define __FUNCTOINS_H__

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

int find_average_between_max_min(FILE *const f, double *const average, const int begin_ind, const int end_ind);
int find_max_min_in_file(FILE *const f, int *const ind_max, int *const ind_min);
void definition_begin_end_indexes(int *const ind_1, int *const ind_2);

#endif 
