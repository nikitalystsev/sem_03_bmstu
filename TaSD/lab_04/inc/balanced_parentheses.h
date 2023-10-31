#ifndef __BALANCED_PARENTHESES_H__
#define __BALANCED_PARENTHESES_H__

#include "defines.h"
#include "stack_array.h"
#include "stack_list.h"

bool ismatching_pair(const char character1, const char character2);

bool balanced_parentheses_stack_array(stack_array_t *const stack,
                                      const char *const exp);

bool balanced_parentheses_stack_list(stack_list_t **stack,
                                     const char *const exp);

#endif
