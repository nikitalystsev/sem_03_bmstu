#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>

typedef int (*cmp_t)(const void *, const void *);

#define TEST_PATH "./unit_tests/data/"
#define PARAM_FILTER 4
#define PARAM_NO_FILTER 3

#define ERR_NO_DATA 100
#define ERR_ALLOC_MEM 101
#define ERR_READ_ARRAY 102
#define ERR_OPEN_FILE -103
#define ERR_NO_VALID_PARAM 105
#define ERR_WRITE_TO_FILE 106

#define ERR_EQUAL_SIZE_ARRAY 200
#define ERR_EQUAL_ELEM_ARRAY 201

#endif
