#ifndef __CREATE_ARRAY_H__
#define __CREATE_ARRAY_H__

#include "defines.h"

int get_count_elements_from_file(FILE *file, 
const char *const file_name,
int *const count_elements);

int get_count_elements(int *pb_src,
int *pe_src);

int read_array(FILE *file,
const char *const file_name,
int *const ptr_start,
int *const ptr_end);

int create_array(FILE *file,
const char *const file_name,
int **pb_src,
int **pe_src);

#endif
