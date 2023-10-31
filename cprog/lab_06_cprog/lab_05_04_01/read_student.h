#ifndef __READ_STUDENT_H__

#define __READ_STUDENT_H__

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

int read_student(FILE *const f, student_t *student);
int init_arr_student_arr_from_file(FILE *f, student_t *arr_students, 
int *const count_students, char const *argv[]);

#endif
