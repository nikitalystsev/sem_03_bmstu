#ifndef __PROCESSING_H__
#define __PROCESSING_H__

#include "defines.h"
#include "stack_array.h"
#include "stack_list.h"
#include "balanced_parentheses.h"
#include "timing.h"
#include "read.h"
#include "print.h"

int execute_menu_item(int8_t menu_item,
                      stack_array_t *stack_array,
                      bool *const check_stack_array,
                      stack_list_t **stack_list,
                      bool *const add_first_elem,
                      free_addr_t *const free_addr,
                      int *const size_stack_list);

#endif
