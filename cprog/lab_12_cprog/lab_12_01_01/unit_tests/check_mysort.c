#include "check_mysort.h"
#include "mysort.h"

int equal_array(int *const array1, int size1, int *const array2, int size2)
{
    if (size1 != size2)
        return ERR_EQUAL_SIZE_ARRAY;
    
    for (int i = 0; i < size1; i++)
        if (array1[i] != array2[i])
            return ERR_EQUAL_ELEM_ARRAY;
    
    return 0;
}

START_TEST(test1_mysort)
{
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    mysort(a, 10, sizeof(int), compare);

    int rc = equal_array(a, 10, b, 10);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test2_mysort)
{
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    mysort(a, 10, sizeof(int), compare);

    int rc = equal_array(a, 10, b, 10);
    ck_assert_int_eq(rc, ERR_EQUAL_ELEM_ARRAY);
}
END_TEST

START_TEST(test3_mysort)
{
    int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    mysort(a, 10, sizeof(int), compare);

    int rc = equal_array(a, 10, b, 10);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test4_mysort)
{
    int a[10] = {100, 2, 10, 7, 5, 6, 7, 8, 13, 10};
    int b[10] = {2, 5, 6, 7, 7, 8, 10, 10, 13, 100};

    mysort(a, 10, sizeof(int), compare);

    int rc = equal_array(a, 10, b, 10);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test5_mysort)
{
    int a[5] = {1, 1, 1, 1, 1};
    int b[5] = {1, 1, 1, 1, 1};

    mysort(a, 5, sizeof(int), compare);

    int rc = equal_array(a, 5, b, 5);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test6_mysort)
{
    int a[1] = {5};
    int b[1] = {5};

    mysort(a, 1, sizeof(int), compare);

    int rc = equal_array(a, 1, b, 1);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_compare)
{
    int a = 5, b = 5;

    int rc = compare(&a, &b);
    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite *mysort_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("mysort");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test1_mysort);
    tcase_add_test(tc_pos, test2_mysort);
    tcase_add_test(tc_pos, test3_mysort);
    tcase_add_test(tc_pos, test4_mysort);
    tcase_add_test(tc_pos, test5_mysort);
    tcase_add_test(tc_pos, test6_mysort);
    tcase_add_test(tc_pos, test1_compare);
    suite_add_tcase(s, tc_pos);

    return s;
}

int tests_mysort(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = mysort_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
