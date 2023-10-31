#include "defines.h"
#include "create_array.h"
#include "filter.h"
#include "mysort.h"
#include "param_check.h"
#include "write_numbers_to_file.h"

int main(int argc, char const *argv[])
{
    FILE *file = NULL;
    int *pb_src = NULL, *pe_src = NULL;
    int *pb_dst = NULL, *pe_dst = NULL;
    int *pb_cur = NULL, *pe_cur = NULL;

    int rc = 0;
    int count_elem = 0;

    if ((rc = check_argc(argc, argv)) != 0)
        return rc;

    rc = create_array(file, argv[1], &pb_src, &pe_src);
    CHECK_RC(rc);

    if (argc == PARAM_NO_FILTER)
    {
        pb_cur = pb_src;
        pe_cur = pe_src;
    }
    else if (argc == PARAM_FILTER)
    {
        rc = key(pb_src, pe_src, &pb_dst, &pe_dst);
        CHECK_RC(rc);
        pb_cur = pb_dst;
        pe_cur = pe_dst;
    }

    count_elem = get_count_elements(pb_cur, pe_cur);

    if (count_elem == 0)         
    {                            
        FREE(pb_src, pb_dst);    
        return ERR_NO_DATA;      
    }  

    mysort(pb_cur, count_elem, sizeof(int), compare);
    
    rc = write_numbers_to_file(file, argv[2], pb_cur, pe_cur);
    CHECK_RC(rc);

    FREE(pb_src, pb_dst);

    return rc;
}
