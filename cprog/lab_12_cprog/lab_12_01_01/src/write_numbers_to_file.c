#include "write_numbers_to_file.h"

int write_numbers_to_file(FILE *file, const char *const file_name,
int *ptr_start, int *ptr_end)
{
    if ((file = fopen(file_name, "w")) == NULL)
        return ERR_OPEN_FILE;
    
    for (int *ptr_cur = ptr_start; ptr_cur < ptr_end; ptr_cur++)
        fprintf(file, "%d ", *ptr_cur);
     
    fclose(file);

    return EXIT_SUCCESS;
}
