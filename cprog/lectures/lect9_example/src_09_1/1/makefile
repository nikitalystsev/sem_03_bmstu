CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic -gdwarf-2

# 1

main_1.exe: stack_1.o main_1.o
	$(CC) -o main_1.exe stack_1.o main_1.o

stack_1.o: stack_1.c stack_1.h
	$(CC) $(CFLAGS) -c stack_1.c

main_1.o: main_1.c stack_1.h
	$(CC) $(CFLAGS) -c main_1.c

clean:
	$(RM) *.o *.exe