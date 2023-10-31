#include <stdio.h>
#include <stdint.h>
#define SUCCESS 0
#define ERROR 1
#define BIT_SIZE 32
#define CORRECT_INPUT 2
#define NEGATIVE_NUMBER 3

void print_bin_number(uint32_t dec_number)
{
    printf("Result: ");
    for (int i = BIT_SIZE - 1; i >= 0; i--)
        printf("%d", (dec_number >> i) & 1);
}

void bitwise_left_shift(uint32_t dec_number, int n)
{
    if (n > BIT_SIZE)
        n %= BIT_SIZE;
  
    dec_number = (dec_number << n) | (dec_number >> (BIT_SIZE - n)); 
    print_bin_number(dec_number);
}

int main(void)
{
    uint32_t a;
    int n;
    int rc;

    puts("Enter numbers:");
    rc = scanf("%u", &a);
    rc += scanf("%d", &n);

    if (rc != CORRECT_INPUT)
    {
        printf("Error: wrong input");
        return ERROR;
    }
    else if (n < 0)
    {
        printf("Error: shift must be a positive number");
        return NEGATIVE_NUMBER;
    }
   
    bitwise_left_shift(a, n);
    return SUCCESS;
}
