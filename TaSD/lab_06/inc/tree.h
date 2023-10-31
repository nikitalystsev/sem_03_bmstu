#ifndef __TREE_H__
#define __TREE_H__

#include "defines.h"

typedef struct vertex_t vertex_t;
typedef struct tree_t tree_t;

struct vertex_t
{
    int data;
    vertex_t *left;  // меньшие
    vertex_t *right; // большие
};

struct tree_t
{
    vertex_t *root;
};

vertex_t *create_vertex(int data);

vertex_t *add_vertex(vertex_t *root, vertex_t *vertex);

vertex_t *search(vertex_t *root, int data);

vertex_t *find_parent(vertex_t *root, vertex_t *vertex);

int delete_vertex(vertex_t **root, int data);

bool is_empty_tree(tree_t *tree);

void free_vertex(vertex_t *root);

void free_tree(tree_t *tree);

int get_tree_depth(vertex_t *root);

int get_count_vertex_in_level(vertex_t *root, int n, int c);

void print_tree(vertex_t *root, int p);

#endif
