#include "check_create_array.h"
#include "create_array.h"

START_TEST(test1_pos_create_array)
{
    FILE *file = NULL;
    char file_name[] = TEST_PATH"test1_pos_create_array.txt";
    int rc;

    int  *ptr_start = NULL, *ptr_end = NULL;
    rc = create_array(file, file_name, &ptr_start, &ptr_end);

    ck_assert_int_eq(rc, 0);

    free(ptr_start);
}
END_TEST

START_TEST(test1_neg_create_array)
{
    FILE *file = NULL;
    char file_name[] = TEST_PATH"test1_neg_create_array.txt";
    int rc;

    int  *ptr_start = NULL, *ptr_end = NULL;
    rc = create_array(file, file_name, &ptr_start, &ptr_end);

    ck_assert_int_eq(rc, 100);

    free(ptr_start);
}
END_TEST

Suite *create_array_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("create_array");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test1_pos_create_array);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test1_neg_create_array);
    suite_add_tcase(s, tc_neg);

    return s;
}

int tests_create_array(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = create_array_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
