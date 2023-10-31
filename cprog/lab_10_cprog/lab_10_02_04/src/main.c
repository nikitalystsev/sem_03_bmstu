#include "defines.h"
#include "node.h"
#include "process.h"

int main(void)
{
    node_t *head1 = NULL, *head2 = NULL, *head_res = NULL;
    char *word = NULL;

    int number1, number2;

    int rc = 0;

    if ((rc = read_command(&word)) != 0)
        goto free_all;

    if (strcmp(word, "out") == 0)
    {
        if ((rc = do_out(&number1, &head_res)) != 0)
            goto free_all;
    }
    else if (strcmp(word, "mul") == 0)
    {
        if ((rc = do_multiplication(&number1, &number2,
        &head1, &head2, &head_res)) != 0)
            goto free_all;

        print_list(head_res);
    }
    else if (strcmp(word, "div") == 0)
    {
        if ((rc = do_division(&number1, &number2,
        &head1, &head2, &head_res)) != 0)
            goto free_all;

        print_list(head_res);
    }
    else
    {
        if ((rc = do_square(&number1, &head1, &head_res)) != 0)
            goto free_all;

        print_list(head_res);
    }
    goto free_all;

    free_all:
    {
        free_list(head1);
        free_list(head2);
        free_list(head_res);
        free(word);
    }

    return rc;
}
