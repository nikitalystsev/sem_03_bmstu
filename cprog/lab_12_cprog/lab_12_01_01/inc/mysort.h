#ifndef _MYSORT_H__
#define _MYSORT_H__

#include "defines.h"

void swap(void *value1, void *value2, const int size);

int compare(const void *val1, const void *val2);

void mysort(void *first,
size_t number,
size_t size,
cmp_t comparator);

#endif
