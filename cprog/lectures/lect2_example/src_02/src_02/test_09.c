/*
Слайд 9
*/

// По мотивам
// https://stackoverflow.com/questions/4217037/catch-ctrl-c-in-c

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler(int sig)
{
    printf("Thats all...\n");

    exit(0);
}

int main(void)
{
    signal(SIGINT, sigint_handler);

    while (1)
    {
         printf(".");   
    }
    
    return 0;
}
