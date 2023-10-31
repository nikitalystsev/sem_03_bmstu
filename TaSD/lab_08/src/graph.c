#include "graph.h"

adj_list_t *create_node(int number)
{
    adj_list_t *node = malloc(sizeof(adj_list_t));

    if (node)
    {
        node->number = number;
        node->is_del = false;
        node->next = NULL;
    }

    return node;
}

int create_graph(graph_t *graph)
{
    graph->data = malloc(sizeof(vertex_t) * graph->size);

    if (!graph->data)
        return ERR_MEM_ALLOC;

    return EXIT_SUCCESS;
}

adj_list_t *push_end(adj_list_t *head, adj_list_t *node)
{
    adj_list_t *cur = head;

    if (!head)
        return node;

    for (; cur->next; cur = cur->next)
        ;

    cur->next = node;

    return head;
}

void default_graph(graph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        graph->data[i].head = NULL;
        graph->data[i].is_visited = false;
        graph->data[i].is_del = false;
    }
}

int find_vertex_for_DFS(graph_t *graph)
{
    int number = 1;

    for (int i = 0; i < graph->size; i++)
        if (!graph->data[i].is_visited && !graph->data[i].is_del)
            number = graph->data[i].number;

    return number;
}

/// @brief модифицированный алгоритм поиска в глубину
/// @param graph граф
/// @param number вершина, с которой начинается обход
/// @return через указатель число пройденных вершин
void DFS(graph_t *graph, int number, int *count_visited)
{
    if (!graph->data[number - 1].is_del)
    {
        (*count_visited)++;
        
        graph->data[number - 1].is_visited = true;

        adj_list_t *tmp = graph->data[number - 1].head;

        while (tmp)
        {
            int cur_number = tmp->number;
            if (!graph->data[cur_number - 1].is_visited && !tmp->is_del)
                DFS(graph, cur_number, count_visited);

            tmp = tmp->next;
        }
    }
}

static int get_real_count_node(adj_list_t *head)
{
    int count_node = 0;

    adj_list_t *tmp = head;

    while (tmp)
    {
        if (!tmp->is_del)
            count_node++;

        tmp = tmp->next;
    }

    return count_node;
}

// основана на формуле степеней графа
int get_count_edges(graph_t *graph)
{
    int sum_degrees = 0;

    for (int i = 0; i < graph->size; i++)
        if (!graph->data[i].is_del)
            sum_degrees += get_real_count_node(graph->data[i].head);

    int count_edges = sum_degrees / 2;

    return count_edges;
}

void free_agj_list(adj_list_t *head)
{
    adj_list_t *next;

    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

void free_graph(graph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
        free_agj_list(graph->data[i].head);

    free(graph->data);

    graph->data = NULL;
    graph->size = 0;
}
