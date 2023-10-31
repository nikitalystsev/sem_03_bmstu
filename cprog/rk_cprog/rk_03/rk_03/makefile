$(shell mkdir -p out)

CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -Iinc -Wvla

PREF_SRC := ./src/
PREF_INC := ./inc/
PREF_OUT := ./out/

SRC := $(wildcard $(PREF_SRC)*.c)

SRC_OBJ := $(patsubst $(PREF_SRC)%.c, $(PREF_OUT)%.o, $(SRC))

.PHONY: build run clean 

build : app.exe 

run : app.exe
	./app.exe in.txt out.txt

app.exe : $(SRC_OBJ)
	$(CC) $(SRC_OBJ) -o app.exe 

$(PREF_OUT)%.o : $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c -MD $< -o $@

include $(wildcard $(PREF_OUT)*.d) 

clean : 
	rm -Rf $(PREF_OUT) ./*.exe ./out.txt
