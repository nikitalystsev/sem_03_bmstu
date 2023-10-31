#!/bin/bash

array_sizes=("5" "500" "1000" "1500" "2000" "2500" "3000" "3500" "4000" "4500" "5000" "5500" "6000" "6500" "7000" "7500" "8000" "8500" "9000" "9500" "10000" "20000" "30000" "40000" "50000")

len_array_sizes=${#array_sizes[@]}

count=0
all_count=$((len_array_sizes * 3))

if ! [ -d ./apps ]; then
    mkdir apps
fi

echo "start compiling!"

for size in "${array_sizes[@]}"; do
    gcc -std=c99 -Wall -Werror -Wpedantic -DNMAX="${size}"\
    -Wextra -Wfloat-conversion -Wfloat-equal -O2 \
    -o ./apps/mysort_"${size}".exe main.c

    gcc -std=c99 -Wall -Werror -Wpedantic -DNMAX="${size}"\
    -Wextra -Wfloat-conversion -Wfloat-equal -O2 \
    -o ./apps/qsort_"${size}".exe main2.c

    gcc -std=c99 -Wall -Werror -Wpedantic -DNMAX="${size}"\
    -Wextra -Wfloat-conversion -Wfloat-equal -O2 \
    -o ./apps/mysort_memcpy_"${size}".exe main3.c

    count=$((count + 3))
    echo -n -e "was compiling $count/$all_count files\r"
done

echo -e "\nfinish compiling!"
