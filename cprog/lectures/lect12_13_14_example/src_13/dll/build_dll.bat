gcc -std=c99 -Wall -Werror -D EXAMPLE_EXPORTS -c example.c

gcc -shared example.o -Wl,--subsystem,windows -o example.dll