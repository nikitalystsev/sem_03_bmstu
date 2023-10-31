#include "process.h"

static int read_menu_item(int *item)
{
    if (scanf("%d", item) != 1)
    {
        puts(RED "\nНекорректный ввод пункта меню!" RESET);
        return ERR_MENU_ITEM;
    }

    if (*item < 0 || *item > 5)
    {
        puts(RED "\nНеверный номер пункта меню!" RESET);
        return ERR_MENU_ITEM;
    }

    return EXIT_SUCCESS;
}

static int read_file_name(char *file_name)
{
    puts(TURQ "\nВведите имя файла:" RESET);

    if (scanf("%s", file_name) != 1)
    {
        puts(RED "\nНевалидный ввод имени файла!" RESET);
        return ERR_READ_DATA;
    }

    return EXIT_SUCCESS;
}

static int read_del_number(int *number)
{
    puts(TURQ "\nВведите номер удаляемой вершины:" RESET);

    if (scanf("%d", number) != 1)
    {
        puts(RED "\nНевалидный ввод номера вершины!" RESET);
        return ERR_READ_DATA;
    }

    return EXIT_SUCCESS;
}

static int check_node(adj_list_t *node)
{
    if (node)
        return 0;

    return 1;
}

static bool is_empty_graph(graph_t *graph)
{
    if (!graph->data && graph->size == 0)
        return true;

    return false;
}

static int read_adj_list(FILE *file, vertex_t *vertex, int count_node)
{
    int rc = 0;

    int number;

    if (fscanf(file, "%d", &number) != 1)
    {
        fclose(file), puts(RED "\nОшибка чтения данных из файла!" RESET);
        return ERR_READ_DATA;
    }

    vertex->number = number;

    for (int i = 0; i < count_node; i++)
    {
        if (fscanf(file, "%d", &number) != 1)
        {
            fclose(file), puts(RED "\nОшибка чтения данных из файла!" RESET);
            return ERR_READ_DATA;
        }

        adj_list_t *node = create_node(number);

        if ((rc = check_node(node)) != 0)
        {
            puts(RED "\nОшибка выделения памяти!\n" RESET);
            return rc;
        }

        vertex->head = push_end(vertex->head, node);
    }

    return rc;
}

static int read_graph(graph_t *graph)
{
    free_graph(graph);

    int rc = 0;

    char file_name[MAX_STR_SIZE];
    char data_file[MAX_STR_SIZE] = DATA_DIR;

    if ((rc = read_file_name(file_name)) != 0)
        return rc;

    strcat(data_file, file_name);

    FILE *file = fopen(data_file, "r");

    if (!file)
    {
        puts(RED "Ошибка открытия файла!\n" RESET);
        return ERR_OPEN_FILE;
    }

    if (fscanf(file, "%d", &graph->size) != 1)
    {
        fclose(file), puts(RED "\nОшибка чтения данных из файла!" RESET);
        return ERR_READ_DATA;
    }

    if ((rc = create_graph(graph)) != 0)
    {
        fclose(file);
        return rc;
    }

    default_graph(graph);

    for (int i = 0; i < graph->size; i++)
    {
        int count_node;

        if (fscanf(file, "%d", &count_node) != 1)
        {
            fclose(file), puts(RED "\nОшибка чтения данных из файла!" RESET);
            return ERR_READ_DATA;
        }

        if ((rc = read_adj_list(file, &graph->data[i], count_node)) != 0)
        {
            fclose(file);
            return rc;
        }
    }

    fclose(file);

    if (rc == 0)
        puts(GREEN "\nДанные были успешно прочитаны!" RESET);

    return rc;
}

static int graph_to_dot(graph_t *graph)
{
    int rc = 0;

    if (!is_empty_graph(graph))
    {
        char data_file[MAX_STR_SIZE] = DATA_DIR;
        char data_gv[MAX_STR_SIZE];

        if ((rc = read_file_name(data_gv)) != 0)
            return rc;

        strcat(data_file, data_gv);

        if ((rc = export_graph_to_dot(data_file, "my_graph", graph)) != 0)
            return rc;
    }
    else
        puts(VIOLET "\nГраф пустой" RESET);

    return rc;
}

static void del_vertex_from_adj_list(adj_list_t *head, int number)
{
    adj_list_t *tmp = head;

    while (tmp)
    {
        if (tmp->number == number)
            tmp->is_del = true;

        tmp = tmp->next;
    }
}

static void conditional_del_vertex(graph_t *graph, int number)
{
    graph->data[number - 1].is_del = true;

    for (int i = 0; i < graph->size; i++)
        del_vertex_from_adj_list(graph->data[i].head, number);
}

