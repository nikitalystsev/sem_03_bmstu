#!/bin/bash

file_1=$1
file_2=$2

n1=$(wc -l < "$file_1")
n2=$(wc -l < "$file_2")

grep -EA"$n1"  "Result: .*" "$file_1" > ./../../numb1.txt
ex=$(grep -oE "Result: .*" "$file_1")
line=$(head -n 1 ./../../numb1.txt)
sed -i "1s/$line/$ex/" ./../../numb1.txt 

grep -EA"$n2"  "Result: .*" "$file_2" > ./../../numb2.txt
ex=$(grep -oE "Result: .*" "$file_2")
line=$(head -n 1 ./../../numb2.txt)
sed -i "1s/$line/$ex/" ./../../numb2.txt 

diff ./../../numb1.txt ./../../numb2.txt > ./../../output_diff.txt

if [ -s ./../../output_diff.txt ]; then
    exit 1
else
    exit 0
fi
