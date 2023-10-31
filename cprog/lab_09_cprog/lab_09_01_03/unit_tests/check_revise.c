#include "check_revise.h"
#include "revise.h"

START_TEST(test1_pos_check_param)
{
    const char *arr[3] = {"app.exe", "file", "3.4"};
    int argc = 3;
    double price;

    int rc = get_price(argc, arr, &price);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_neg_check_param)
{
    const char *arr[3] = {"app.exe", "file", "bb"};
    int argc = 2;
    double price;

    int rc = get_price(argc, arr, &price);

    ck_assert_int_eq(rc, 107);
}
END_TEST

Suite *check_param_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;
    s = suite_create("check_param");

    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");
    
    tcase_add_test(tc_pos, test1_pos_check_param);
    tcase_add_test(tc_neg, test1_neg_check_param);
    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);
    
    return s;
}

int test_check_param(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = check_param_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
