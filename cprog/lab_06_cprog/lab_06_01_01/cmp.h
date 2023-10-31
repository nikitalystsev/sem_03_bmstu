#ifndef __CMP_H__
#define __CMP_H__

#include "defines.h"
#include "film.h"

void swap(void *value1, void *value2, const int size);
int compare_int(int value1, int value2);
int compare_str(const void *value1, const void *value2);

#endif
