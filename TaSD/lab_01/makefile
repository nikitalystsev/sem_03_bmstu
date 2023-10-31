$(shell mkdir -p out)

CC := gcc

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -g3

PREF_SRC := ./src/
PREF_INC := ./inc/
PREF_OUT := ./out/

SRC := $(wildcard $(PREF_SRC)*.c)
OUT_OBJ := $(patsubst $(PREF_SRC)%.c, $(PREF_OUT)%.o, $(SRC))

app.exe : $(OUT_OBJ)
	$(CC) $(OUT_OBJ) -o app.exe 

$(PREF_OUT)%.o : $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean

clean : 
	rm -Rf $(PREF_OUT) ./*.exe 
