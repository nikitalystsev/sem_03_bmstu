#include "sort.h"

int last_name_cmp(const void *a, const void *b)
{
    return strcmp(((student_t*)a)->last_name, ((student_t*)b)->last_name);
}

void swap(student_t *const student1, student_t *const student2)
{
    student_t buf = *student1;
    *student1 = *student2;
    *student2 = buf;
}

void sort_students(student_t *arr_students, int count_students)
{
    qsort(arr_students, count_students, sizeof(student_t), last_name_cmp);
    for (int i = 0; i < count_students - 1; i++)
        for (int j = 0; j < count_students - 1 - i; j++)
            if (strcmp(arr_students[j].last_name, arr_students[j + 1].last_name) == 0)
                if (strcmp(arr_students[j].name, arr_students[j + 1].name) > 0)
                    swap(&arr_students[j], &arr_students[j + 1]);
}
