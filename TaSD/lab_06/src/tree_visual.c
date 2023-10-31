#include "tree_visual.h"

void vertex_to_dot(vertex_t *vertex, FILE *file)
{
    if (vertex->left)
    {
        fprintf(file, "%d -> %d [color=blue];\n", vertex->data,
                vertex->left->data);
    }
    if (vertex->right)
    {
        fprintf(file, "%d -> %d [color=red];\n", vertex->data,
                vertex->right->data);
    }
}

void tree_to_dot(vertex_t *root, FILE *file)
{
    if (!root)
    {
        return;
    }

    vertex_to_dot(root, file);

    tree_to_dot(root->left, file);
    tree_to_dot(root->right, file);
}

int export_to_dot(const char *file_name, char *tree_name, tree_t *tree)
{
    FILE *file = fopen(file_name, "w");
    if (!file)
    {
        puts(RED "Ошибка открытия файла!\n" RESET);
        return ERR_OPEN_FILE;
    }

    fprintf(file, "digraph %s {\n", tree_name);

    tree_to_dot(tree->root, file);

    fprintf(file, "}\n");

    fclose(file);

    char s[MAX_STR_SIZE];

    snprintf(s, MAX_STR_SIZE, "dot -Tpng -O %s", file_name);

    int rc = system(s);

    if (rc == 0)
        puts(GREEN "\nКартинка была успешно создана!" RESET);

    return rc;
}
