#!/bin/bash

if [ -n "$3" ]; then
    app_args=$(cat ../data/"$3")
else
    app_args=""
fi

if [ -n "${USE_VALGRIND}" ]; then
    check_memory=0

    cd ../.. || exit
    eval "valgrind --log-file=./out/memory_error_report.txt --quiet ./app.exe $app_args"
    rc=$?
    cd func_tests/scripts || exit

    # если файл не пустой
    if [  -s ./../../memory_error_report.txt ]; then
        check_memory=2
    fi

    if [ $rc -eq 0 ]; then
    	./comparator.sh ../../out/"$2" ../data/"$2"
        if [ $? -eq 0 ] && [ $check_memory -eq 0 ]; then
            exit 0
        elif [ $? -eq 0 ] && [ $check_memory -eq 2 ]; then
            exit 2
        elif [ $? -eq 1 ] && [ $check_memory -eq 0 ]; then
    	    exit 1
        elif [ $? -eq 1 ] && [ $check_memory -eq 2 ]; then
    	    exit 3
        fi
    else
        exit 1
    fi

else
    cd ../.. || exit
    eval "./app.exe $app_args"
    rc=$?

    cd func_tests/scripts || exit
    if [ $rc -eq 0 ]; then
    	./comparator.sh ../../out/"$2" ../data/"$2"

    	if [ $? -eq 0 ]; then
            exit 0
    	else
            exit 1
    	fi
    else
    	exit 1
    fi
fi
