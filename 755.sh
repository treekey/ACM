#! /bin/bash

read_input () {
    local n i line
    local array=()

    read line # read '\n'
    read n
    for ((i=0;i<n;++i)) {
        read line
        array=("${array[@]}" $line)
    }
    echo ${array[@]}
}


format () {
    local array=("$@")

    IFS=$'\n'
    echo "${array[*]}" |
         tr [ABC] 2 |
         tr [DEF] 3 |
         tr [GHI] 4 |
         tr [JKL] 5 |
         tr [MNO] 6 |
         tr [PRS] 7 |
         tr [TUV] 8 |
         tr [WXY] 9 |
         tr -d "-" |
         awk '{print substr($1, 0, 3) "-" substr($1, 3)}'
    unset IFS
}

count () {
    local array=("$@")

    IFS=$'\n'
    echo "${array[*]}" | sort | uniq -c -d | awk '{printf "%s:%s\n", $2, $1}'
    unset IFS
}


read n
for ((i=0;i<n;++i)) {

    array=($(read_input))
    format_array=($(format "${array[@]}"))
    result=($(count "${format_array[@]}"))

    if [ ${#result[@]} -gt 0 ]; then
        IFS=$'\n'
        echo "${result[*]}" | tr -d ":"
        unset IFS
    else
        echo "no"
    fi
}
