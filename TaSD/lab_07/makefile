$(shell mkdir -p out)

CC := gcc

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra \
	-Wfloat-equal -Wfloat-conversion -Wvla -O1 -g3 -Iinc -lm  

VALGRIND := valgrind --track-origins=yes --leak-check=full \
	--show-leak-kinds=all -q

PREF_SRC := ./src/
PREF_INC := ./inc/
PREF_OUT := ./out/
PREF_DATA := ./data/

SRC := $(wildcard $(PREF_SRC)*.c)
OUT_OBJ := $(patsubst $(PREF_SRC)%.c, $(PREF_OUT)%.o, $(SRC))

.PHONY : run clean del_data

run : app.exe
	./app.exe 

app.exe : $(OUT_OBJ)
	$(CC) $(OUT_OBJ) -o app.exe 

$(PREF_OUT)%.o : $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c -MD $< -o $@

include $(wildcard $(PREF_OUT)*.d)

del_data :
	rm -Rf $(PREF_DATA)*
	
clean : 
	rm -Rf $(PREF_OUT) ./*.exe ./*.svg ./*.png ./*.gv ./txt
