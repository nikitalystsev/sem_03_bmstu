#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#include "matrix.h"

#define EPS 1e-9

#define TEST_PATH "./unit_tests/data/"

#define ERR_ALLOC_MATRIX 100
#define ERR_DIMENTION 101
#define ERR_INDEX 102
#define ERR_VALUE 103
#define ERR_NO_ZERO_ELEM 104
#define ERR_MILT_SIZE 105
#define ERR_COUNT_ARGS 106
#define ERR_INV_SIZE 107
#define ERR_OPEN_FILE 108
#define ERR_DET 109
#define ERR_ADD_OPER 110
#define ERR_MULT_OPER 111
#define ERR_NULL_SIZE 112
#define ERR_ISNULL_MATRIX 113
#define ERR_INDEX_READ 114
#define ERR_ALREADY_NO_ZERO_ELEM 115
#define ERR_EQUAL_MATRIX 116

#endif
