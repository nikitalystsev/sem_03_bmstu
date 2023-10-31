#include "defines.h"
#include "my_node.h"

int main(int argc, char const *argv[])
{
    if (argc != 3)
        return ERR_PARAM;
    
    FILE *file;

    data_t *arr_data = NULL;
    node_t *head = NULL;
    int count_elements = 0;

    int rc = 0;

    if (!(file = fopen(argv[1], "r")))
        return ERR_OPEN_FILE;

    if ((rc = read_numbers(&arr_data, &count_elements, &head, file)) != 0)
        goto free_all;

    head = sort(head, compare);

    if ((rc = write_list_to_file(head, argv[2])) != 0)
        goto free_all;
    
    free_all:
    {
        free(arr_data);
        free_list(head);
        fclose(file);
    }

    return rc;
}
