#!/bin/bash

./clean.sh

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion  --coverage -O0 -o app.exe main.c -lm
cd func_tests/scripts || exit
bash func_tests.sh
cd ../../
gcov -o ./*.gcno ./*.gcda main.c
