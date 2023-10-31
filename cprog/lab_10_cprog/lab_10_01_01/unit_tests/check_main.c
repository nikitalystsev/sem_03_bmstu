#include "check_my_node.h"

int main(void)
{
    int rc = 0;
    
    rc += tests_my_node();

    return rc;
}
