#ifndef __CHECK_H__
#define __CHECK_H__

#include "defines.h"

bool check_dorm_student_by_year(
    const student_t *const student,
    const int year);

bool check_student_by_mark(
    const student_t *const student,
    const int mark);
    
#endif
