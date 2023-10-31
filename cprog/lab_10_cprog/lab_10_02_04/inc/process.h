#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "defines.h"
#include "node.h"

int check_command(char *const word);

int read_command(char **word);

int check_number_for_mult(int number1, int number2);

int check_number_for_div(int number1, int number2);

int read_number(int *const number);

node_t *create_list_by_prime_fact(int number);

node_t *two_numbers_mult(node_t *head_a, node_t *head_b);

node_t *square_number(node_t *head);

node_t *division_two_numbers(node_t *head_a, node_t *head_b);

int do_out(int *const number, node_t **head);

int do_multiplication(int *const number1, 
int *const number2, 
node_t **head1, 
node_t **head2, 
node_t **head_res);

int do_division(int *const number1, 
int *const number2, 
node_t **head1, 
node_t **head2, 
node_t **head_res);

int do_square(int *const number, 
node_t **head1, 
node_t **head_res);

#endif
