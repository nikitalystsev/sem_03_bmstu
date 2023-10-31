#include "matrix.h"
#include "revise.h"

int get_matrix_size(int *const n, int *const m, FILE *file)
{
    if (fscanf(file, "%d", n) != 1)
        return ERR_DIMENTION;

    if (fscanf(file, "%d", m) != 1)
        return ERR_DIMENTION;

    if (*n <= 0 || *m <= 0)
        return ERR_DIMENTION;

    return EXIT_SUCCESS;
}

int read_matrix_from_file(matrix_t *const matrix, const char *const file_name)
{
    int rc = 0;
    int n = 0, m = 0;
    int count_no_zero;
    FILE *file;

    if ((file = fopen(file_name, "r")) == NULL)
        return ERR_OPEN_FILE;

    if ((rc = get_matrix_size(&n, &m, file)) != 0)
    {
        fclose(file);
        return rc;
    }

    matrix->rows = n;
    matrix->cols = m;

    if ((rc = matrix_alloc(matrix)) != 0)
    {
        fclose(file);
        return rc;
    }

    if (fscanf(file, "%d", &count_no_zero) != 1)
    {
        fclose(file);
        return ERR_NO_ZERO_ELEM;
    }

    if (count_no_zero < 0 || count_no_zero > n * m)
    {
        fclose(file);
        return ERR_NO_ZERO_ELEM;
    }

    for (int i = 0; i < count_no_zero; i++)
    {
        int num_row, num_col;
        double value;

        if ((rc = check_index(&num_row, matrix->rows, file)) != 0)
        {
            fclose(file);
            return rc;
        }

        if ((rc = check_index(&num_col, matrix->cols, file)) != 0)
        {
            fclose(file);
            return rc;
        }

        if (fscanf(file, "%lf", &value) != 1)
        {
            fclose(file);
            return ERR_VALUE;
        }

        if (fabs(matrix->matrix[num_row - 1][num_col - 1]) >= EPS)
        {
            fclose(file);
            return ERR_ALREADY_NO_ZERO_ELEM;
        }
        
        matrix->matrix[num_row - 1][num_col - 1] = value;
    }
    
    fclose(file);

    return rc;
}

int matrix_alloc(matrix_t *const matrix)
{
    matrix->matrix = calloc(matrix->rows, sizeof(double *));

    if (!matrix->matrix)
        return ERR_ALLOC_MATRIX;

    for (size_t i = 0; i < matrix->rows; i++)
    {
        matrix->matrix[i] = calloc(matrix->cols, sizeof(double));

        if (!matrix->matrix[i])
        {
            matrix_free(matrix->matrix, matrix->rows);
            return ERR_ALLOC_MATRIX;
        }
    }

    return EXIT_SUCCESS;
}

void matrix_free(double **matrix, const size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(matrix[i]);

    free(matrix);
}

int gauss_det(const matrix_t *const matrix_cp, double *const det)
{
    *det = 1;

    matrix_t matrix;
    matrix.rows = matrix_cp->rows;
    matrix.cols = matrix_cp->cols;

    if (matrix_alloc(&matrix) != 0)
        return ERR_ALLOC_MATRIX;

    for (size_t i = 0; i < matrix.rows; i++)
        for (size_t j = 0; j < matrix.rows; j++)
            matrix.matrix[i][j] = matrix_cp->matrix[i][j];

    for (size_t i = 0; i < matrix.rows; ++i)
    {
        double mx = fabs(matrix.matrix[i][i]);
        size_t idx = i;

        for (size_t j = i + 1; j < matrix.rows; ++j)
            if (mx < fabs(matrix.matrix[i][j]))
                mx = fabs(matrix.matrix[i][idx = j]);

        if (idx != i)
        {
            for (size_t j = i; j < matrix.rows; ++j)
            {
                double t = matrix.matrix[j][i];
                matrix.matrix[j][i] = matrix.matrix[j][idx];
                matrix.matrix[j][idx] = t;
            }
            *det = -(*det);
        }
        for (size_t k = i + 1; k < matrix.rows; ++k)
        {
            double t = matrix.matrix[k][i] / matrix.matrix[i][i];

            for (size_t j = i; j < matrix.rows; ++j)
                matrix.matrix[k][j] -= matrix.matrix[i][j] * t;
        }
    }
    for (size_t i = 0; i < matrix.rows; ++i)
        *det *= matrix.matrix[i][i];

    matrix_free(matrix.matrix, matrix.rows);

    return EXIT_SUCCESS;
}

