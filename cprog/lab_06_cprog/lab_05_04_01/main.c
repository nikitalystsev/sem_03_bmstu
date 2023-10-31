#include "defines.h"
#include "print.h"
#include "read_student.h"
#include "find_substr.h"
#include "write_student.h"
#include "sort.h"
#include "average.h"
#include "check_argc.h"

#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *f = NULL; 
    student_t arr_students[NMAX];
    int count_students = 0;
    char substr[26];
    double average;

    int rc;

    int mark = check_argc(argc, argv);
    switch (mark)
    {
        case 1:
            rc = init_arr_student_arr_from_file(f, arr_students, &count_students, argv);
            sort_students(arr_students, count_students);
            print_arr_students(arr_students, count_students);
            break;
        case 2:
            rc = init_arr_student_arr_from_file(f, arr_students, &count_students, argv);
            memcpy(substr, argv[4], strlen(argv[4]) + 1);
            student_t students[NMAX];
            int number_substr_std = 0;
            rc += find_student_by_substr(arr_students, count_students, substr, students, &number_substr_std);
            rc += write_students_to_file(f, students, number_substr_std, argv[3]);
            break;
        case 3:
            rc = init_arr_student_arr_from_file(f, arr_students, &count_students, argv);
            rc += calc_average(arr_students, count_students, &average);
            delete_student(arr_students, &count_students, average);
            rc += write_students_to_file(f, arr_students, count_students, argv[2]);
            break;
        default:
            return ERR_NO_VALID_PARAMETERS;
    }

    if (rc != 0)
        return rc;

    return EXIT_SUCCESS;
}
