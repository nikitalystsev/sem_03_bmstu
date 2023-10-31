#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int (*cmp_str_t)(const void *, const void *);
typedef int (*cmp_int_t)(int, int);

#define MAX_COUNT_FILMS 16
#define NAME_SIZE 26
#define SIZE_INT 4

#define PARAM_LIST 3
#define PARAM_FIND 4

#define ERR_CHECK_STR 100
#define ERR_READ_NUM 101
#define ERR_NO_VALID_YEAR 102
#define ERR_COUNT_FILMS 103
#define ERR_CLOSE_FILE 104
#define ERR_OPEN_FILE 105
#define ERR_EMPTY_FILE 106
#define ERR_NO_VALID_FIELD 107
#define ERR_WRONG_NUMBERS_OF_PARAM 108

#define NO_FIND_FILM 109

#endif
