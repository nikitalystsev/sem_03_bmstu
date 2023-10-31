#ifndef __SORT_H__
#define __SORT_H__

#include "defines.h"

void swap(void *value1, void *value2, size_t size);

int compare_table(const void *value1, const void *value2);

int compare_keys(const void *value1, const void *value2);

void bubble_sort(
    void *array,
    size_t count_elem,
    size_t size,
    cmp_t comparator);

#endif
