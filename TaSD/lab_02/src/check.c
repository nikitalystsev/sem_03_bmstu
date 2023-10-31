#include "check.h"

bool check_dorm_student_by_year(
    const student_t *const student,
    const int year)
{
    if (student->flag == 1 || student->year_adm != year)
    {
        return false;
    }

    return true;
}

bool check_student_by_mark(
    const student_t *const student,
    const int mark)
{
    if (student->mark != mark)
    {
        return false;
    }

    return true;
}
