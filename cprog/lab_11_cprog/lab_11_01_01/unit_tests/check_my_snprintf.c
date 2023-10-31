#include "check_my_snprintf.h"

START_TEST(test1_c_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%c %c", 'a', 'A');
    rc2 = snprintf(s2, 100, "%c %c", 'a', 'A');

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_d_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%d %d %d %d", INT_MAX, INT_MIN, 100, 0);
    rc2 = snprintf(s2, 100, "%d %d %d %d", INT_MAX, INT_MIN, 100, 0);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test2_d_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%d %d", 0x33, -40);
    rc2 = snprintf(s2, 100, "%d %d", 0x33, -40);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_i_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%i %i %i %i", INT_MAX, INT_MIN, 100, 0);
    rc2 = snprintf(s2, 100, "%i %i %i %i", INT_MAX, INT_MIN, 100, 0);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test2_i_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%i %i", 0x33, -40);
    rc2 = snprintf(s2, 100, "%i %i", 0x33, -40);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_x_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%x %x", INT_MAX, INT_MIN);
    rc2 = snprintf(s2, 100, "%x %x", INT_MAX, INT_MIN);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test2_x_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%x %x %x", 0x33, 15, 0);
    rc2 = snprintf(s2, 100, "%x %x %x", 0x33, 15, 0);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_o_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%o %o", INT_MAX, INT_MIN);
    rc2 = snprintf(s2, 100, "%o %o", INT_MAX, INT_MIN);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test2_o_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%o %o %o", 0x33, 15, 0);
    rc2 = snprintf(s2, 100, "%o %o %o", 0x33, 15, 0);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_s_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%s %s %s %s", "\0", " ", "hello", "hi");
    rc2 = snprintf(s2, 100, "%s %s %s %s", "\0", " ", "hello", "hi");

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_hi_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%hi %hi %hi %hi", SHRT_MAX, SHRT_MIN, 100, 0);
    rc2 = snprintf(s2, 100, "%hi %hi %hi %hi", SHRT_MAX, SHRT_MIN, 100, 0);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test2_hi_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%hi %hi", 0x33, -40);
    rc2 = snprintf(s2, 100, "%hi %hi", 0x33, -40);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_li_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%li %li", LONG_MAX, LONG_MIN);
    rc2 = snprintf(s2, 100, "%li %li", LONG_MAX, LONG_MIN);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_ld_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%ld %ld", LONG_MAX, LONG_MIN);
    rc2 = snprintf(s2, 100, "%ld %ld", LONG_MAX, LONG_MIN);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_lld_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 100, "%lld %lld", LLONG_MAX, LLONG_MIN);
    rc2 = snprintf(s2, 100, "%lld %lld", LLONG_MAX, LLONG_MIN);

    int rc = 1;

    if (rc1 == rc2 && strcmp(s1, s2) == 0)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_zero_n_my_snprintf)
{
    int rc1 = 0, rc2 = 0;
    char s1[100];
    char s2[100];

    rc1 = my_snprintf(s1, 0, "%lld %s %c hello, friend", LLONG_MAX, "are you my mummy?", 'd');
    rc2 = snprintf(s2, 0, "%lld %s %c hello, friend", LLONG_MAX, "are you my mummy?", 'd');

    int rc = 1;

    if (rc1 == rc2)
        rc = 0;

    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite *my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("my_snprintf_module");
    tc = tcase_create("specifiers");

    tcase_add_test(tc, test1_c_my_snprintf);
    tcase_add_test(tc, test1_d_my_snprintf);
    tcase_add_test(tc, test2_d_my_snprintf);
    tcase_add_test(tc, test1_i_my_snprintf);
    tcase_add_test(tc, test2_i_my_snprintf);
    tcase_add_test(tc, test1_x_my_snprintf);
    tcase_add_test(tc, test2_x_my_snprintf);
    tcase_add_test(tc, test1_o_my_snprintf);
    tcase_add_test(tc, test2_o_my_snprintf);
    tcase_add_test(tc, test_s_my_snprintf);
    tcase_add_test(tc, test1_hi_my_snprintf);
    tcase_add_test(tc, test2_hi_my_snprintf);
    tcase_add_test(tc, test_li_my_snprintf);
    tcase_add_test(tc, test_ld_my_snprintf);
    tcase_add_test(tc, test_lld_my_snprintf);
    tcase_add_test(tc, test_zero_n_my_snprintf);

    suite_add_tcase(s, tc);

    return s;
}

int tests_my_snprintf(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = my_snprintf_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
