#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "defines.h"
#include "tree.h"
#include "print.h"
#include "tree_visual.h"
#include "gen_data.h"
#include "timing.h"

void compare_time_add(tree_t *tree, const char *file_name,
                      int size, long double *end1, long double *end2);

void compare(tree_t *tree, const char *file_name);

int add_file(const char *file_name, int data);
int process(void);

#endif
