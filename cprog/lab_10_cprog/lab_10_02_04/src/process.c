#define _POSIX_C_SOURCE 200809L

#include "process.h"

int check_command(char *const word)
{
    if (strcmp(word, "out") != 0 &&
        strcmp(word, "mul") != 0 &&
        strcmp(word, "sqr") != 0 &&
        strcmp(word, "div") != 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int check_number_for_mult(int number1, int number2)
{
    if (number1 == 0 || number2 == 0)
    {
        return ERR_MULT;
    }

    return EXIT_SUCCESS;
}

int check_number_for_div(int number1, int number2)
{
    if (number2 == 0)
    {
        return ERR_DIV;
    }

    if (number1 < number2)
    {
        return ERR_DIV;
    }

    if (number1 % number2 != 0)
    {
        return ERR_DIV;
    }

    return EXIT_SUCCESS;
}

int read_command(char **word)
{
    size_t n = 0;
    *word = NULL;

    if (getline(word, &n, stdin) == -1)
    {
        return ERR_READ_COMMAND;
    }

    (*word)[strlen(*word) - 1] = '\0';

    if (check_command(*word) != 0)
    {
        return ERR_COMMAND;
    }

    return EXIT_SUCCESS;
}

int read_number(int *const number)
{
    if (fscanf(stdin, "%d", number) != 1)
    {
        return ERR_READ_NUMBER;
    }

    if (*number < 0)
    {
        return ERR_NUMBER;
    }

    return EXIT_SUCCESS;
}

node_t *create_list_by_prime_fact(int number)
{
    node_t *head = NULL;

    int divisor = 2;

    while (number != 1)
    {
        int power = 0;

        while (number % divisor == 0)
        {
            power++;
            number /= divisor;
        }

        if (power)
        {
            if (add_node_to_end(&head, divisor, power) != 0)
            {
                return NULL;
            }
        }

        divisor++;
    }

    return head;
}

node_t *two_numbers_mult(node_t *head_a, node_t *head_b)
{
    node_t *head_res = NULL;
    node_t *tmp_head_a = head_a, *tmp_head_b = head_b;

    while (tmp_head_a != NULL && tmp_head_b != NULL)
        if (tmp_head_a->factor == tmp_head_b->factor)
        {
            int power = tmp_head_a->power + tmp_head_b->power;

            if (add_node_to_end(&head_res, tmp_head_a->factor, power) != 0)
            {
                return NULL;
            }

            tmp_head_a = tmp_head_a->next;
            tmp_head_b = tmp_head_b->next;
        }
        else if (tmp_head_a->factor < tmp_head_b->factor)
        {
            if (add_node_to_end(&head_res, tmp_head_a->factor, tmp_head_a->power) != 0)
            {
                return NULL;
            }

            tmp_head_a = tmp_head_a->next;
        }
        else
        {
            if (add_node_to_end(&head_res, tmp_head_b->factor, tmp_head_b->power) != 0)
            {
                return NULL;
            }

            tmp_head_b = tmp_head_b->next;
        }

    node_t *tmp_head = tmp_head_a ? tmp_head_a : tmp_head_b;

    while (tmp_head)
    {
        if (add_node_to_end(&head_res, tmp_head->factor, tmp_head->power) != 0)
        {
            return NULL;
        }

        tmp_head = tmp_head->next;
    }

    return head_res;
}

node_t *square_number(node_t *head)
{
    node_t *head_res = NULL;

    node_t *tmp_head = head;

    while (tmp_head)
    {
        if (add_node_to_end(&head_res, tmp_head->factor, tmp_head->power * 2) != 0)
        {
            return NULL;
        }

        tmp_head = tmp_head->next;
    }

    return head_res;
}

node_t *division_two_numbers(node_t *head_a, node_t *head_b)
{
    node_t *head_res = NULL;
    node_t *tmp_head_a = head_a, *tmp_head_b = head_b;

    while (tmp_head_a != NULL && tmp_head_b != NULL)
        if (tmp_head_a->factor == tmp_head_b->factor)
        {
            if (tmp_head_a->power - tmp_head_b->power != 0)
            {
                int power = tmp_head_a->power - tmp_head_b->power;

                if (add_node_to_end(&head_res, tmp_head_a->factor, power) != 0)
                {
                    return NULL;
                }
            }

            tmp_head_a = tmp_head_a->next;
            tmp_head_b = tmp_head_b->next;
        }
        else if (tmp_head_a->factor < tmp_head_b->factor)
        {
            if (add_node_to_end(&head_res, tmp_head_a->factor, tmp_head_a->power) != 0)
            {
                return NULL;
            }

            tmp_head_a = tmp_head_a->next;
        }
        else
        {
            if (add_node_to_end(&head_res, tmp_head_b->factor, tmp_head_b->power) != 0)
            {
                return NULL;
            }

            tmp_head_b = tmp_head_b->next;
        }

    node_t *tmp_head = tmp_head_a ? tmp_head_a : tmp_head_b;

    while (tmp_head)
    {
        if (add_node_to_end(&head_res, tmp_head->factor, tmp_head->power) != 0)
        {
            return NULL;
        }

        tmp_head = tmp_head->next;
    }

    return head_res;
}

int do_out(int *const number, node_t **head)
{
    int rc = 0;

    if ((rc = read_number(number)) != 0)
    {
        return rc;
    }

    if ((*head = create_list_by_prime_fact(*number)) == NULL)
    {
        return ERR_ALLOC_MEM;
    }

    print_list(*head);

    return rc;
}

int do_multiplication(int *const number1, 
int *const number2, 
node_t **head1, 
node_t **head2, 
node_t **head_res)
{
    int rc = 0;

    if ((rc = read_number(number1)) != 0)
        return rc;

    if ((rc = read_number(number2)) != 0)
        return rc;

    if ((rc = check_number_for_mult(*number1, *number2)) != 0)
        return rc;

    if ((*head1 = create_list_by_prime_fact(*number1)) == NULL)
        return ERR_ALLOC_MEM;

    if ((*head2 = create_list_by_prime_fact(*number2)) == NULL)
        return ERR_ALLOC_MEM;

    if ((*head1 = reverse(*head1)) == NULL)
        return ERR_ALLOC_MEM;

    if ((*head2 = reverse(*head2)) == NULL)
        return ERR_ALLOC_MEM;

    if ((*head_res = two_numbers_mult(*head1, *head2)) == NULL)
        return ERR_ALLOC_MEM;

    return rc;
}

int do_division(int *const number1, 
int *const number2, 
node_t **head1, 
node_t **head2, 
node_t **head_res)
{
    int rc = 0;

    if ((rc = read_number(number1)) != 0)
        return rc;

    if ((rc = read_number(number2)) != 0)
        return rc;

    if ((rc = check_number_for_div(*number1, *number2)) != 0)
        return rc;

    if ((*head1 = create_list_by_prime_fact(*number1)) == NULL)
        return ERR_ALLOC_MEM;

    if ((*head2 = create_list_by_prime_fact(*number2)) == NULL)
        return ERR_ALLOC_MEM;

    if ((*head1 = reverse(*head1)) == NULL)
        return ERR_ALLOC_MEM;

    if ((*head2 = reverse(*head2)) == NULL)
        return ERR_ALLOC_MEM;

    if ((*head_res = division_two_numbers(*head1, *head2)) == NULL)
        return ERR_ALLOC_MEM;

    return rc;
}

int do_square(int *const number, 
node_t **head1, 
node_t **head_res)
{
    int rc = 0;

    if ((rc = read_number(number)) != 0)
        return rc;

    if ((*head1 = create_list_by_prime_fact(*number)) == NULL)
        return ERR_ALLOC_MEM;

    if ((*head_res = square_number(*head1)) == NULL)
        return ERR_ALLOC_MEM;

    *head_res = reverse(*head_res);

    return rc;
}
