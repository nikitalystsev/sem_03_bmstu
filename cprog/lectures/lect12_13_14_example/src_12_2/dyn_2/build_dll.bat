gcc -std=c99 -Wall -Werror -D ARR_EXPORTS -c arr_lib.c

gcc -shared arr_lib.o -Wl,--subsystem,windows -o arr.dll
