#!/bin/bash

file_1=$1
file_2=$2

grep -oE "[+-]?[0-9]+([.][0-9]+)?" "$file_1" > ./../../numb1.txt
grep -oE "[+-]?[0-9]+([.][0-9]+)?" "$file_2" > ./../../numb2.txt


diff ./../../numb1.txt ./../../numb2.txt > ./../../output_diff.txt

if [ -s ./../../output_diff.txt ]; then
    exit 1
else
    exit 0
fi
