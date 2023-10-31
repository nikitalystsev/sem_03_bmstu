#include "../inc/defines.h"
#include "../inc/print.h"
#include "../inc/get_info.h"
#include "../inc/normalization.h"
#include "../inc/check.h"
#include "../inc/division.h"

int main(void)
{
    char number1[MAX_LEN_NUMBER];
    real_number_t float1;
    char number2[MAX_LEN_NUMBER];
    real_number_t float2;
    int len_number;
    int rc;

    rules();

    input_float(number1, 1);

    len_number = strlen(number1);

    if ((rc = check_real_number(number1, len_number)) != 0)
        return rc;
    
    get_info_about_number(number1, len_number, &float1);

    input_float(number2, 2);

    len_number = strlen(number2);

    if ((rc = check_real_number(number2, len_number)) != 0)
        return rc;

    get_info_about_number(number2, len_number, &float2);

    normalization(&float1, &float2);
    
    real_number_t result = {.len_mantissa = 0};

    if ((rc = division(&float1, &float2, &result)) != 0)
        return rc;

    print_result(&result);

    return EXIT_SUCCESS;
}
