#include "check_param_check.h"
#include "param_check.h"

START_TEST(test1_pos_argc_check)
{
    int argc = 3;
    const char *argv[] = {"apricot", "apple"};
    int rc = check_argc(argc, argv);
    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite *file_check_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("param_check");
    
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test1_pos_argc_check);
    suite_add_tcase(s, tc_pos);

    return s;
}

int test_file_check(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = file_check_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
