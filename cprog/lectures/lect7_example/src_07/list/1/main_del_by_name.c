#include <assert.h>
#include <stdio.h>
#include "list.h"


#define SEARCH_NAME "Sidorov"


int main(void)
{
    struct person_t *head = NULL;
    struct person_t *node;
    int n = 0;

    node = person_create(SEARCH_NAME, 1994);
    assert(node);
    head = list_add_front(head, node);

    node = person_create("Ivanov", 1995);
    assert(node);
    head = list_add_front(head, node);

    node = person_create(SEARCH_NAME, 1994);
    assert(node);
    head = list_add_front(head, node);

    node = person_create("Petrov", 1995);
    assert(node);
    head = list_add_front(head, node);

    node = person_create(SEARCH_NAME, 1994);
    assert(node);
    head = list_add_front(head, node);

    n = 0;
    list_apply(head, person_count, &n);

    printf("List contains %d element(s)\n", n);

    list_apply(head, person_print, "%s %d\n");
    printf("\n");

    head = list_del_by_name_ex(head, SEARCH_NAME);

    n = 0;
    list_apply(head, person_count, &n);

    printf("List contains %d element(s)\n", n);

    list_apply(head, person_print, "%s %d\n");
    printf("\n");

    list_free_all(head);
    head = NULL;

    //===

    node = person_create(SEARCH_NAME, 1994);
    assert(node);
    head = list_add_front(head, node);

    node = person_create(SEARCH_NAME, 1994);
    assert(node);
    head = list_add_front(head, node);

    node = person_create(SEARCH_NAME, 1994);
    assert(node);
    head = list_add_front(head, node);

    n = 0;
    list_apply(head, person_count, &n);

    printf("List contains %d element(s)\n", n);

    list_apply(head, person_print, "%s %d\n");
    printf("\n");

    head = list_del_by_name_ex(head, SEARCH_NAME);

    n = 0;
    list_apply(head, person_count, &n);

    printf("List contains %d element(s)\n", n);

    list_apply(head, person_print, "%s %d\n");
    printf("\n");

    list_free_all(head);

    return 0;
}