static void recov_vertex_from_adj_list(adj_list_t *head, int number)
{
    adj_list_t *tmp = head;

    while (tmp)
    {
        if (tmp->number == number)
            tmp->is_del = false;

        tmp = tmp->next;
    }
}

static void recov_vertex(graph_t *graph, int number)
{
    graph->data[number - 1].is_del = false;

    for (int i = 0; i < graph->size; i++)
        recov_vertex_from_adj_list(graph->data[i].head, number);
}

static void clean_is_visited(graph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
        graph->data[i].is_visited = false;
}

static int size_list(adj_list_t *head)
{
    int size = 0;

    adj_list_t *tmp_head = head;

    while (tmp_head)
    {
        size += sizeof(int);
        size += sizeof(bool);
        size += sizeof(adj_list_t *);

        tmp_head = tmp_head->next;
    }

    return size;
}

static int vertex_size(vertex_t *vertex)
{
    int size = 0;

    size += sizeof(vertex->number);
    size += (2 * sizeof(vertex->is_del));
    size += sizeof(adj_list_t *);

    return size;
}

static int graph_size(graph_t *graph)
{
    int size = 0;

    size += (graph->size * vertex_size(&graph->data[0]));

    for (int i = 0; i < graph->size; i++)
        size += size_list(graph->data[i].head);

    return size;
}

static int perform_a_check(graph_t *graph)
{
    int rc = 0;

    long double beg, end;

    if (!is_empty_graph(graph))
    {
        bool is_can = false;

        beg = microseconds_now();

        for (int i = 0; i < graph->size; i++)
        {
            conditional_del_vertex(graph, i + 1);

            int count_visited = 0;

            int number = find_vertex_for_DFS(graph);

            DFS(graph, number, &count_visited);
            clean_is_visited(graph);

            int count_edges = get_count_edges(graph);

            /*
            первое условие - проверка на связность
            второе условие - критерий дерева
            */

            if (count_visited == graph->size - 1 &&
                graph->size - 1 - 1 == count_edges)
                printf(GREEN "Можно, для этого нужно удалить "
                             "вершину с номером %d\n" RESET,
                       i + 1),
                    is_can = true;
            recov_vertex(graph, i + 1);
        }

        end = microseconds_now() - beg;

        if (!is_can)
            puts(VIOLET "\nГраф нельзя превратить в дерево!" RESET);

        printf(YELLOW "\nВремя работы программы (мкс) = %LF\n" RESET, end);

        int size = graph_size(graph);

        printf(YELLOW "\nРазмер памяти (байты), "
                      "требуемый для хранения графа = %d\n" RESET,
               size);
    }
    else
        puts(VIOLET "\nГраф пустой" RESET);

    return rc;
}

static int del_vertex(graph_t *graph)
{
    int rc = 0;

    if (!is_empty_graph(graph))
    {
        int number;

        if ((rc = read_del_number(&number)) != 0)
            return rc;

        if (number < 1 || number > graph->size)
            printf(VIOLET "Вершины с номером %d нет в графе!\n", number);
        else
        {
            conditional_del_vertex(graph, number);
            printf(GREEN "Вершина с номером %d "
                         "была успешно удалена!\n",
                   number);
        }
    }
    else
        puts(VIOLET "\nГраф пустой" RESET);

    return rc;
}

static void recov_all_vertex(graph_t *graph)
{
    if (!is_empty_graph(graph))
    {
        for (int i = 0; i < graph->size; i++)
            recov_vertex(graph, i + 1);

        puts(GREEN "\nУдаленные вершины были успешно восстановлены!" RESET);
    }
    else
        puts(VIOLET "\nГраф пустой" RESET);
}

int process(void)
{
    int rc = 0;

    graph_t graph;
    graph.size = 0, graph.data = NULL;

    while (true)
    {
        print_menu();

        int menu_item;

        if ((rc = read_menu_item(&menu_item)) != 0)
            goto free;

        switch (menu_item)
        {
        case 0:
            free_graph(&graph);
            exit(0);
            break;
        case 1:
            if ((rc = read_graph(&graph)) != 0)
                goto free;
            break;
        case 2:
            if ((rc = graph_to_dot(&graph)) != 0)
                goto free;
            break;
        case 3:
            if ((rc = perform_a_check(&graph)) != 0)
                goto free;
            break;
        case 4:
            if ((rc = del_vertex(&graph)) != 0)
                goto free;
            break;
        case 5:
            recov_all_vertex(&graph);
            break;
        default:
            break;
        }
    }

free:
    free_graph(&graph);

    return rc;
}
