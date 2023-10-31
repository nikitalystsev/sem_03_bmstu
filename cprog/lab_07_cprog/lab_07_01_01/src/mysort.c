#include "mysort.h"

void swap(void *value1, void *value2, const int size)
{  
    for (int i = 0; i < size; i++)
    {
        char temp = *((char *)value1 + i);
        *((char *)value1 + i) = *((char *)value2 + i);
        *((char *)value2 + i) = temp;
    }
}

int compare(const void *value1, const void *value2)
{
    return (*(int *)value1 - *(int *)value2); 
}

void mysort(void *array,
size_t count_elem,
size_t size,
cmp_t comparator)
{
    for (size_t i = 0; i < count_elem; i++)
        for (size_t j = 0; j < count_elem - 1; j++)
            if (comparator((char *)array + j * size, (char *)array + j * size + size) > 0)
                swap((char *)array + j * size, (char *)array + j * size + size, size);
}
