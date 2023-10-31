#ifndef __FILTER_H__
#define __FILTER_H__

#include "defines.h"
#include "mysort.h"

void get_index_max_and_min(const int *pb_src,
const int *pe_src,
int *const ind_max,
int *const ind_min);

int key(const int *pb_src, 
const int *pe_src, 
int **pb_dst, 
int **pe_dst);

#endif
