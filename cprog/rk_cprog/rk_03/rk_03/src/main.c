#include "defines.h"
#include "my_matrix.h"

/*
Номер по журналу 15
*/

int main(int argc, char const *argv[])
{

    int n = 0, m = 0;
    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        return ERR_OPEN_FILE;
    }

    argc = 0;
    int rc = 0;

    if ((rc = read_size_matrix(&n, &m, file)) != 0)
    {
        return rc;
    }

    matrix_t matrix;

    matrix.matrix = matrix_alloc(n, m);

    if (!matrix.matrix)
    {
        return ERR_ALLOC_MEM;
    }

    matrix.row = n;
    matrix.col = m;

    if ((rc = read_matrix_from_file(&matrix, file)) != 0)
    {
        free_matrix(matrix.matrix, matrix.row);
        return rc;
    }

    printf("matrix in:\n");
    print_matrix(&matrix);

    if ((rc = find_min_zero_matrix(&matrix)) != 0)
    {
        return rc;
    }

    printf("matrix out:\n");
    print_matrix(&matrix);

    if ((rc = write_matrix_to_file(&matrix, argv[2])) != 0)
    {
        free_matrix(matrix.matrix, matrix.row);
        return rc;
    }

    free_matrix(matrix.matrix, matrix.row);

    fclose(file);

    return argc;
}
