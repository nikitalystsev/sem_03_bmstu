#!/bin/bash

gcc -std=c99 -Wall -Werror -c avg.c
gcc -std=c99 -Wall -Werror -c check_unit_tests.c
gcc -o app.exe avg.o check_unit_tests.o -lcheck -lpthread -lsubunit -lrt -lm
