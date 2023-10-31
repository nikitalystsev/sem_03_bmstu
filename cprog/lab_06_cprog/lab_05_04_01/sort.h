#ifndef __SORT_H__

#define __SORT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defines.h"

int last_name_cmp(const void *a, const void *b);
void swap(student_t *const student1, student_t *const student2);
void sort_students(student_t *arr_students, int count_students);

#endif 
