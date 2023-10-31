CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic -gdwarf-2

# 0

main_0.exe: stack_0.o main_0.o
	$(CC) -o main_0.exe stack_0.o main_0.o

stack_0.o: stack_0.c stack_0.h
	$(CC) $(CFLAGS) -c stack_0.c

main_0.o: main_0.c stack_0.h
	$(CC) $(CFLAGS) -c main_0.c

clean:
	$(RM) *.o *.exe