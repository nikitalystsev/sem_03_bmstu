CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic -gdwarf-2

# 2

main_2.exe: stack_2.o main_2.o
	$(CC) -o main_2.exe stack_2.o main_2.o

stack_2.o: stack_2.c stack_2.h
	$(CC) $(CFLAGS) -c stack_2.c

main_2.o: main_2.c stack_2.h
	$(CC) $(CFLAGS) -c main_2.c

clean:
	$(RM) *.o *.exe