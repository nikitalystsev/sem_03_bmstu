#!/bin/bash

if [ -n "$1" ] && [ "$1" = "--USE-VALGRIND" ]; then
    input_file=$2
    touch ./../../memory_error_report.txt
    if [ -n "$3" ]; then
        app_args=$(cat ./../../"$3")
    else
        app_args=""
    fi
    valgrind --log-file=./../../memory_error_report.txt --quiet ./../../main.exe "$app_args" < "$input_file" > ./../../out_neg.txt
    check=$?
else
    input_file=$1
    if [ -n "$2" ]; then
       app_args=$(cat ./../../"$2")
    else
       app_args=""
    fi
    ./../../main.exe "$app_args" < "$input_file" > ./../../out_neg.txt
    check=$?
fi


if [ $check -ne 0 ]; then
    exit 0
else
    exit 1
fi

