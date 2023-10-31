$(shell mkdir -p out lib)

CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra \
	-Wfloat-equal -Wfloat-conversion -Iinc -Wvla

PREF_SRC := ./src/
PREF_INC := ./inc/
PREF_OUT := ./out/
PREF_LIB := ./lib/

# получаем список си файлов в подпапке ./src/
SRC := $(wildcard $(PREF_SRC)*.c)

# получаем заменой список объектных файлов для файлов из подпапки ./src/
SRC_OBJ := $(patsubst $(PREF_SRC)%.c, $(PREF_OUT)%.o, $(SRC))

# получаем список общих объектных файлов, фильтруя файл main из подпапки ./src/
GENERAL_OBJ := $(filter-out  $(PREF_OUT)main.o, $(SRC_OBJ))

.PHONY: all lib clean

all : lib
	cd $(PREF_SRC) && python interface.py

lib : $(PREF_LIB)libarr.dll

$(PREF_LIB)libarr.dll : $(GENERAL_OBJ)
	$(CC) -shared $^ -o $@

# получаем объектные файлы с помощью си файлов из подпапки ./src/
$(PREF_OUT)%.o : $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c -fPIC -MD $< -o $@

include $(wildcard $(PREF_OUT)*.d)

clean : 
	rm -Rf $(PREF_OUT) $(PREF_LIB) ./*.exe 
