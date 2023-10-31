#!/bin/bash

./clean.sh

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion  --coverage -O0 -o app.exe ./*.c -lm
cd func_tests/scripts || exit
bash func_tests.sh
cd ../../
lcov -t "app" -o app.info -c -d .
genhtml -o report_coverage app.info
