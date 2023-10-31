#ifndef __PRINT_H__
#define __PRINT_H__

#include "defines.h"
#include "stack_array.h"
#include "stack_list.h"
#include "balanced_parentheses.h"
#include "timing.h"

void print_menu(void);

void print_timing(const char *const exp,
                  stack_array_t *stack_array,
                  stack_list_t **stack_list);

void print_func_time(void);
 
void print_result(const char *const exp,
                  stack_array_t *stack_array,
                  stack_list_t **stack_list);

#endif
