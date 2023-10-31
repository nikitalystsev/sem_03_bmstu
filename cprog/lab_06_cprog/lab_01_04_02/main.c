#include <stdio.h>
#define TO_HOUR 3600
#define TO_MIN 60
#define SUCCESS 0

int main(void)
{
    int time_sec, time_min, time_hour;

    puts("Enter time in seconds:");
    scanf("%d", &time_sec);
    
    time_hour = (time_sec / TO_HOUR);
    time_sec %= TO_HOUR;
    time_min = (time_sec / TO_MIN);
    time_sec %= TO_MIN;
    
    printf("%d\n", time_hour);
    printf("%d\n", time_min);
    printf("%d\n", time_sec);
    return SUCCESS;
}
