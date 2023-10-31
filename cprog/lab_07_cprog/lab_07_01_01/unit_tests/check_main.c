#include "check_write_numbers_to_file.h"
#include "check_create_array.h"
#include "check_param_check.h"
#include "check_filter.h"
#include "check_mysort.h"

int main(void)
{
    int rc = 0;
    
    rc += tests_create_array();
    rc += tests_filter();
    rc += tests_mysort();
    rc += test_file_check();
    rc += test_write_to_file();

    return rc;
}
