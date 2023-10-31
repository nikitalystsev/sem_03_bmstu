#include "write_numbers_to_file.h"

int write_numbers_to_file(FILE *file,
const char *const file_name,
int *ptr_start,
int *ptr_end)
{
    file = fopen(file_name, "w");

    if (file == NULL)
        return ERR_OPEN_FILE;
    
    for (int *ptr_cur = ptr_start; ptr_cur < ptr_end; ptr_cur++)
        fprintf(file, "%d ", *ptr_cur);
     
    if (fclose(file) != 0)
        return ERR_CLOSE_FILE;

    return EXIT_SUCCESS;
}
