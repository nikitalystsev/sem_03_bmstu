#include "check_matrix.h"

int equal_matrix(double **matrix1, double **matrix2, const int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (fabs(matrix1[i][j] - matrix2[i][j]) > EPS)
                return ERR_EQUAL_MATRIX;
        }

    return EXIT_SUCCESS;
}

START_TEST(test1_pos_get_matrix_size)
{
    const char file_name[] = TEST_PATH "test1_pos_get_matrix_size.txt";
    int rc;
    int n, m;
    FILE *file;

    file = fopen(file_name, "r");

    rc = get_matrix_size(&n, &m, file);

    fclose(file);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_pos_read_matrix_from_file)
{
    const char file_name[] = TEST_PATH "test1_pos_read_matrix_from_file.txt";
    int rc;

    matrix_t matrix;

    rc = read_matrix_from_file(&matrix, file_name);

    matrix_free(matrix.matrix, matrix.rows);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_pos_gauss_det)
{
    const char file_name[] = TEST_PATH "test1_pos_gauss_det.txt";

    matrix_t matrix;

    read_matrix_from_file(&matrix, file_name);

    double det;
    gauss_det(&matrix, &det);

    matrix_free(matrix.matrix, matrix.rows);

    ck_assert_double_eq(det, 56.0);
}
END_TEST

START_TEST(test1_pos_inversion_matrix)
{
    const char file_name[] = TEST_PATH "test1_pos_inversion_matrix.txt";

    matrix_t matrix;
    double mtr[3][3] = {{1, 1, 1}, {1, 2, 3}, {1, 3, 6}};
    double *p_mtr[3] = {mtr[0], mtr[1], mtr[2]};

    read_matrix_from_file(&matrix, file_name);

    inversion_matrix(&matrix);

    int rc = equal_matrix(p_mtr, matrix.matrix, matrix.rows);

    matrix_free(matrix.matrix, matrix.rows);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_pos_matrix_add)
{
    const char file_name1[] = TEST_PATH "test1_pos_matrix_add_mtr1.txt";
    const char file_name2[] = TEST_PATH "test1_pos_matrix_add_mtr2.txt";

    matrix_t matrix1, matrix2, matrix_res;

    double mtr[2][2] = {{7, 10}, {10, 5}};
    double *p_mtr[2] = {mtr[0], mtr[1]};

    read_matrix_from_file(&matrix1, file_name1);
    read_matrix_from_file(&matrix2, file_name2);

    matrix_res.rows = matrix1.rows;
    matrix_res.cols = matrix2.cols;

    matrix_alloc(&matrix_res);

    matrix_add(&matrix1, &matrix2, &matrix_res);

    int rc = equal_matrix(p_mtr, matrix_res.matrix, matrix_res.rows);

    matrix_free(matrix1.matrix, matrix1.rows);
    matrix_free(matrix2.matrix, matrix2.rows);
    matrix_free(matrix_res.matrix, matrix_res.rows);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_pos_matrix_mult)
{
    const char file_name1[] = TEST_PATH "test1_pos_matrix_mult_mtr1.txt";
    const char file_name2[] = TEST_PATH "test1_pos_matrix_mult_mtr2.txt";

    matrix_t matrix1, matrix2, matrix_res;

    double mtr[3][3] = {{31, 28, 25}, {44, 41, 38}, {57, 54, 51}};
    double *p_mtr[3] = {mtr[0], mtr[1], mtr[2]};

    read_matrix_from_file(&matrix1, file_name1);
    read_matrix_from_file(&matrix2, file_name2);

    matrix_res.rows = matrix1.rows;
    matrix_res.cols = matrix2.cols;

    matrix_alloc(&matrix_res);

    matrix_mult(&matrix1, &matrix2, &matrix_res);

    int rc = equal_matrix(p_mtr, matrix_res.matrix, matrix_res.rows);

    matrix_free(matrix1.matrix, matrix1.rows);
    matrix_free(matrix2.matrix, matrix2.rows);
    matrix_free(matrix_res.matrix, matrix_res.rows);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_pos_get_count_no_zero)
{
    const char file_name[] = TEST_PATH "test1_pos_get_count_no_zero.txt";

    matrix_t matrix;

    read_matrix_from_file(&matrix, file_name);

    int count = get_count_no_zero(&matrix);

    matrix_free(matrix.matrix, matrix.rows);

    ck_assert_int_eq(count, 2);
}
END_TEST

Suite *matrix_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("matrix_module");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test1_pos_get_matrix_size);
    tcase_add_test(tc_pos, test1_pos_read_matrix_from_file);
    tcase_add_test(tc_pos, test1_pos_gauss_det);
    tcase_add_test(tc_pos, test1_pos_inversion_matrix);
    tcase_add_test(tc_pos, test1_pos_matrix_add);
    tcase_add_test(tc_pos, test1_pos_matrix_mult);
    tcase_add_test(tc_pos, test1_pos_get_count_no_zero);
    suite_add_tcase(s, tc_pos);

    return s;
}

int tests_matrix(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = matrix_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
