rem gcc -std=c99 -Wall -Werror main.c libarr.a -o test.exe

gcc -std=c99 -Wall -Werror main.c -L. -larr -o test.exe