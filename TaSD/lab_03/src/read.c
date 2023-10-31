#include "read.h"

int get_choise_option_of_mtr_create(int *const choise_option)
{
    if (scanf("%d", choise_option) != 1)
    {
        printf("Некорректный ввод выбора опции!\n");
        return ERR_READ_CHOISE_OPTION;
    }

    if (*choise_option != 0 && *choise_option != 1)
    {
        printf("Неверный ввод! Выбор опции создания матрицы - целое число от 0 до 1\n");
        return ERR_CHOISE_OPTION;
    }

    return EXIT_SUCCESS;
}

int get_size_matrix(int *const row, int *const col)
{
    printf("Введите количество строк матрицы (целое число от 1 до 20000):\n");
    if (scanf("%d", row) != 1)
    {
        printf("Некорректный ввод количества строк матрицы!\n");
        return ERR_READ_COUNT_ROW;
    }
    if (*row < 1 || *row > MAX_SIZE_MATRIX)
    {
        printf("Неверный ввод! Количество строк матрицы - целое число от 1 до 20000\n");
        return ERR_COUNT_ROW;
    }

    printf("Введите количество столбцов матрицы (целое число от 1 до 20000):\n");
    if (scanf("%d", col) != 1)
    {
        printf("Некорректный ввод количества столбцов матрицы!\n");
        return ERR_READ_COUNT_ROW;
    }
    if (*col < 1 || *col > MAX_SIZE_MATRIX)
    {
        printf("Неверный ввод! Количество столбцов матрицы - целое число от 1 до 20000\n");
        return ERR_COUNT_COL;
    }

    return EXIT_SUCCESS;
}

int get_size_vector_col(int *const row)
{
    printf("Введите количество строк вектора столбца (целое число от 1 до 20000):\n");
    if (scanf("%d", row) != 1)
    {
        printf("Некорректный ввод количества строк вектора столбца!\n");
        return ERR_READ_COUNT_ROW;
    }
    if (*row < 1 || *row > MAX_SIZE_MATRIX)
    {
        printf("Неверный ввод! Количество строк вектора столбца - целое число от 1 до 20000\n");
        return ERR_COUNT_ROW;
    }

    return EXIT_SUCCESS;
}

int check_sizes_for_mult(const int col_matrix, const int row_vector_col)
{
    if (col_matrix != row_vector_col)
    {
        printf("Неверные размеры матрицы и вектора столбца! Их нельзя умножать\n");
        return ERR_CHECK_SIZES;
    }

    return EXIT_SUCCESS;
}

int input_no_zero_elem(int *const count_no_zero, const int row, const int col)
{
    if (scanf("%d", count_no_zero) != 1)
    {
        printf("Некорректный ввод количества ненулевых элементов!\n");
        return ERR_READ_COUNT_NO_ZERO;
    }
    if (*count_no_zero < 0 || *count_no_zero > row * col)
    {
        printf("Неверный ввод! Количество ненулевых элементов - целое число от 0 до %d\n", row * col);
        return ERR_COUNT_NO_ZERO;
    }

    return EXIT_SUCCESS;
}

int matrix_alloc(std_matrix_t *const matrix)
{
    matrix->matrix = calloc(matrix->count_row, sizeof(int *));

    if (!matrix->matrix)
    {
        printf("Ошибка выделения памяти!\n");
        return ERR_ALLOC_MATRIX;
    }

    for (int i = 0; i < matrix->count_row; i++)
    {
        matrix->matrix[i] = calloc(matrix->count_col, sizeof(int));

        if (!matrix->matrix[i])
        {
            matrix_free(matrix->matrix, matrix->count_row);
            printf("Ошибка выделения памяти!\n");
            return ERR_ALLOC_MATRIX;
        }
    }

    return EXIT_SUCCESS;
}

void matrix_free(int **matrix, const size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
}

int array_alloc(int **array, int count_elements)
{
    *array = calloc(count_elements, sizeof(int));

    if (!*array)

    {
        printf("Ошибка выделения памяти!\n");
        return ERR_ALLOC_MEMORY;
    }

    return EXIT_SUCCESS;
}

void fill_std_matrix_by_random(std_matrix_t *const std_matrix,
                               const int count_no_zero)
{
    srand(time(NULL));

    for (int i = 0; i < count_no_zero; i++)
    {
        int ind_row, ind_col, value;

        ind_row = rand() % std_matrix->count_row;
        ind_col = rand() % std_matrix->count_col;

        while (std_matrix->matrix[ind_row][ind_col] != 0)
        {
            ind_row = rand() % std_matrix->count_row;
            ind_col = rand() % std_matrix->count_col;
        }
        value = 1 + rand() % 100;

        std_matrix->matrix[ind_row][ind_col] = value;
    }
}

int get_count_no_zero(std_matrix_t *const std_matrix)
{
    int count = 0;

    for (int i = 0; i < std_matrix->count_row; i++)
        for (int j = 0; j < std_matrix->count_col; j++)
        {
            if (std_matrix->matrix[i][j] != 0)
                count++;
        }

    return count;
}

