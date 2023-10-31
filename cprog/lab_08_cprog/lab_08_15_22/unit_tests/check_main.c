#include "check_matrix.h"
#include "check_revise.h"


int main(void)
{
    int rc = 0;
    
    rc += tests_matrix();
    rc += tests_revise();
    
    return rc;
}
