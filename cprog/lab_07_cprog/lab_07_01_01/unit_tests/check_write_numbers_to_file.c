#include "check_write_numbers_to_file.h"
#include "write_numbers_to_file.h"

START_TEST(write_valid_array_to_file)
{
    FILE *file = NULL;
    char file_name[] = TEST_PATH"test1_pos_writenumbers_to_file.txt";
    int array[5] = {1, 2, 3, 4, 5};
    int rc;

    int  *ptr_end = array + 5;
    rc = write_numbers_to_file(file, file_name, array, ptr_end);

    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite *write_numbers_to_file_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("write_numbers_to_file");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, write_valid_array_to_file);

    suite_add_tcase(s, tc_pos);

    return s;
}

int test_write_to_file(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = write_numbers_to_file_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
