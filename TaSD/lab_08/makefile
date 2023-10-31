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

run : app.exe
	$(VALGRIND) ./app.exe 

app.exe : $(OUT_OBJ)
	$(CC) $(OUT_OBJ) -o app.exe 

$(PREF_OUT)%.o : $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c -MD $< -o $@

include $(wildcard $(PREF_OUT)*.d)

.PHONY : clean del_data

del_data : 
	rm -Rf $(PREF_DATA)*.png $(PREF_DATA)*.gv
	
clean : 
	rm -Rf $(PREF_OUT) ./*.exe
