#include "print.h"

void print_student(student_t student)
{
    printf("%s\n", student.last_name);
    printf("%s\n", student.name);
    for (int i = 0; i < 4; i++)
        printf("%d ", student.marks[i]);
    printf("\n");
}

void print_arr_students(student_t *const arr_students, int count_students)
{
    for (int i = 0; i < count_students; i++)
        print_student(arr_students[i]);
}
