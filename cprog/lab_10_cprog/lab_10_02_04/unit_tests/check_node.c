#include "check_node.h"

bool equal_list(node_t *head1, node_t *head2)
{
    int c = get_count_node(head1);
    int c1 = get_count_node(head2);

    if (c != c1)
    {
        return false;
    }

    node_t *tmp_head1 = head1, *tmp_head2 = head2;

    for (int i = 0; i < c; i++)
    {
        if (head1->factor != head2->factor ||
            head1->power != head2->power)
            return false;

        tmp_head1 = tmp_head1->next;
        tmp_head2 = tmp_head2->next;
    }

    return true;
}

START_TEST(test1_pos_get_count_node)
{
    node_t *head = NULL;

    for (int i = 0; i < 5; i++)
    {
        node_t *node = create_node(5, 5);
        head = push_back(head, node);
    }

    int c = get_count_node(head);

    free_list(head);

    ck_assert_int_eq(c, 5);
}
END_TEST

Suite *node_suite(void)
{
    Suite *s;
    // TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("node_module");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test1_pos_get_count_node);
    suite_add_tcase(s, tc_pos);

    // tc_neg = tcase_create("negatives");
    // tcase_add_test(tc_neg, test1_neg_check_matrix_for_inverse);
    // suite_add_tcase(s, tc_neg);

    return s;
}

int tests_node(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = node_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
