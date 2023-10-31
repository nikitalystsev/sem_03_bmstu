#include "cmp.h"

void swap(void *value1, void *value2, const int size)
{
    char buffer[SIZE];

    memcpy(buffer, value1, size);
    memcpy(value1, value2, size);
    memcpy(value2, buffer, size);
}

int compare_int(int value1, int value2)
{
    return (value1 - value2); 
}

int compare_str(const void *value1, const void *value2)
{
    return strcmp((char *)value1, (char *)value2); 
}
