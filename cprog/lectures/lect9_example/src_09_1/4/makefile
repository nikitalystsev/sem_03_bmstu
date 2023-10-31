CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic -gdwarf-2

# 4

app_1.exe: stack_1.o main.o
	$(CC) -o app_1.exe stack_1.o main.o

app_2.exe: stack_2.o main.o
	$(CC) -o app_2.exe stack_2.o main.o

main.o: main.c stack.h
	$(CC) $(CFLAGS) -c main.c

stack_1.o: stack_1.c stack.h
	$(CC) $(CFLAGS) -c stack_1.c

stack_2.o: stack_1.c stack.h
	$(CC) $(CFLAGS) -c stack_2.c

clean:
	$(RM) *.o *.exe