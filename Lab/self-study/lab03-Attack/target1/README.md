# 95分

**欢迎大佬指点迷津** 

**详见 phase5/README.md** 



> ./ctarget -q -i exploit.bin

> gdb -q ctarget

(gdb) run -q -i exploit.bin


## phase 1

> ./hex2raw < phase1.txt > phase1.bin

> ./ctarget -q -i phase1.bin


## phase 2

> gcc -c phase2.s -o phase2.o

> objdump -d phase2.o > phase2.d

phase2.d -> phase2.txt



This file contains materials for one instance of the attacklab.

Files:

    ctarget

Linux binary with code-injection vulnerability.  To be used for phases
1-3 of the assignment.

    rtarget

Linux binary with return-oriented programming vulnerability.  To be
used for phases 4-5 of the assignment.

     cookie.txt

Text file containing 4-byte signature required for this lab instance.

     farm.c

Source code for gadget farm present in this instance of rtarget.  You
can compile (use flag -Og) and disassemble it to look for gadgets.

     hex2raw

Utility program to generate byte sequences.  See documentation in lab
handout.

