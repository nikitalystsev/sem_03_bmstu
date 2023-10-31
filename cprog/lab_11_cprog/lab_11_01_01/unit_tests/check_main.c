#include "check_my_snprintf.h"

int main(void)
{
    int rc = 0;
    
    rc += tests_my_snprintf();

    return rc;
}
