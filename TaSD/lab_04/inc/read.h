#ifndef __READ_H__
#define __READ_H__

#include "defines.h"

int input_expression_with_bracked(char *const exp);

int get_expression_with_bracked_from_file(char *const exp,
                                          const char *const file_name);

int input_size_stack_array(int *const count);

int input_data(data_t *const data);

#endif
