# Слайд 7

greeting.exe : hello.o bye.o main.o
	gcc -o greeting.exe hello.o bye.o main.o

test_greeting.exe : hello.o bye.o test.o
	gcc -o test_greeting.exe hello.o bye.o test.o

hello.o : hello.c hello.h
	gcc -std=c99 -Wall -Werror -pedantic -c hello.c

bye.o : bye.c bye.h
	gcc -std=c99 -Wall -Werror -pedantic -c bye.c

main.o : main.c hello.h bye.h
	gcc -std=c99 -Wall -Werror -pedantic -c main.c

test.o : test.c hello.h bye.h
	gcc -std=c99 -Wall -Werror -pedantic -c test.c

clean :
	rm *.o *.exe
