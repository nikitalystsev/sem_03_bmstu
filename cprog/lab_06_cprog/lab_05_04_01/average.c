#include "average.h"

void calc_sum_marks(const int *const marks, double *const sum)
{
    for (int i = 0; i < COUNT_MARKS; i++)
        (*sum) += marks[i];
}

int calc_average(student_t *const arr_students, const int count_students, 
double *const average)
{
    int count = 0;
    double sum = 0.0;
    for (int i = 0; i < count_students; i++)
    {
        calc_sum_marks(arr_students[i].marks, &sum);
        count += COUNT_MARKS;
    }
    if (count == 0)
        return ERR_NO_MARKS;

    *average = sum / count;

    return EXIT_SUCCESS;
}

void delete_student(student_t *const arr_students, 
int *const count_students, const double average)
{
    for (int i = 0; i < *count_students; i++)
    {
        double sum = 0;
        calc_sum_marks(arr_students[i].marks, &sum);
        double average_student = sum / COUNT_MARKS;
        if (average_student < average)
        {
            for (int j = i; j < *count_students - 1; j++)
                arr_students[j] = arr_students[j + 1];
            (*count_students)--;
            i--;
        }
    }
}
