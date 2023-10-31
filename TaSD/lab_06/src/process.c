#include "process.h"

static int read_menu_item(int *item)
{
    if (scanf("%d", item) != 1)
    {
        puts(RED "\nНекорректный ввод пункта меню!" RESET);
        return ERR_MENU_ITEM;
    }

    if (*item < 0 || *item > 9)
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
        puts(RED "Невалидный ввод имени файла!" RESET);
        return ERR_READ_DATA;
    }

    return EXIT_SUCCESS;
}

int read_data(const char *file_name, tree_t *tree)
{
    int rc = 0;

    FILE *file = fopen(file_name, "r");
    if (!file)
    {
        puts(RED "Ошибка открытия файла!\n" RESET);
        return ERR_OPEN_FILE;
    }

    int count, data;

    if (fscanf(file, "%d", &count) != 1)
    {
        fclose(file), puts(RED "Ошибка чтения данных из файла!\n" RESET);
        return ERR_READ_DATA;
    }

    for (int i = 0; i < count; i++)
    {
        if (fscanf(file, "%d", &data) != 1)
        {
            fclose(file), puts(RED "Ошибка чтения данных из файла!\n" RESET);
            return ERR_READ_DATA;
        }

        vertex_t *vertex = create_vertex(data);
        if (!vertex)
        {
            fclose(file);
            return ERR_READ_DATA;
        }

        tree->root = add_vertex(tree->root, vertex);
    }

    fclose(file);

    if (rc == 0)
        puts(GREEN "\nДанные были успешно прочитаны!" RESET);

    return rc;
}

int read_elem_tree(int *num)
{
    puts(TURQ "\nВведите элемент дерева:" RESET);

    if (scanf("%d", num) != 1)
    {
        puts(RED "\nНекорректный ввод элемента дерева!" RESET);
        return ERR_MENU_ITEM;
    }

    return EXIT_SUCCESS;
}

int add(tree_t *tree, int data)
{
    int rc = 0;

    vertex_t *vertex = create_vertex(data);

    if (!vertex)
    {
        puts(RED "Ошибка добавления данных!\n" RESET);
        return ERR_READ_DATA;
    }

    tree->root = add_vertex(tree->root, vertex);

    return rc;
}

// int add_file(const char *file_name, int data)
// {
//     int rc = 0;

//     FILE *file = fopen(file_name, "r");
//     if (!file)
//     {
//         return ERR_OPEN_FILE;
//     }

//     int count;

//     if (fscanf(file, "%d", &count) != 1)
//     {
//         fclose(file);
//         return ERR_READ_DATA;
//     }

//     // считывание данных из файла в массив
//     int *data_arr = malloc((count + 1) * sizeof(int));
//     if (!data_arr)
//     {
//         fclose(file);
//         return ERR_ALLOC_MEM;
//     }

//     for (int i = 0; i < count; i++)
//     {
//         if (fscanf(file, "%d", &data_arr[i]) != 1)
//         {
//             fclose(file);
//             return ERR_READ_DATA;
//         }
//     }
//     // добавление нового элемента
//     data_arr[count] = data;

//     fclose(file);
//     // запись измененного массива в файл
//     file = fopen(file_name, "w");
//     if (!file)
//     {
//         return ERR_OPEN_FILE;
//     }

//     fprintf(file, "%d\n", count + 1);

//     for (int i = 0; i <= count; i++)
//     {
//         fprintf(file, "%d\n", data_arr[i]);
//     }

//     fclose(file);

//     free(data_arr);

//     return rc;
// }

int add_file(const char *file_name, int data)
{
    int rc = 0;

    FILE *file = fopen(file_name, "a");
    if (!file)
    {
        return ERR_OPEN_FILE;
    }

    fprintf(file, "%d\n", data);
    
    fclose(file);

    return rc;
}

void del(tree_t *tree, int data)
{
    if (delete_vertex(&tree->root, data) != 0)
    {
        puts(VIOLET "\nУдаляемого элемента в дереве нет" RESET);
    }
    else
    {
        printf(GREEN "\nЭлемент со значением (%d) "
                     "был успешно удален!\n" RESET,
               data);
    }
}

