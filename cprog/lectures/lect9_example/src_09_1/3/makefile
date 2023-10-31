CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic -gdwarf-2

# 3

main_3.exe: stack_3.o main_3.o
	$(CC) -o main_3.exe stack_3.o main_3.o

stack_3.o: stack_3.c stack_3.h
	$(CC) $(CFLAGS) -c stack_3.c

main_3.o: main_3.c stack_3.h
	$(CC) $(CFLAGS) -c main_3.c

clean:
	$(RM) *.o *.exe
