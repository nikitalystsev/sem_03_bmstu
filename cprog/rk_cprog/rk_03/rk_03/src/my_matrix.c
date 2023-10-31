#include "my_matrix.h"

int32_t **matrix_alloc(const int n, const int m)
{
    int32_t **data = calloc(n, sizeof(int32_t *));

    if (!data)
    {
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        data[i] = malloc(m * sizeof(int32_t));

        if (!data[i])
        {
            free_matrix(data, n);
            return NULL;
        }
    }

    return data;
}

void free_matrix(int32_t **matrix, const int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
}

int read_size_matrix(int *const n, int *const m, FILE *const file)
{
    if (fscanf(file, "%d", n) != 1)
    {
        return ERR_READ_SIZE;
    }

    if (fscanf(file, "%d", m) != 1)
    {
        return ERR_READ_SIZE;
    }

    if (*n <= 0 || *m <= 0)
    {
        return ERR_SIZE;
    }

    return EXIT_SUCCESS;
}

int read_matrix_from_file(matrix_t *const matrix, FILE *const file)
{

    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->col; j++)
        {
            if (fscanf(file, "%d", &matrix->matrix[i][j]) != 1)
            {
                return ERR_READ_MATRIX;
            }
        }

    return EXIT_SUCCESS;
}

void print_row(const int32_t *const row, const int m)
{
    for (int i = 0; i < m; i++)
    {
        printf("%4d ", row[i]);
    }

    printf("\n");
}

void print_matrix(const matrix_t *const matrix)
{
    for (int i = 0; i < matrix->row; i++)
    {
        print_row(matrix->matrix[i], matrix->col);
    }
}

int write_matrix_to_file(const matrix_t *const matrix,
                         const char *const file_name)
{
    FILE *file = fopen(file_name, "w");

    if (!file)
    {
        return ERR_OPEN_FILE;
    }

    fprintf(file, "%d %d\n", matrix->row, matrix->col);

    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->col; j++)
        {
            fprintf(file, "%d ", matrix->matrix[i][j]);
        }

    fprintf(file, "\n");

    fclose(file);

    return EXIT_SUCCESS;
}

bool isnull(int32_t number)
{
    if (number != 0)
    {
        return false;
    }

    return true;
}

int delete_col(matrix_t *const matrix)
{
    for (int k = 0; k < matrix->row; k++)
    {
        matrix->matrix[k] = realloc(matrix->matrix[k], matrix->col - 1);

        if (!matrix->matrix[k])
        {
            return ERR_ALLOC_MEM;
        }
    }

    return EXIT_SUCCESS;
}

int find_min_zero_matrix(matrix_t *const matrix)
{
    for (int i = 0; i < matrix->row; i++)
    {
        for (int j = 0; j < matrix->col; j++)
        {
            if (isnull(matrix->matrix[i][j]))
            {
                delete_col(matrix);

                matrix->col--;
            }
        }
    }

    return EXIT_SUCCESS;
}
