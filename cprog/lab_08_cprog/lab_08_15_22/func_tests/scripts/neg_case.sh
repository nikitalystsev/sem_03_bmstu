#!/bin/bash

if [ -n "$2" ]; then
    app_args=$(cat ../data/"$2")
else
    app_args=""
fi

if [ -n "${USE_VALGRIND}" ]; then
    check_memory=1

    cd ../.. || exit
    eval "valgrind --log-file=./out/memory_error_report.txt --quiet ./app.exe $app_args"
    rc=$?
    echo "rc = $rc"
    cd func_tests/scripts || exit

    # если файл не пустой
    if [ -s ./../../memory_error_report.txt ]; then
        check_memory=2
    fi

    if [ $rc -ne 0 ] && [ $check_memory -eq 0 ]; then
        exit 0
    elif [ $rc -ne 0 ] && [ $check_memory -eq 2 ]; then
        exit 2
    elif [ $rc -eq 0 ] && [ $check_memory -eq 2 ]; then
        exit 3
    elif [ $rc -eq 0 ] && [ $check_memory -eq 0 ]; then
        exit 1
    fi
else
    cd ../.. || exit
    eval "./app.exe $app_args"
    rc=$?
    echo "rc = $rc"
    cd func_tests/scripts || exit

    if [ $rc -ne 0 ]; then
        exit 0
    else
        exit 1
    fi
fi
