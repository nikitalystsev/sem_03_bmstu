$(shell mkdir -p out)

CC := gcc

CFLAGS := -std=c99 -Wall  -v -Werror -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -Iinc
LINKFLAGS := -lcheck -lpthread  -lrt 
# LINKFLAGS := -L. -lcheck -lpthread -lsubunit -lrt -lm

PREF_SRC := ./src/
PREF_INC := ./inc/
PREF_OUT := ./out/
PREF_INIT_TESTS := ./unit_tests/

# получаем список си файлов в подпапке ./unit_tests/
UNIT_TESTS := $(wildcard $(PREF_INIT_TESTS)*.c)

# получаем заменой список объектных файлов для файлов из подпапки ./unit_tests/
INIT_TESTS_OBJ := $(patsubst $(PREF_INIT_TESTS)%.c, $(PREF_OUT)%.o, $(UNIT_TESTS))

# получаем список си файлов в подпапке ./src/
SRC := $(wildcard $(PREF_SRC)*.c)

# получаем заменой список объектных файлов для файлов из подпапки ./src/
APP_OBJ := $(patsubst $(PREF_SRC)%.c, $(PREF_OUT)%.o, $(SRC))

# получаем список общих объектных файлов, фильтруя файлы из подпапки ./src/
GENERAL_OBJ := $(filter-out  $(PREF_OUT)main.o, $(APP_OBJ))

all : app.exe unit_tests.exe 

app.exe : $(APP_OBJ)
	$(CC) $(APP_OBJ) -o app.exe 

# получаем объектные файлы с помощью си файлов из подпапки ./src/
$(PREF_OUT)%.o : $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c -MD $< -o $@

unit_tests.exe : $(INIT_TESTS_OBJ) $(GENERAL_OBJ)
	$(CC) $(INIT_TESTS_OBJ) $(GENERAL_OBJ) $(LINKFLAGS) -o unit_tests.exe 

# получаем объектные файлы с помощью си файлов из подпапки ./unit_tests/
$(PREF_OUT)%.o : $(PREF_INIT_TESTS)%.c 
	$(CC) $(CFLAGS) -c -MD $< -o $@ 

include $(wildcard $(PREF_OUT)*.d)

.PHONY: coverage clean unit func 

coverage : CFLAGS += --coverage -O0
coverage : $(APP_OBJ)
	$(CC) $(CFLAGS) $(APP_OBJ) -o app.exe
	cd func_tests/scripts && ./func_tests.sh
	lcov -t "app" -o app.info -c -d .
	genhtml -o ./out/report_coverage app.info
	mv ./*.info ./out/ && rm ./*.exe

unit : unit_tests.exe
	./unit_tests.exe

func : app.exe
	cd func_tests/scripts && ./func_tests.sh

clean : 
	rm -Rf $(PREF_OUT) ./*.exe 
