#include "sort.h"

void swap(void *value1, void *value2, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        char temp = *((char *)value1 + i);
        *((char *)value1 + i) = *((char *)value2 + i);
        *((char *)value2 + i) = temp;
    }
}

int compare_table(const void *value1, const void *value2)
{
    return (((student_t *)value1)->mark - ((student_t *)value2)->mark);
}

int compare_keys(const void *value1, const void *value2)
{
    return (((key_t *)value1)->mark - ((key_t *)value2)->mark);
}

void bubble_sort(
    void *array,
    size_t count_elem,
    size_t size,
    cmp_t comparator)
{
    for (size_t i = 0; i < count_elem - 1; i++)
        for (size_t j = 0; j < count_elem - 1 - i; j++)
            if (comparator((char *)array + j * size, (char *)array + j * size + size) > 0)
                swap((char *)array + j * size, (char *)array + j * size + size, size);
}
