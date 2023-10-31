#include "check_filter.h"
#include "filter.h"

START_TEST(test1_neg_key)
{
    int *pb_src = NULL;
    int *pe_src = NULL;
    int *pb_dst = NULL, *pe_dst = NULL;


    int rc = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, 100);
}
END_TEST


START_TEST(test3_neg_key)
{
    int pb_src[5] = {1, 2, 3, 4, 5};
    int *pe_src = NULL;
    int *pb_dst = NULL, *pe_dst = NULL;

    pe_src = pb_src + 5;

    int rc = key(pe_src, pb_src, &pb_dst, &pe_dst);

    ck_assert_int_eq(rc, 100);
}
END_TEST

START_TEST(test5_neg_key)
{
    int pb_src[5] = {4, 2, 3, 1, 5};
    int *pe_src = NULL;
    int *pb_dst = NULL, *pe_dst = NULL;

    pe_src = pb_src + 5;

    int rc = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, 100);
}
END_TEST

START_TEST(test1_pos_key)
{
    int pb_src[5] = {1, 2, 3, 4, 5};
    int *pe_src = NULL;
    int *pb_dst = NULL, *pe_dst = NULL;

    pe_src = pb_src + 5;

    int rc = key(pb_src, pe_src, &pb_dst, &pe_dst);
    free(pb_dst);
    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite *filter_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("key");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test1_pos_key);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test1_neg_key);
    tcase_add_test(tc_neg, test3_neg_key);
    tcase_add_test(tc_neg, test5_neg_key);
    suite_add_tcase(s, tc_neg);

    return s;
}

int tests_filter(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = filter_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