void clean_file(const char *file_name)
{
    FILE *file = fopen(file_name, "w");
    fprintf(file, "%d\n", 0);
    fclose(file);
}

void compare(tree_t *tree, const char *file_name)
{
    printf(YELLOW "\n|----------------------------------------------------------------|\n");
    printf("│ Количество элементов │        Добавление элемента (мкс)        │\n");
    printf("| Измерений для        |-----------------------------------------|\n");
    printf("│ каждого случая = %3d │       Дерево       │        Файл        │\n", N_REPS);
    printf("|----------------------------------------------------------------|\n");

    srand(time(NULL));
    int size = 1000;

    long double end1, end2;

    long double sum1 = 0, sum2 = 0;
    for (int i = 0; i < N_REPS && size <= 10000;)
    {
        compare_time_add(tree, file_name, size, &end1, &end2);
        free_tree(tree);
        clean_file(file_name);

        sum1 += end1, sum2 += end2;

        if (i == N_REPS - 1)
        {
            sum1 = sum1 / N_REPS, sum2 = sum2 / N_REPS;
            print_compare_time(sum1, sum2, size);
            size += 1000;
            sum1 = 0, sum2 = 0;
            i = 0;
        }
        else
            i++;
    }
}

void compare_time_add(tree_t *tree, const char *file_name,
                      int size, long double *end1, long double *end2)
{
    for (int i = 0; i < size; i++)
    {
        int data = MIN_DATA + rand() % (MAX_DATA - MIN_DATA + 1);

        long double beg = microseconds_now();
        add(tree, data);
        *end1 = microseconds_now() - beg;

        beg = microseconds_now();
        add_file(file_name, data);
        *end2 = microseconds_now() - beg;
    }
}

bool is_exist_file(const char *file_name)
{
    FILE *file = fopen(file_name, "r");

    if (!file)
        return false;

    fclose(file);

    return true;
}

int process(void)
{
    int rc = 0;

    tree_t tree;
    tree.root = NULL;

    int elem;

    char name[10000];
    char data_file[10000] = PATH;
    char data_gv[10000];

    int l = 0, t = 0;

    while (true)
    {
        print_menu();

        int menu_item;

        if ((rc = read_menu_item(&menu_item)) != 0)
            goto free;

        switch (menu_item)
        {
        case 0:
            free_tree(&tree);
            exit(0);
            break;
        case 1:
            if ((rc = read_file_name(name)) != 0)
                goto free;
            strcat(data_file, name);
            if (!is_exist_file(data_file))
                gen_data_file(data_file);
            strcpy(data_gv, data_file);
            strcat(data_gv, GV);
            if ((rc = read_data(data_file, &tree)) != 0)
                goto free;
            break;
        case 2:
            if ((rc = read_elem_tree(&elem)) != 0)
                goto free;
            if ((rc = add(&tree, elem)) != 0)
                goto free;
            break;
        case 3:
            if ((rc = read_elem_tree(&elem)) != 0)
                goto free;
            if ((rc = add_file(data_file, elem)) != 0)
                goto free;
            break;
        case 4:
            if ((rc = read_elem_tree(&elem)) != 0)
                goto free;
            del(&tree, elem);
            break;
        case 5:
            if (!is_empty_tree(&tree))
                print_tree(tree.root, 3);
            break;
        case 6:

            if (!is_empty_tree(&tree))
                if ((rc = export_to_dot(data_gv, "my_tree", &tree)) != 0)
                    goto free;
            break;
        case 7:
            if (!is_empty_tree(&tree))
                while ((l = get_count_vertex_in_level(tree.root, t++, 0)) != 0)
                {
                    printf(GREEN "level(%d) = %d\n" RESET, t - 1, l);
                }
            t = 0, l = 0;
            break;
        case 8:
            free_tree(&tree);
            clean_file("./data/compare.txt");
            compare(&tree, "./data/compare.txt");
            break;
        case 9:
            if (!is_empty_tree(&tree))
            {
                free_tree(&tree);
                puts(GREEN "\nДерево было успешно очищено!" RESET);
            }
            break;
        default:
            break;
        }
    }

free:
    free_tree(&tree);

    return rc;
}
