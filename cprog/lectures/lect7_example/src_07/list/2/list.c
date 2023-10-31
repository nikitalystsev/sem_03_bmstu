#include <string.h>
#include "list.h"


person_t* list_add_front(person_t *head, person_t *pers)
{
    pers->next = head;
    return pers;
}


void list_add_front_usual(person_t **head, person_t *pers)
{
    pers->next = *head;
    *head = pers;
}


person_t* list_add_end(person_t *head, person_t *pers)
{
    person_t *cur = head;

    if (!head)
        return pers;

    for ( ; cur->next; cur = cur->next)
        ;

    cur->next = pers;

    return head;
}


person_t* list_lookup(person_t *head, const char *name)
{
    for ( ; head; head = head->next)
        if (strcmp(head->name, name) == 0)
            return head;

    return NULL;
}


void list_apply(person_t *head, ptr_action_t f, void *arg)
{
    for ( ; head; head = head->next)
        f(head, arg);
}


void list_free_all(person_t *head)
{
    person_t *next;

    for ( ; head; head = next)
    {
        next = head->next;
        person_free(head);
    }
}


person_t* list_del_by_name(person_t *head, const char *name)
{
    person_t *cur, *prev = NULL;

    for (cur = head; cur; cur = cur->next)
    {
        if (strcmp(cur->name, name) == 0)
        {
            if (prev)
                prev->next = cur->next;
            else
                head = cur->next;

            person_free(cur);

            return head;
        }

        prev = cur;
    }

    return head;
}


person_t* list_del_by_name_ex(person_t *head, const char *name)
{
    person_t *cur = head, *prev = NULL, *del;

    while (cur)
    {
        if (strcmp(cur->name, name) == 0)
        {
            del = cur;

            if (prev)
                prev->next = cur = cur->next;
            else
                head = cur = cur->next;

            person_free(del);
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }

    return head;
}
