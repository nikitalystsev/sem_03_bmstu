#ifndef __DEFINES_H__
#define __DEFINES_H__

/*
улица в одно слово
не дата поступления, а год
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

typedef int (*cmp_t)(const void *, const void *);

#define SURNAME_SIZE 30 + 1
#define NAME_SIZE 30 + 1
#define STREET_SIZE 30 + 1
#define DATE_SIZE 11
#define MAX_STUDENT 10100
#define MIN_YEAR 2015
#define MAX_YEAR 2022
#define MIN_MARK 60
#define MAX_MARK 100

#define DATA_FILE "src/data/data10000.txt"

#define ERR_OPEN_FILE 100
#define ERR_MENU_ITEM 101
#define ERR_SIZE_DATA_FILE 102
#define ERR_GET_DATA_FROM_FILE 103
#define ERR_YEAR_OF_ADM 104
#define ERR_ADD_STUDENT 105

#define ERR_INPUT_HOUSE 106
#define ERR_INPUT_SURNAME 107
#define ERR_INPUT_NAME 108
#define ERR_INPUT_STUDY_GROUP 109
#define ERR_INPUT_GENDER 110
#define ERR_INPUT_AGE 111
#define ERR_INPUT_MARK 112
#define ERR_INPUT_STREET 113
#define ERR_INPUT_NUM_HOME 114
#define ERR_INPUT_NUM_FLAT 115
#define ERR_INPUT_NUM_DORM 116
#define ERR_INPUT_ROOM 117

#define EXIT_FROM_THE_PROGRAM 1

typedef struct 
{
    int mark;
    int index_mark;
} key_t;

typedef struct
{
    char street[STREET_SIZE];
    int num_home;
    int num_flat;
} home_t;

typedef struct
{
    int num_dorm;
    int num_room;
} dorm_t;

typedef union
{
    home_t home;
    dorm_t dorm;
} house_t;

typedef struct student_t
{
    int flag;
    char surname[SURNAME_SIZE];
    char name[NAME_SIZE];
    int study_group;
    int gender;
    int age;
    int mark;
    int year_adm;
    house_t house;
} student_t;

#endif
