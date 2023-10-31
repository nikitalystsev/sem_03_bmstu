#!/bin/bash

$(cmp -s -c "$1" "$2")
rc="$?"

if [ "$rc" -eq 0 ]; then
    exit 0
else
    exit 1
fi
