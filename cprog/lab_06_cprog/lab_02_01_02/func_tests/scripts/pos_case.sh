#!/bin/bash

input_file=$1
reference_output=$2

if [ -n "$3" ]; then
    app_args=$(cat ../data/"$3")
else
    app_args=""
fi

if [ -n "${USE_VALGRIND}" ]; then
    check_memory=0
    mycommand="valgrind --log-file=./../../memory_error_report.txt --quiet ./../../app.exe $app_args < $input_file > ./../../out.txt"
    eval "$mycommand"
    code_return=$?
    if [ -s ./../../memory_error_report.txt ]; then
        check_memory=2
    fi
    
    if [ $code_return -eq 0 ]; then
    	./comparator.sh ./../../out.txt "$reference_output"
    	check=$?
        if [ $check -eq 0 ] && [ $check_memory -eq 0 ]; then 
            exit 0
        elif [ $check -eq 0 ] && [ $check_memory -eq 2 ]; then
            exit 2
        elif [ $check -eq 1 ] && [ $check_memory -eq 0 ]; then
    	    exit 1
        else 
    	    exit 3
        fi
    else
        exit 1
    fi

else
    mycommand="./../../app.exe $app_args < $input_file > ./../../out.txt"
    eval "$mycommand"
    code_return=$?
    if [ $code_return -eq 0 ]; then
    	./comparator.sh ./../../out.txt "$reference_output"
    	check=$?
    	if [ $check -eq 0 ]; then 
            exit 0
    	else
            exit 1
    	fi
    else
    	exit 1
    fi
fi


