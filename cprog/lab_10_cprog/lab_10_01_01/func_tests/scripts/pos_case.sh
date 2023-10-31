#!/bin/bash

RESET="\033[0m"
BLACK="\033[0;m"
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
VIOLET="\033[0;35m"
TURQ="\033[0;36m" # бирюзовый
WHITE="\033[0;37m"

if [ -n "$3" ]; then
    app_args=$(cat ../data/"$3")
else
    app_args=""
fi

if [ -n "${USE_VALGRIND}" ]; then
    check_memory=0

    cd ../.. || exit
    mycommand="valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all \
    --log-file=./out/memory_error_report.txt -q ./app.exe $app_args"
    eval "$mycommand"
    code_return=$?
    echo -e "rc = ${VIOLET}$code_return${RESET}"

    if [[ -s ./out/memory_error_report.txt ]]; then
        check_memory=2
    fi
    cd func_tests/scripts || exit

    if [ $code_return -eq 0 ]; then
    	./comparator.sh ../../out/"$2" ../data/"$2"
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
    cd ../.. || exit
    mycommand="./app.exe $app_args"
    eval "$mycommand"
    code_return=$?
    echo -e "rc = ${VIOLET}$code_return${RESET}"
    cd func_tests/scripts || exit

    if [ $code_return -eq 0 ]; then
    	./comparator.sh ../../out/"$2" ../data/"$2"
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
