#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include "defines.h"
#include "print.h"
#include "check.h"
#include "read.h"
#include "sort.h"
#include "timing.h"

void delete_one_student(
    student_t *const arr_students,
    size_t *const count_students,
    size_t index_student);

void delete_one_key(
    key_t *const arr_keys,
    size_t *const count_students,
    size_t index_key);

void relac(
    key_t *const arr_keys,
    size_t *const count_students,
    size_t index_key);

void delete_students_by_mark(
    student_t *const arr_students,
    size_t *const count_students,
    const int mark);

int add_student(
    key_t *const arr_key,
    student_t *const arr_students,
    size_t *const count_students);

void print_dorm_student_by_year(
    student_t *const arr_students,
    size_t count_students,
    const int year);

void print_dorm_student_by_year(
    student_t *const arr_students,
    size_t count_students,
    int year);

void get_arr_keys(
    key_t *const arr_keys,
    student_t *const arr_students,
    size_t count_students);

void copy_data(
    key_t *const keys,
    key_t *const arr_keys,
    student_t *const students,
    student_t *const arr_students,
    const size_t count_students);
    
void sort_comparison(
    key_t *const arr_keys,
    student_t *const arr_students,
    const size_t count_students);

int execute_menu_item(
    key_t *const arr_keys,
    student_t *const arr_students,
    size_t *const count_students,
    int8_t menu_item);

#endif