int inversion_matrix(matrix_t *const matrix)
{
    double temp;

    matrix_t iden;
    iden.rows = matrix->rows;
    iden.cols = matrix->cols;

    if (matrix_alloc(&iden) != 0)
        return ERR_ALLOC_MATRIX;

    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->rows; j++)
            iden.matrix[i][j] = i == j;

    for (size_t k = 0; k < matrix->rows; k++)
    {
        temp = matrix->matrix[k][k];

        for (size_t j = 0; j < matrix->rows; j++)
        {
            matrix->matrix[k][j] /= temp;
            iden.matrix[k][j] /= temp;
        }

        for (size_t i = k + 1; i < matrix->rows; i++)
        {
            temp = matrix->matrix[i][k];

            for (size_t j = 0; j < matrix->rows; j++)
            {
                matrix->matrix[i][j] -= matrix->matrix[k][j] * temp;
                iden.matrix[i][j] -= iden.matrix[k][j] * temp;
            }
        }
    }

    for (int k = matrix->rows - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = matrix->matrix[i][k];

            for (size_t j = 0; j < matrix->rows; j++)
            {
                matrix->matrix[i][j] -= matrix->matrix[k][j] * temp;
                iden.matrix[i][j] -= iden.matrix[k][j] * temp;
            }
        }
    }

    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->rows; j++)
            matrix->matrix[i][j] = iden.matrix[i][j];

    matrix_free(iden.matrix, iden.rows);

    return EXIT_SUCCESS;
}

void matrix_add(matrix_t *const matrix1,
matrix_t *const matrix2,
matrix_t *const matrix_res)
{
    for (size_t i = 0; i < matrix1->rows; i++)
        for (size_t j = 0; j < matrix1->cols; j++)
            matrix_res->matrix[i][j] =
                matrix1->matrix[i][j] + matrix2->matrix[i][j];
}

void matrix_mult(matrix_t *const matrix1,
matrix_t *const matrix2,
matrix_t *const matrix_res)
{
    for (size_t i = 0; i < matrix1->rows; i++)
        for (size_t j = 0; j < matrix2->cols; j++)
        {
            matrix_res->matrix[i][j] = 0;
            for (size_t k = 0; k < matrix1->cols; k++)
                matrix_res->matrix[i][j] +=
                    matrix1->matrix[i][k] * matrix2->matrix[k][j];
        }
}

int get_count_no_zero(const matrix_t *const matrix)
{
    int count = 0;

    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->cols; j++)
            if (fabs(matrix->matrix[i][j]) >= EPS)
                count++;
    
    return count;
}

int write_matrix_to_file_by_coord(const matrix_t *const matrix,  
const char *const file_name)
{
    FILE *file;
    
    if ((file = fopen(file_name, "w")) == NULL)
        return ERR_OPEN_FILE;

    int count_no_zero = get_count_no_zero(matrix);

    fprintf(file, "%lu %lu %d\n", matrix->rows, matrix->cols, count_no_zero);

    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->cols; j++)
            if (fabs(matrix->matrix[i][j]) >= EPS)
                fprintf(file, "%lu %lu %lf\n", i + 1, j + 1, matrix->matrix[i][j]);
    
    fclose(file);

    return EXIT_SUCCESS;
}
