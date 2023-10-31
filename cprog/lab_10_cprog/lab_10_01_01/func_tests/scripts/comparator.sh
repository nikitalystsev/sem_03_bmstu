#!/bin/bash

file_1=$1
file_2=$2

$(cmp -s -c "$file_1" "$file_2")
rc="$?"

if [ "$rc" -eq 0 ]; then
    exit 0
else
    exit 1
fi
