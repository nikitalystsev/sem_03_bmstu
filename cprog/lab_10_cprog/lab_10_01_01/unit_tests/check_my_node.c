#include "check_my_node.h"

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
        if (((data_t *)tmp_head1->data)->number !=
            ((data_t *)tmp_head2->data)->number)
            return false;
        
        tmp_head1 = tmp_head1->next;
        tmp_head2 = tmp_head2->next;
    }

    return true;
}

START_TEST(test1_pos_get_count_node)
{
    node_t *head = NULL;

    data_t *arr_data = NULL;

    arr_data = malloc(5 * sizeof(data_t));
    for (int i = 0; i < 5; i++)
    {
        arr_data[i].number = i;
    }

    for (int i = 0; i < 5; i++)
    {
        node_t *node = create_node(&arr_data[i]);
        head = push_back(head, node);
    }

    int c = get_count_node(head);

    free_list(head);
    free(arr_data);

    ck_assert_int_eq(c, 5);
}
END_TEST

START_TEST(test1_pos_sorted_merge)
{
    node_t *head = NULL;
    node_t *head2 = NULL;
    node_t *head3 = NULL;
    node_t *head4 = NULL;
    data_t *arr_data = NULL;

    arr_data = malloc(5 * sizeof(data_t));
    for (int i = 0; i < 5; i++)
    {
        arr_data[i].number = i;
    }

    for (int i = 0; i < 5; i++)
    {
        node_t *node = create_node(&arr_data[i]);
        head = push_back(head, node);
    }

    for (int i = 0; i < 5; i++)
    {
        node_t *node = create_node(&arr_data[i]);
        head2 = push_back(head2, node);
    }

    for (int i = 0; i < 5; i++)
    {
        node_t *node = create_node(&arr_data[i]);
        node_t *node2 = create_node(&arr_data[i]);
        head3 = push_back(head3, node);
        head3 = push_back(head3, node2);
    }

    head4 = sorted_merge(&head, &head2, compare);
    
    int rc = 0;
    if (!equal_list(head4, head3))
        rc = 1;

    free_list(head);
    free_list(head2);
    free_list(head3);
    free_list(head4);
    free(arr_data);

    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test1_pos_sort)
{
    node_t *head = NULL;
    node_t *head2 = NULL;

    data_t *arr_data = NULL;

    arr_data = malloc(5 * sizeof(data_t));
    for (int i = 0; i < 5; i++)
    {
        arr_data[i].number = i;
    }

    for (int i = 4; i >= 0; i--)
    {
        node_t *node = create_node(&arr_data[i]);
        head = push_back(head, node);
    }

    for (int i = 0; i < 5; i++)
    {
        node_t *node = create_node(&arr_data[i]);
        head2 = push_back(head2, node);
    }

    head = sort(head, compare);  

    int rc = 0;
    if (!equal_list(head, head2))
        rc = 1;

    free_list(head);
    free_list(head2);
    free(arr_data);

    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite *my_node_suite(void)
{
    Suite *s;
    // TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("my_node_module");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test1_pos_get_count_node);
    tcase_add_test(tc_pos, test1_pos_sorted_merge);
    tcase_add_test(tc_pos, test1_pos_sort);
    suite_add_tcase(s, tc_pos);

    // tc_neg = tcase_create("negatives");
    // tcase_add_test(tc_neg, test1_neg_check_matrix_for_inverse);
    // suite_add_tcase(s, tc_neg);

    return s;
}

int tests_my_node(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = my_node_suite();

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
