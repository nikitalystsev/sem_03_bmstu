#ifndef __READ_H__
#define __READ_H__

#include "defines.h"
#include "check_string.h"

int read_str(FILE *const file, char *const string);
int read_number(FILE *const file, int *const number);

#endif
