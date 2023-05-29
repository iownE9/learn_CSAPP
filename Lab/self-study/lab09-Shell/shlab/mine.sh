#!/bin/bash

touch ./testdir/ref0{1..9}
touch ./testdir/mine0{1..9}
touch ./testdir/dif0{1..9}

for i in {1..9}
do
    make rtest0${i} > ./testdir/ref0${i}
    make test0${i} > ./testdir/mine0${i}
    diff ./testdir/ref0${i} ./testdir/mine0${i} > ./testdir/dif0${i}

    sleep 1
    echo ${i}
done


touch ./testdir/ref1{0..6}
touch ./testdir/mine1{0..6}
touch ./testdir/dif1{0..6}

for i in {0..6}
do
    make rtest1${i} > ./testdir/ref1${i}
    make test1${i} > ./testdir/mine1${i}
    diff ./testdir/ref1${i} ./testdir/mine1${i} > ./testdir/dif1${i}
    
    sleep 1
    echo ${i}
done



# for i in {1..9}
# do
#     touch ./testdir/ref0${i}
#     touch ./testdir/mine0${i}
#     touch ./testdir/dif0${i}
    
#     ./sdriver.pl -t trace0${i}.txt -s ./tshref -a "-p" > ./testdir/ref0${i}
#     ./sdriver.pl -t trace0${i}.txt -s ./tsh -a "-p" > ./testdir/mine0${i}
#     diff ./testdir/ref0${i} ./testdir/mine0${i} > ./testdir/dif0${i}

#     sleep 1
#     echo ${i}
# done



# for i in {0..6}
# do
#     touch ./testdir/ref1${i}
#     touch ./testdir/mine1${i}
#     touch ./testdir/dif1${i}
    
#     ./sdriver.pl -t trace1${i}.txt -s ./tshref -a "-p" > ./testdir/ref1${i}
#     ./sdriver.pl -t trace1${i}.txt -s ./tsh -a "-p" > ./testdir/mine1${i}
#     diff ./testdir/ref1${i} ./testdir/mine1${i} > ./testdir/dif1${i}
    
#     sleep 1
#     echo ${i}
# done