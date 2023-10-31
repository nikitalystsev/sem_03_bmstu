#ifndef __WRITE_STUDENT_H__

#define __WRITE_STUDENT_H__

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

void write_one_student_to_file(FILE *const f, student_t *student);
int write_students_to_file(FILE *f, student_t *arr_students, int count_students, char const *argv);

#endif 
