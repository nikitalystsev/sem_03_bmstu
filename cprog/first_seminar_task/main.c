#include <stdio.h>

int calculate(int max_number)
{
    long int c1 = 0;
    int find_number = 0;
    for (int i = 1; i < max_number; i++)
    {
        int number = i;
        long int c = 0;
        while (number != 1)
        {
            if (number % 2 == 0)
            {
                number = number / 2;
                c++;
            }
            else
            {
                number = number * 3 + 1;
                c++;
            }
        }
        if (c > c1)
        {
            c1 = c; 
            find_number = i;  
        }
    }
    return find_number;
}

int main(void)
{
    int number = calculate(100000);
    printf("%d\n", number);

    return 0;
    
}