#ifndef __PRINT_H__
#define __PRINT_H__

#include "defines.h"

void print_menu(void);

void print_student(student_t *const student);

void print_arr_students(
    student_t *const arr_students,
    size_t count_students);


void print_arr_students_by_keys(
    key_t *const arr_keys,
    student_t *const arr_students,
    const size_t count_students);

void print_key(
    const key_t *const student);

void print_keys(
    key_t *const arr_keys,
    const size_t count_students);

void print_result_timing_students(long double time, bool check_qsort);

void print_result_timing_keys(long double  time, bool check_qsort);

#endif
