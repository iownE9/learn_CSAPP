#!/bin/bash

python3 wget.py

i=1
while read line
do
    if [ ${i} -lt 6 ];then
        ((i++))
    else
        wget ${line}      
    fi
done < url.txt