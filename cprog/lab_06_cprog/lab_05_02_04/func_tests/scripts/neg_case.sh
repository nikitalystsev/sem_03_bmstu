#!/bin/bash

if [ -n "$2" ]; then
    app_args=$(cat ../data/"$2")
else
    app_args=""
fi

if [ -s "$1" ] && [ "$app_args" == "" ]; then
    input_file=$1
else
    input_file=""
fi


if [ -n "${USE_VALGRIND}" ]; then
    check_memory=0
    mycommand="valgrind --log-file=./../../memory_error_report.txt --quiet ./../../app.exe $app_args $input_file > ./../../out_neg.txt"
    eval "$mycommand"
    code_return=$?
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
    mycommand="./../../app.exe $app_args $input_file > ./../../out_neg.txt"
    eval "$mycommand"
    code_return=$?
    if [ $code_return -ne 0 ]; then
        exit 0
    else
        exit 1
    fi
fi

