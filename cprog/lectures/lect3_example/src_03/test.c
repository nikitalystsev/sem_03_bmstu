#include <stdio.h>
#include "hello.h"
#include "bye.h"

int main(void)
{
	hello();
	printf("If you see hello message, everything is all right.\n");

	goodbye();
	printf("If you see buy message, everything is all right.\n");

	return 0;
}
