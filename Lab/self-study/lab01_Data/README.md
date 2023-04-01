# Lab01_Data

## 谨记

做题三大宝：
找规律
分类讨论
临界分析

隐式向无符号转换
a ^ a = 0
-x = ~x + 1
INT_MIN = ~INT_MIN + 1
(x << (n+1)) - (x << m)

非规范 E = 1 -bias; M = f
  规范 E = e -bias; M = 1 + f

## 指导

unix> tar xvf datalab-handout.tar
unix> make

// 数子表示
unix> ./ishow 0x27
Hex = 0x00000027, Signed = 39, Unsigned = 39

unix> ./fshow 2080374784
Floating point value 2.658455992e+36
Bit Representation 0x7c000000, sign = 0, exponent = 0xf8, fraction = 0x000000
Normalized.  +1.0000000000 X 2^(121)

unix> ./fshow 0x15213
Floating point value 1.212781782e-40
Bit Representation 0x00015213, sign = 0, exponent = 0x00, fraction = 0x015213
Denormalized.  +0.0103172064 X 2^(-126)

unix> ./fshow 15.2130003
Floating point value 15.2130003
Bit Representation 0x41736873, sign = 0, exponent = 0x82, fraction = 0x736873
Normalized.  +1.9016250372 X 2^(3)

// 检测代码正确性
unix> ./btest

// 指定题目
unix> ./btest -f bitXor

unix> ./btest -f bitOr -1 7 -2 0xf
This will call bitOr exactly once, using the arguments x=7 and y=15.

rebuild btest each time you modify your bits.c file

// 统计操作符
unix> ./dlc bits.c

unix> ./dlc -e bits.c // 详细输出

unix> ./dlc -help

// 综合命令
unix> ./driver.pl

## other

Fall-2015/L1-datalab/datalab.pdf-7
