#include "matrix_operations.h"

void std_matrix_mult(std_matrix_t *const std_matrix1,
                     std_matrix_t *const std_matrix2,
                     std_matrix_t *const std_matrix_res)
{
    for (int i = 0; i < std_matrix1->count_row; i++)
        for (int j = 0; j < std_matrix2->count_col; j++)
        {
            std_matrix_res->matrix[i][j] = 0;
            for (int k = 0; k < std_matrix1->count_col; k++)
            {
                std_matrix_res->matrix[i][j] +=
                    std_matrix1->matrix[i][k] * std_matrix2->matrix[k][j];
            }
        }
}

int transpose_vector_col(std_matrix_t *const std_matrix,
                         std_matrix_t *const std_transpose_matrix)
{
    std_transpose_matrix->count_row = std_matrix->count_col;
    std_transpose_matrix->count_col = std_matrix->count_row;

    if (matrix_alloc(std_transpose_matrix) != 0)
    {
        printf("Ошибка выделения памяти!\n");
        return ERR_ALLOC_MATRIX;
    }

    for (int i = 0; i < std_matrix->count_col; i++)
        for (int j = 0; j < std_matrix->count_row; j++)
        {
            std_transpose_matrix->matrix[i][j] = std_matrix->matrix[j][i];
        }

    return EXIT_SUCCESS;
}

int get_data_by_pos(list_t *head, const int pos)
{
    list_t *temp_ptr = head;

    for (int i = 0; i < pos; i++)
    {
        if (temp_ptr->next_elem == NULL)
        {
            fprintf(stderr, "Ошибка индекса\n");
            return ERR_IND_ROW;
        }

        temp_ptr = temp_ptr->next_elem;
    }

    temp_ptr->next_elem = NULL;
    return temp_ptr->index_start_row;
}

list_t *get_by_pos(list_t *head, const int pos)
{
    list_t *temp_ptr = head->next_elem;

    for (int i = 0; i < pos; i++)
    {
        if (temp_ptr->next_elem == NULL)
        {
            fprintf(stderr, "Ошибка индекса\n");
            return NULL;
        }

        temp_ptr = temp_ptr->next_elem;
    }

    return temp_ptr;
}

void sparse_mult(sparse_matrix_t *const sparse_matrix1,
                 sparse_matrix_t *const sparse_vector,
                 sparse_matrix_t *const sparse_matrix_res)
{
    sparse_matrix_res->count_row = sparse_matrix1->count_row;
    sparse_matrix_res->count_col = sparse_vector->count_col;

    list_t *temp1_IA = sparse_matrix1->IA.next_elem;
    list_t *temp1_IA_next = NULL;

    list_t *temp2_IA = sparse_vector->IA.next_elem;
    list_t *temp2_IA_next = temp2_IA->next_elem;

    sparse_matrix_res->count_no_zero = 0;

    // printf("Индексы столбцов\n");
    // for (int i = 0; i < sparse_matrix1->count_no_zero; i++)
    // {
    //     printf("%d\n", sparse_matrix1->JA[i]);
    // }
    // printf("Индексы столбцов вектора\n");
    // for (int i = 0; i < sparse_matrix1->count_no_zero; i++)
    // {
    //     printf("%d\n", sparse_vector->JA[i]);
    // }

    for (int i = 0; i < sparse_matrix_res->count_row; i++)
    {
        temp1_IA_next = temp1_IA->next_elem;

        int curr_sum = 0;

        for (int k = temp1_IA->index_start_row; k < temp1_IA_next->index_start_row; k++)
            for (int l = temp2_IA->index_start_row; l < temp2_IA_next->index_start_row; l++)
            {
                if (sparse_matrix1->JA[k] == sparse_vector->JA[l])
                {
                    curr_sum += sparse_matrix1->A[k] * sparse_vector->A[l];
                    break;
                }
            }

        if (curr_sum != 0)
        {
            sparse_matrix_res->A[sparse_matrix_res->count_no_zero] = curr_sum;
            sparse_matrix_res->JA[sparse_matrix_res->count_no_zero] = 0;
            if (i > 0)
                add_element_end(sparse_matrix_res->count_no_zero, &sparse_matrix_res->IA);
            sparse_matrix_res->count_no_zero++;
        }
        else
        {
            if (i > 0)
                add_element_end(sparse_matrix_res->count_no_zero, &sparse_matrix_res->IA);
        }

        temp1_IA = temp1_IA_next;
    }
    add_element_end(sparse_matrix_res->count_no_zero, &sparse_matrix_res->IA);
}