int read_indexes_std_matrix_for_elem(int *const ind_row,
                                     int *const ind_col,
                                     const int count_row,
                                     const int count_col)
{
    printf("Введите номер строки для ненулевого элемента (целое число от 0 до %d):\n",
           count_row - 1);
    if (scanf("%d", ind_row) != 1)
    {
        printf("Некорректный ввод! Индекс строки - целое число от 0 до %d\n",
               count_row - 1);
        return ERR_READ_IND_ROW;
    }
    if (*ind_row < 0 || *ind_row > count_row - 1)
    {
        printf("Некорректный ввод! Индекс строки - целое число от 0 до %d\n",
               count_row - 1);
        return ERR_IND_ROW;
    }

    printf("Введите номер столбца для ненулевого элемента (целое число от 0 до %d):\n",
           count_col - 1);
    if (scanf("%d", ind_col) != 1)
    {
        printf("Некорректный ввод! Индекс столбца - целое число от 0 до %d\n",
               count_col - 1);
        return ERR_READ_IND_COL;
    }
    if (*ind_col < 0 || *ind_col > count_col - 1)
    {
        printf("Некорректный ввод! Индекс столбца - целое число от 0 до %d\n",
               count_col - 1);
        return ERR_IND_COL;
    }

    return EXIT_SUCCESS;
}

int get_matrix_element(int *const value)
{
    printf("Введите значение для ненулевого элемента (целое число)\n");
    if (scanf("%d", value) != 1)
    {
        printf("Некорректный ввод! Значение элемента - целое число\n");
        return ERR_READ_VALUE;
    }
    if (*value == 0)
    {
        printf("Введенное значение элемента является нулевым!\n");
        return ERR_VALUE;
    }

    return EXIT_SUCCESS;
}

int fill_matrix_by_input(std_matrix_t *const std_matrix,
                         const int count_no_zero)
{
    int rc = 0;

    for (int i = 0; i < count_no_zero; i++)
    {
        int ind_row, ind_col, value;

        if ((rc = read_indexes_std_matrix_for_elem(
                 &ind_row, &ind_col, std_matrix->count_row, std_matrix->count_col)) != 0)
            return rc;

        if (std_matrix->matrix[ind_row][ind_col] != 0)
        {
            printf("Элемент под такими номерами строки и столбца уже ненулевой!\n");
            return ERR_ALREADY_NO_ZERO;
        }

        if ((rc = get_matrix_element(&value)) != 0)
            return rc;

        std_matrix->matrix[ind_row][ind_col] = value;
    }

    return rc;
}

int get_size_std_matrix_from_file(std_matrix_t *const std_matrix, FILE *file)
{
    if (fscanf(file, "%d", &(std_matrix->count_row)) != 1)
    {
        return ERR_READ_COUNT_ROW;
    }
    if (std_matrix->count_row < 0 || std_matrix->count_row > 20000)
    {
        return ERR_COUNT_ROW;
    }

    if (fscanf(file, "%d", &(std_matrix->count_col)) != 1)
    {
        return ERR_READ_COUNT_ROW;
    }
    if (std_matrix->count_col < 0 || std_matrix->count_col > 20000)
    {
        return ERR_COUNT_COL;
    }

    return EXIT_SUCCESS;
}

int get_std_matrix_from_file(std_matrix_t *const std_matrix,
                             const char *const file_name)
{
    FILE *file;
    int rc = 0;

    if ((file = fopen(file_name, "r")) == NULL)
    {
        return ERR_OPEN_FILE;
    }

    if ((rc = get_size_std_matrix_from_file(std_matrix, file)) != 0)
    {
        fclose(file);
        return rc;
    }

    if ((rc = matrix_alloc(std_matrix)) != 0)
    {
        fclose(file);
        return rc;
    }

    for (int i = 0; i < std_matrix->count_row; i++)
        for (int j = 0; j < std_matrix->count_col; j++)
        {
            if (fscanf(file, "%d", &std_matrix->matrix[i][j]) != 1)
            {
                return ERR_READ_VALUE;
            }
        }

    return EXIT_SUCCESS;
}

int copy_std_matrix_to_sparse_matrix(const std_matrix_t *const std_matrix,
                                     sparse_matrix_t *const sparse_matrix,
                                     const int count_no_zero)
{

    sparse_matrix->count_row = std_matrix->count_row;
    sparse_matrix->count_col = std_matrix->count_col;

    int ind_data = 0;
    int i = 0;

    bool first_nz_in_row = true;

    for (int j = 0; j < std_matrix->count_col; j++)
    {
        if (first_nz_in_row)
        {
            if ((sparse_matrix->IA.next_elem = create_linked_list(ind_data)) == NULL)
            {
                printf("Ошибка выделения памяти!\n");
                return ERR_ALLOC_MEMORY;
            }
            first_nz_in_row = false;
        }

        if (std_matrix->matrix[i][j] != 0)
        {
            sparse_matrix->A[ind_data] = std_matrix->matrix[i][j];
            sparse_matrix->JA[ind_data] = j;
            ind_data++;
        }
    }

    for (i = 1; i < std_matrix->count_row; i++)
    {
        first_nz_in_row = true;

        for (int j = 0; j < std_matrix->count_col; j++)
        {
            if (first_nz_in_row)
            {
                add_element_end(ind_data, sparse_matrix->IA.next_elem);
                first_nz_in_row = false;
            }

            if (std_matrix->matrix[i][j] != 0)
            {
                sparse_matrix->A[ind_data] = std_matrix->matrix[i][j];
                sparse_matrix->JA[ind_data] = j;
                ind_data++;
            }
        }
    }

    add_element_end(count_no_zero, sparse_matrix->IA.next_elem);
    sparse_matrix->count_no_zero = count_no_zero;

    return EXIT_SUCCESS;
}
