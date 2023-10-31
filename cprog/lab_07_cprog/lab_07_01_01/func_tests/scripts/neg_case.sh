#!/bin/bash

if [ -n "$2" ]; then
    app_args=$(cat ../data/"$2")
else
    app_args=""
fi

if [ -n "${USE_VALGRIND}" ]; then
    check_memory=0

    cd ../.. || exit
    mycommand="valgrind --log-file=./out/memory_error_report.txt --quiet ./app.exe $app_args"
    eval "$mycommand"
    code_return=$?
    echo "rc = $code_return"
    cd func_tests/scripts || exit

    if [ -s ./../../memory_error_report.txt ]; then
        check_memory=2
    fi

    if [ $code_return -ne 0 ] && [ $check_memory -eq 0 ]; then
        exit 0
    elif [ $code_return -ne 0 ] && [ $check_memory -eq 2 ]; then
        exit 2
    else
        exit 1
    fi
else
    cd ../.. || exit
    mycommand="./app.exe $app_args"
    eval "$mycommand"
    code_return=$?
    cd func_tests/scripts || exit

    if [ $code_return -ne 0 ]; then
        exit 0
    else
        exit 1
    fi
fi
