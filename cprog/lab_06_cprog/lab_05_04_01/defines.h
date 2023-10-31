#ifndef __DEFINES_H__

#define __DEFINES_H__

#define ERR_OPEN_FILE (-1)
#define ERR_NO_RECORD_DATA (-2)
#define ERR_EMPTY_FILE (-3)
#define ERR_NO_MARKS (-4)
#define ERR_NO_VALID_PARAMETERS 53
#define END_OF_FILE 1
#define COUNT_MARKS 4

#define NMAX 100

typedef struct student
{
    char last_name[26];
    char name[11];
    int marks[4];
} student_t;

#endif 
