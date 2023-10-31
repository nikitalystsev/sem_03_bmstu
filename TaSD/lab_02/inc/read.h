#ifndef __READ_H__
#define __READ_H__

#include "defines.h"

int get_basic_info(
    student_t *const student);

int get_variable_info(
    student_t *const student);

int get_mark(int *mark);

int get_year_of_adm(int *const year);

int get_file_size(FILE *data_file, size_t *const file_size);

int get_data_from_file(
    key_t *const arr_keys,
    student_t *const arr_students,
    size_t *const count_student);

#endif
