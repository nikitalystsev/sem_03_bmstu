#ifndef __FIND_SUBSTR_H__

#define __FIND_SUBSTR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"

int find_student_by_substr(student_t *arr_students, int count_students, 
char *substr, student_t *students, int *number_substr_std);

#endif
