#!/bin/bash

if [ -n "$1" ] && [ "$1" = "--USE-VALGRIND" ]; then
    input_file=$2
    reference_output=$3
    touch ./../../memory_error_report.txt
    if [ -n "$4" ]; then
        app_args=$(cat ../data/"$4")
    else
 	app_args=""
    fi
    valgrind --log-file=./../../memory_error_report.txt --quiet ./../../main.exe "$app_args" < "$input_file" > ./../../out_pos.txt
    code_return=$?
else
    input_file=$1
    reference_output=$2
    if [ -n "$3" ]; then
        app_args=$(cat ../data/"$3")
    else
        app_args=""
    fi
    ./../../main.exe "$app_args" < "$input_file" > ./../../out_pos.txt
    code_return=$?
fi

if [ $code_return -eq 0 ]; then
    ./comparator.sh ./../../out_pos.txt "$reference_output"
    check=$?
    if [ $check -eq 0 ]; then 
        exit 0
    else
        exit 1
    fi
else
    exit 1
fi
