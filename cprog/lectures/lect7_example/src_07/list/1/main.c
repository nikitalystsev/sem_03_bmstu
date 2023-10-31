#include <assert.h>
#include <stdio.h>
#include "list.h"


#define SEARCH_NAME "Sidorov"


int main(void)
{
    struct person_t *head = NULL;
    struct person_t *node;
    int n = 0;

    // NB: "Ivanov" - строковый литерал, т.е. строковая константа
    node = person_create("Ivanov", 1995);
    assert(node);
    head = list_add_front(head, node);

    node = person_create(SEARCH_NAME, 1994);
    assert(node);
    head = list_add_front(head, node);

    node = person_create("Petrov", 1995);
    assert(node);
    head = list_add_front(head, node);

    list_apply(head, person_print, "%s %d\n");

    printf("\n");

    node = person_create("Vasechkin", 1996);
    assert(node);
    head = list_add_end(head, node);

    list_apply(head, person_print, "%s %d\n");

    printf("\n");

    list_apply(head, person_count, &n);

    printf("List contains %d element(s)\n", n);

    node = list_lookup(head, SEARCH_NAME);

    printf("%s is in %p element\n", SEARCH_NAME, node);

    head = list_del_by_name(head, SEARCH_NAME);

    node = list_lookup(head, SEARCH_NAME);

    printf("%s is in %p element\n", SEARCH_NAME, node);

    list_free_all(head);

    return 0;
}
