$(shell mkdir -p out lib)

CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra \
	-Wfloat-equal -Wfloat-conversion -Iinc -Wvla

LINKFLAGS := -lcheck -lpthread -lrt -lsubunit -lm

PREF_SRC := ./src/
PREF_INC := ./inc/
PREF_OUT := ./out/
PREF_LIB := ./lib/
PREF_INIT_TESTS := ./unit_tests/

# получаем список си файлов в подпапке ./unit_tests/
UNIT_TESTS := $(wildcard $(PREF_INIT_TESTS)*.c)

# получаем заменой список объектных файлов для файлов из подпапки ./unit_tests/
INIT_TESTS_OBJ := $(patsubst $(PREF_INIT_TESTS)%.c, $(PREF_OUT)%.o, $(UNIT_TESTS))

# получаем список си файлов в подпапке ./src/
SRC := $(wildcard $(PREF_SRC)*.c)

# получаем заменой список объектных файлов для файлов из подпапки ./src/
SRC_OBJ := $(patsubst $(PREF_SRC)%.c, $(PREF_OUT)%.o, $(SRC))

# получаем список общих объектных файлов, фильтруя файл main из подпапки ./src/
GENERAL_OBJ := $(filter-out  $(PREF_OUT)main.o, $(SRC_OBJ))

.PHONY: debug release coverage clean unit func stat_link_app  \
	din_link_app din_load_app static_link_init_tests din_load_init_tests \
	din_link_init_tests

stat_link_app : $(PREF_OUT)main.o $(PREF_LIB)libapp.a
	$(CC) $(CFLAGS) $^ -o app.exe

$(PREF_LIB)libapp.a : $(GENERAL_OBJ)
	ar rc $@ $^
	ranlib $@


din_load_app : $(PREF_OUT)main.o $(PREF_LIB)libapp.so
	$(CC) $(CFLAGS) $^ -o app.exe

din_link_app : $(PREF_OUT)main.o $(PREF_LIB)libapp.so
	$(CC) $(CFLAGS) $< -L$(PREF_LIB) -lapp -Wl,-rpath,$(PREF_LIB) -o app.exe

$(PREF_LIB)libapp.so : $(GENERAL_OBJ)
	$(CC) -shared $^ -o $@


stat_link_unit_tests : $(PREF_OUT)check_main.o $(PREF_LIB)libunit_tests.a
	$(CC) $(CFLAGS) $^ $(LINKFLAGS) -o unit_tests.exe

$(PREF_LIB)libunit_tests.a : $(INIT_TESTS_OBJ) $(GENERAL_OBJ) 
	ar rc $@ $^
	ranlib $@


din_load_unit_tests : $(PREF_OUT)check_main.o $(PREF_LIB)libunit_tests.so
	$(CC) $(CFLAGS) $^ $(LINKFLAGS) -o unit_tests.exe

din_link_unit_tests : $(PREF_OUT)check_main.o $(PREF_LIB)libunit_tests.so
	$(CC) $< -L$(PREF_LIB) -lunit_tests -Wl,-rpath,$(PREF_LIB) $(LINKFLAGS) \
	 -o unit_tests.exe

$(PREF_LIB)libunit_tests.so : $(INIT_TESTS_OBJ) $(GENERAL_OBJ) 
	$(CC) -shared $^ -o $@


# получаем объектные файлы с помощью си файлов из подпапки ./src/
$(PREF_OUT)%.o : $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c -fPIC -MD $< -o $@

# получаем объектные файлы с помощью си файлов из подпапки ./unit_tests/
$(PREF_OUT)%.o : $(PREF_INIT_TESTS)%.c 
	$(CC) $(LINKFLAGS) $(CFLAGS) -c -MD $< -o $@ 

include $(wildcard $(PREF_OUT)*.d)

debug : CFLAGS += -g3
debug : app.exe

release : CFLAGS += -g0
release : app.exe

coverage : CFLAGS += --coverage -O0
coverage : $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) -o app.exe
	cd func_tests/scripts && ./func_tests.sh
	lcov -t "app" -o app.info -c -d .
	genhtml -o ./out/report_coverage app.info
	mv ./*.info ./out/ && rm ./*.exe

unit : unit_tests.exe
	./unit_tests.exe

func : app.exe
	cd func_tests/scripts && ./func_tests.sh

clean : 
	rm -Rf $(PREF_OUT) $(PREF_LIB) ./*.exe 
