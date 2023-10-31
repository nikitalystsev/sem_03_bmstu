#ifndef __DEFINES_H__

#define __DEFINES_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <regex.h>

#define PLUS '+'
#define MINUS '-'
#define POINT '.'
#define EXP 'E'

#define MAX_LEN_MANTISSA 32
#define MAX_LEN_POWER 7
#define MAX_ORDER 99999
#define MAX_LEN_NUMBER 39

#define NO_INDEX -100

#define CHECK_ERROR 100
#define MANTISSA_ERROR 101
#define ERROR_ORDER 102
#define LEN_ERROR 103
#define ERR_DIV_BY_ZERO 104
#define ERR_BIG_ORDER 105
#define ERR_OVERLFOW 106

#define FLOAT2_BIGGER_FLOAT1 106

#define INT 10
#define FLOAT 11

// макрос, меняющий зачения двух элементов переданного типа
#define SWAP(type, a, b) \
    do                   \
    {                    \
        type temp = a;   \
        a = b;           \
        b = temp;        \
    } while (0);

typedef struct
{
    int mantissa[MAX_LEN_MANTISSA];  
    int len_mantissa;          
    char sing_num;            
    int power;                 
    int point_pos;              
    int e_pos;                 
} real_number_t;

#endif
