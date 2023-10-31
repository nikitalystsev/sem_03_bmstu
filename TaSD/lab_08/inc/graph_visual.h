#ifndef __GRAPH_VISUAL_H__
#define __GRAPH_VISUAL_H__

#include "defines.h"
#include "graph.h"

int export_graph_to_dot(const char *file_name,
                        char *graph_name, graph_t *graph);

#endif
