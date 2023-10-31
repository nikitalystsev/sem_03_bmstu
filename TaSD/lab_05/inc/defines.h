#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

#define RESET "\033[0m"
#define BLACK "\033[0;m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define VIOLET "\033[0;35m"
#define TURQ "\033[0;36m" // бирюзовый
#define WHITE "\033[0;37m"

#define EPS 1e-9
#define COUNT_PROCESS 5
#define MIN_TIME_ADD 0
#define MAX_TIME_ADD 6
#define MIN_TIME_PROCESSING 0
#define MAX_TIME_PROCESSING 1
#define COUNT_APPLICATION 1000
#define COUNT_PRINT_APPLICATION 100
#define MAX_FREE_ADDR_SIZE 100000
#define MAX_SIZE_QUEUE 100000
#define EMPTY_QUEUE 1
#define MAX_INPUT_SIZE 10000

#define ERR_ALLOC_MEM 100
#define ERR_READ_WORK 101
#define ERR_WORK 103
#define ERR_READ_ITEM 104
#define ERR_ITEM 105
#define ERR_READ_TIME 106
#define ERR_TIME 107
#define ERR_READ_SIZE 108
#define ERR_SIZE 109
#define ERR_QUEUE_ELEM 110
#define ERR_QUEUE_OVERFLOW 111

typedef struct elem_t elem_t;

/// @brief заявка
struct elem_t
{
    double add_time;     // время добавления
    double process_time; // время обработки
    int count_iter;      // количество проходов
};

#endif
