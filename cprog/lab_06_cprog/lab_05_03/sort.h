#ifndef __SORT_H__

#define __SORT_H__

#include <stdio.h>
#include "get_put_numbers.h"
#include "defines.h"

void swap(FILE *f, int number1, int number2, int pos_1, int pos_2);
int sort_numbers_in_file(FILE *f);
int sort(char const *argv);

#endif 
