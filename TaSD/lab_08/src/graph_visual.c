#include "graph_visual.h"

static void adj_list_to_dot(FILE *file, adj_list_t *head, int number)
{
    adj_list_t *tmp_head = head;

    while (tmp_head)
    {
        if (!tmp_head->is_del)
            fprintf(file, "%d -> %d [color=blue];\n", number,
                    tmp_head->number);
        tmp_head = tmp_head->next;
    }
}

int export_graph_to_dot(const char *file_name,
                        char *graph_name, graph_t *graph)
{
    int rc = 0;

    FILE *file = fopen(file_name, "w");

    if (!file)
    {
        puts(RED "Ошибка открытия файла!\n" RESET);
        return ERR_OPEN_FILE;
    }

    fprintf(file, "digraph %s {\n", graph_name);

    for (int i = 0; i < graph->size; i++)
        if (!graph->data[i].is_del)
            adj_list_to_dot(file, graph->data[i].head, graph->data[i].number);

    fprintf(file, "}\n");

    fclose(file);

    char s[MAX_STR_SIZE];

    snprintf(s, MAX_STR_SIZE, "dot -Tpng -O %s", file_name);

    rc = system(s);

    if (rc == 0)
        puts(GREEN "\nКартинка была успешно создана!" RESET);

    return rc;
}
