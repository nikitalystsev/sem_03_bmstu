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
#define ERR_CLOSE_FILE -104
#define ERR_NO_VALID_PARAM 105
#define ERR_WRITE_TO_FILE 106

#define ERR_EQUAL_SIZE_ARRAY 200
#define ERR_EQUAL_ELEM_ARRAY 201

#define FREE(pb_src, pb_dst) \
    do                       \
    {                        \
        free(pb_src);        \
        free(pb_dst);        \
        pb_src = NULL;       \
        pb_dst = NULL;       \
    } while (0);

#define CHECK_RC(rc)              \
    do                            \
    {                             \
        if (rc == ERR_ALLOC_MEM)  \
            return rc;            \
        if (rc != 0)              \
        {                         \
            FREE(pb_src, pb_dst); \
            return rc;            \
        }                         \
    } while (0)

#endif
