#ifndef __TREE_VISUAL_H__
#define __TREE_VISUAL_H__

#include "defines.h"
#include "tree.h"

void vertex_to_dot(vertex_t *vertex, FILE *file);

void tree_to_dot(vertex_t *root, FILE *file);

int export_to_dot(const char *file_name, char *tree_name, tree_t *tree);

#endif
