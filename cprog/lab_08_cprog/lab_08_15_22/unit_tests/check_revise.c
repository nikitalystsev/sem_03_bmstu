#include "check_revise.h"

START_TEST(test1_pos_check_matrix_for_inverse)
{
    const char file_name[] = TEST_PATH"test1_pos_check_matrix_for_inverse.txt";
    int rc;

    matrix_t matrix;
    
    read_matrix_from_file(&matrix, file_name);

    rc = check_matrix_for_inverse(&matrix);

    matrix_free(matrix.matrix, matrix.rows);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_neg_check_matrix_for_inverse)
{
    const char file_name[] = TEST_PATH"test1_neg_check_matrix_for_inverse.txt";
    int rc;

    matrix_t matrix;
    
    read_matrix_from_file(&matrix, file_name);

    rc = check_matrix_for_inverse(&matrix);

    matrix_free(matrix.matrix, matrix.rows);

    ck_assert_int_eq(rc, 109);
}
END_TEST

START_TEST(test1_pos_check_matrix_for_add)
{
    const char file_name1[] = TEST_PATH"test1_pos_check_matrix_for_add_mtr1.txt";
    const char file_name2[] = TEST_PATH"test1_pos_check_matrix_for_add_mtr2.txt";
    int rc;

    matrix_t matrix1, matrix2;
    
    read_matrix_from_file(&matrix1, file_name1);
    read_matrix_from_file(&matrix2, file_name2);

    rc = check_matrix_for_add(&matrix1, &matrix2);

    matrix_free(matrix1.matrix, matrix1.rows);
    matrix_free(matrix2.matrix, matrix2.rows);

    ck_assert_int_eq(rc, 0);
}

START_TEST(test1_pos_check_matrix_for_mult)
{
    const char file_name1[] = TEST_PATH"test1_pos_check_matrix_for_mult_mtr1.txt";
    const char file_name2[] = TEST_PATH"test1_pos_check_matrix_for_mult_mtr2.txt";
    int rc;

    matrix_t matrix1, matrix2;
    
    read_matrix_from_file(&matrix1, file_name1);
    read_matrix_from_file(&matrix2, file_name2);

    rc = check_matrix_for_mult(&matrix1, &matrix2);

    matrix_free(matrix1.matrix, matrix1.rows);
    matrix_free(matrix2.matrix, matrix2.rows);

    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite *revise_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("revise_module");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test1_pos_check_matrix_for_inverse);
    tcase_add_test(tc_pos, test1_pos_check_matrix_for_add);
    tcase_add_test(tc_pos, test1_pos_check_matrix_for_mult);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test1_neg_check_matrix_for_inverse);
    suite_add_tcase(s, tc_neg);

    return s;
}

int tests_revise(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = revise_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
