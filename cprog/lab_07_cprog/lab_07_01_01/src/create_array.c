#include "create_array.h"

int get_count_elements_from_file(FILE *file, 
const char *const file_name,
int *const count_elements)
{
    int counted_number;
    *count_elements = 0;

    file = fopen(file_name, "r");

    if (file == NULL)
        return ERR_OPEN_FILE;

    while (fscanf(file, "%d", &counted_number) == 1)
        (*count_elements)++;

    if (fclose(file) != 0)
        return ERR_CLOSE_FILE;

    if (*count_elements == 0)
        return ERR_NO_DATA;

    return EXIT_SUCCESS;
}

int get_count_elements(int *pb_src, int *pe_src)
{
    int count_elements = 0;

    for (int *ptr_cur = pb_src; ptr_cur < pe_src; ptr_cur++)
        count_elements++;
    
    return count_elements;  
}

int read_array(FILE *file,
const char *const file_name,
int *const ptr_start,
int *const ptr_end)
{
    int rc = 0;

    file = fopen(file_name, "r");

    if (file == NULL)
        return ERR_OPEN_FILE;

    for (int *ptr_cur = ptr_start; ptr_cur < ptr_end; ptr_cur++)
        if (fscanf(file, "%d", ptr_cur) != 1)
            rc = ERR_READ_ARRAY;

    if (fclose(file) != 0)
        return ERR_CLOSE_FILE;

    return rc;
}

int create_array(FILE *file,
const char *const file_name,
int **pb_src,
int **pe_src)
{
    int rc;
    int count_elements;

    if ((rc = get_count_elements_from_file(file, file_name, &count_elements)) != 0)
        return rc;

    *pb_src = malloc(count_elements * sizeof(int));

    if (*pb_src == NULL)
        return ERR_ALLOC_MEM;

    *pe_src = *pb_src + count_elements;

    if ((rc = read_array(file, file_name, *pb_src, *pe_src)) != 0)
        return rc;

    return EXIT_SUCCESS;
}
