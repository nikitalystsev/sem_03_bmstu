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

#define ERR_OPEN_FILE 100
#define ERR_MENU_ITEM 102
#define ERR_READ_DATA 103
#define ERR_ALLOC_MEM 104

#define COUNT_DATA 10
#define MAX_DATA 1000
#define MIN_DATA 1
#define NOT_FOUND 101
#define MAX_STR_SIZE 1000
#define PATH "./data/"
#define DATA "data1"
#define GV ".gv"
#define CHANGE "change_"
#define N_REPS 5

#endif
