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

ls ../data/ > ./../../file.txt
pos_in=()
while IFS=" " read -r line; do pos_in+=("$line"); \
done < <(grep "pos_[0-9][0-9]_in.txt" ./../../file.txt)

pos_out=()
while IFS=" " read -r line; do pos_out+=("$line"); \
done < <(grep "pos_[0-9][0-9]_out.txt" ./../../file.txt)

neg_in=()
while IFS=" " read -r line; do neg_in+=("$line"); \
done < <(grep "neg_[0-9][0-9]_in.txt" ./../../file.txt)

rm ./../../file.txt

pos_args=()
neg_args=()

len_pos=${#pos_in[@]}
len_neg=${#neg_in[@]}

for ((i=0;i<len_pos;i++))
do
     if [ "$i" -ge 0 ] && [ "$i" -lt 9 ]; then
         if [ -e ../data/pos_0"$((i + 1))"_args.txt ]; then
             pos_args[i]=pos_0"$((i + 1))"_args.txt
         else
             pos_args[i]="none"
         fi
     else
         if [ -e ../data/pos_"$((i + 1))"_args.txt ]; then
             pos_args[i]=pos_"$((i + 1))"_args.txt
         else
             pos_args[i]="none"
         fi
     fi
done

for ((i=0;i<len_neg;i++))
do
     if [ "$i" -ge 0 ] && [ "$i" -lt 9 ]; then
         if [ -e ../data/neg_0"$((i + 1))"_args.txt ]; then
             neg_args[i]=neg_0"$((i + 1))"_args.txt
         else
             neg_args[i]="none"
         fi
     else
         if [ -e ../data/neg_"$((i + 1))"_args.txt ]; then
             neg_args[i]=neg_"$((i + 1))"_args.txt
         else
             neg_args[i]="none"
         fi
     fi
done

count_failed_pos_tests=0
count_failed_neg_tests=0

check_args(){
    if [ "$1" == "none" ]; then
        echo ""
    else
        echo "$1"
    fi
}

print_pos(){
    if [ "$1" -eq 0 ]; then
        echo -e "${TURQ}positive test${RESET}" "${TURQ}$2${RESET}": \
        "${GREEN}passed${RESET};" "$3"
    else
        echo -e "${TURQ}positive test${RESET}" "${TURQ}$2${RESET}": \
        "${RED}failed${RESET};" "$3"
    fi
}

print_neg(){
    if [ "$1" -eq 0 ]; then
        echo -e "${BLUE}negative test${RESET}" "${BLUE}$2${RESET}": \
        "${GREEN}passed${RESET};" "$3"
    else
        echo -e "${BLUE}negative test${RESET}" "${BLUE}$2${RESET}": \
        "${RED}failed${RESET};" "$3"
    fi
}

print_valgrind(){
    if [ "$1" -eq 0 ]; then
        echo -e memory: "${GREEN}passed${RESET}"
    else
        echo -e memory: "${RED}failed${RESET};"
    fi
}

print_all_res(){
    echo  -e "${TURQ}Positive test${RESET}": \
    "${YELLOW}correct${RESET}" "$1" of "$2"";"
    echo  -e "${BLUE}Negative test${RESET}": \
    "${YELLOW}correct${RESET}"  "$3" of "$4"";"
}

print_all_res_and_valgrind(){
    echo -e "${TURQ}Positive test${RESET}": "${YELLOW}correct${RESET}"  "$1" of "$2"";" \
    "${YELLOW}memory passed${RESET}"  "$5" of "$2"
    echo -e "${BLUE}Negative test${RESET}": "${YELLOW}correct${RESET}"  "$3" of "$4"";" \
    "${YELLOW}memory passed${RESET}" "$6" of "$4"
}

if [ -n "${USE_VALGRIND}" ]; then
    count_passed_pos_memory=0
    count_passed_neg_memory=0

    for ((i=0;i<len_pos;i++))
    do
        check_local_memory=0
        app_args="$(check_args ${pos_args[i]})"
        ./pos_case.sh "${pos_in[i]}" "${pos_out[i]}" "$app_args"
        check=$?

        if [ $check -eq 3 ]; then
            check_local_memory=2
            check=1
        elif [ $check -eq 2 ]; then
            check_local_memory=2
            check=0
        else
            count_passed_pos_memory=$(( count_passed_pos_memory + 1 ))
        fi

        print_pos $check $((i + 1)) "$(print_valgrind $check_local_memory)"
        count_failed_pos_tests=$(( count_failed_pos_tests + check ))
    done

    echo ""

    for ((i=0;i<len_neg;i++))
    do
        check_local_memory=0
        app_args="$(check_args ${neg_args[i]})"
        ./neg_case.sh "${neg_in[i]}" "$app_args"
        check=$?

        if [ $check -eq 2 ]; then
             check_local_memory=2
             check=0
        else
             count_passed_neg_memory=$(( count_passed_neg_memory + 1 ))
        fi

        print_neg $check $((i + 1)) "$(print_valgrind $check_local_memory)"
        count_failed_neg_tests=$(( count_failed_neg_tests + check ))
    done
else

    for ((i=0;i<len_pos;i++))
    do
        app_args="$(check_args ${pos_args[i]})"
        ./pos_case.sh "${pos_in[i]}" "${pos_out[i]}" "$app_args"
        check=$?
        print_pos $check $((i + 1)) ""
        count_failed_pos_tests=$(( count_failed_pos_tests + check ))
    done

    echo ""

    for ((i=0;i<len_neg;i++))
    do
        app_args="$(check_args ${neg_args[i]})"
        ./neg_case.sh "${neg_in[i]}" "$app_args"
        check=$?
        print_neg $check $((i + 1)) ""
        count_failed_neg_tests=$(( count_failed_neg_tests + check ))
    done
fi

echo ""

correct_pos=$((len_pos - count_failed_pos_tests))
correct_neg=$((len_neg - count_failed_neg_tests))
failed_all_tests=$((count_failed_pos_tests + count_failed_neg_tests))

if [ -n "${USE_VALGRIND}" ]; then
    print_all_res_and_valgrind "$correct_pos" "$len_pos" "$correct_neg" "$len_neg" \
    "$count_passed_pos_memory" "$count_passed_neg_memory"
else
    print_all_res "$correct_pos" "$len_pos" "$correct_neg" "$len_neg"
fi

exit $failed_all_tests
