#include "read_student.h"

int read_student(FILE *const f, student_t *student)
{
    fscanf(f, "%s", student->last_name);
    fscanf(f, "%s", student->name);
    fscanf(f, "%d %d %d %d", &student->marks[0], &student->marks[1], &student->marks[2], &student->marks[3]);

    if (feof(f))
        return END_OF_FILE;

    return EXIT_SUCCESS;
}

int init_arr_student_arr_from_file(FILE *f, student_t *arr_students, 
int *const count_students, char const *argv[])
{
    f = fopen(argv[2], "r");
    if (f != NULL)
    {
        for (int i = 0; read_student(f, &arr_students[i]) == 0; i++)
            (*count_students)++;
        fclose(f);
    }
    else
        return ERR_OPEN_FILE;

    if (*count_students == 0)
        return ERR_EMPTY_FILE;

    return EXIT_SUCCESS;
}
