#!/bin/bash

array_sizes=("5" "500" "1000" "1500" "2000" "2500" "3000" "3500" "4000" "4500" "5000" "5500" "6000" "6500" "7000" "7500" "8000" "8500" "9000" "9500" "10000" "20000" "30000" "40000" "50000")
count=10

################################################################################################################

# сборка основного датасета

len_array_sizes=${#array_sizes[@]}
len_opts=${#opts[@]}

counter=0 # счетчик
all_count=$((len_array_sizes *  count * 3)) # общее количество возможных вариантов программ

# компилирую
bash build_apps.sh


echo -e "\nstart collecting data!"

for c in $(seq "$count"); do
    for size in "${array_sizes[@]}"; do
        # запускаю тестирование вот тут,
        # count отвечает за количество строчек в файле ./data/data"${number}"_"${array_size}".txt
        ./apps/mysort_"${size}".exe >> ./data/mysort_"${size}".txt

        ./apps/qsort_"${size}".exe >> ./data/qsort_"${size}".txt

        ./apps/mysort_memcpy_"${size}".exe >> ./data/mysort_memcpy_"${size}".txt
        counter=$((counter + 3))
        echo -n -e "was collecting $counter/$all_count.  $c/$count $size \r"
    done
done

echo  -e "\nfinish collecting data!"

#################################################################################################################

# первичный анализ и подготовка данных для построения первого графика

ls ./data > ls_data.txt
files=$(grep -v "clean.sh" ls_data.txt)
rm ls_data.txt


if ! [ -d ./postproc_data ]; then
    mkdir postproc_data
fi

if ! [ -d ./postproc_data/grap1 ]; then
    mkdir postproc_data/grap1
fi

counter=0
all_count=$(( len_array_sizes  * 3))

echo -e "\nstart get info for graph1!"

for size in "${array_sizes[@]}"; do
    for file in $files; do

        cd preproc_scripts/ || exit
        bash build_c_scripts.sh
        cd ../

        if [ "${file}" == "mysort_""${size}"".txt" ]; then
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")
            echo "${size} ${ar_time}" >> ./postproc_data/grap1/mysort.txt
            counter=$((counter + 1))
        fi

        if [ "${file}" == "qsort_""${size}"".txt" ]; then
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")
            echo "${size} ${ar_time}" >> ./postproc_data/grap1/qsort.txt
            counter=$((counter + 1))
        fi

        if [ "${file}" == "mysort_memcpy_""${size}"".txt" ]; then
            ar_time=$(preproc_scripts/ar_mean.exe < ./data/"${file}")
            echo "${size} ${ar_time}" >> ./postproc_data/grap1/mysort_memcpy.txt
            counter=$((counter + 1))
        fi

        echo -n -e "$counter/$all_count records were received\r"
    done
done

echo  -e "\nfinish get info for graph1!"

#################################################################################################################
