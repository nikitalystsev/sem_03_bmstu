#include "tree.h"

vertex_t *create_vertex(int data)
{
    vertex_t *vertex = malloc(sizeof(vertex_t));

    if (vertex)
    {
        vertex->data = data;
        vertex->left = NULL;
        vertex->right = NULL;
    }

    return vertex;
}

vertex_t *add_vertex(vertex_t *root, vertex_t *vertex)
{
    if (!root)
    {
        return vertex;
    }

    if (vertex->data < root->data)
    {
        root->left = add_vertex(root->left, vertex);
    }
    else if (vertex->data > root->data)
    {
        root->right = add_vertex(root->right, vertex);
    }

    return root;
}

vertex_t *search(vertex_t *root, int data)
{
    if (!root)
    {
        return NULL;
    }

    if (data < root->data)
    {
        return search(root->left, data);
    }
    if (data > root->data)
    {
        return search(root->right, data);
    }

    return root;
}

/*
Функция для нахождения родителя элемента.
Случай, когда элементом является корень, не обрабатывается
*/
vertex_t *find_parent(vertex_t *root, vertex_t *vertex)
{
    if (!root)
    {
        return NULL;
    }

    if (vertex->data < root->data)
    {
        if (root->left->data == vertex->data)
        {
            return root;
        }

        return find_parent(root->left, vertex);
    }
    if (vertex->data > root->data)
    {
        if (root->right->data == vertex->data)
        {
            return root;
        }

        return find_parent(root->right, vertex);
    }

    return root;
}

static vertex_t *find_min_right(vertex_t *vertex)
{
    vertex_t *tmp_vertex = vertex;

    while (tmp_vertex->left)
    {
        tmp_vertex = tmp_vertex->left;
    }

    return tmp_vertex;
}

// static vertex_t *find_max_left(vertex_t *vertex)
// {
//     vertex_t *tmp_vertex = vertex;

//     while (tmp_vertex->right)
//     {
//         tmp_vertex = tmp_vertex->right;
//     }

//     return tmp_vertex;
// }

int delete_vertex(vertex_t **root, int data)
{
    vertex_t *parent = NULL;
    vertex_t *find = search(*root, data);
    if (!find)
    {
        return NOT_FOUND;
    }

    // если удаляемый не корень, то находим родителя
    if (find != *root)
    {
        parent = find_parent(*root, find);
    }

    // у удаляемого элемента есть оба потомка
    if (find->left && find->right)
    {
        // находим самый левый (минимальный) элемент в правом поддереве
        vertex_t *min_right = find_min_right(find->right);

        // или находим самый правый (максимальный) элемент в левом поддереве
        // vertex_t *min_right = find_max_left(find->left);

        int data = min_right->data;

        // удаляем всех преемников найденного (min_right) элемента
        // и его самого тоже
        delete_vertex(root, min_right->data);

        find->data = data;
    }
    // у удаляемого элемента 0 или 1 потомок
    else
    {
        // переводится heir как преемник
        vertex_t *heir = (find->left) ? find->left : find->right;

        if (!parent)
        {
            if (!heir)
                free(*root);
            *root = heir;
        }
        else
        {
            if (parent->left == find)
            {
                free(find);
                parent->left = heir, find = NULL;
            }
            else if (parent->right == find)
            {
                free(find);
                parent->right = heir, find = NULL;
            }
        }
    }

    return EXIT_SUCCESS;
}

bool is_empty_tree(tree_t *tree)
{
    if (!tree->root)
    {
        puts(VIOLET "\nДерево пустое" RESET);
        return true;
    }

    return false;
}

void free_vertex(vertex_t *root)
{
    if (root)
    {
        free_vertex(root->right);
        free_vertex(root->left);
    }

    free(root);
}

void free_tree(tree_t *tree)
{
    free_vertex(tree->root);
    tree->root = NULL;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int get_tree_depth(vertex_t *root)
{
    if (!root)
    {
        return 0;
    }

    int ldepth = get_tree_depth(root->left);
    int rdepth = get_tree_depth(root->right);

    if (ldepth > rdepth)
    {
        return ldepth + 1;
    }

    return rdepth + 1;
}

int get_count_vertex_in_level(vertex_t *root, int n, int c)
{

    if (n == c)
    {
        return 1;
    }

    int count = 0;

    if (root->left)
    {
        count += get_count_vertex_in_level(root->left, n, c + 1);
    }
    if (root->right)
    {
        count += get_count_vertex_in_level(root->right, n, c + 1);
    }

    return count;
}

void print_tree(vertex_t *root, int p)
{
    if (!root)
    {
        return;
    }

    print_tree(root->right, p + 3);

    printf("\n");
    for (int i = 0; i < p; i++)
    {
        printf(" ");
    }

    printf("%3d\n", root->data);
    print_tree(root->left, p + 3);
}
