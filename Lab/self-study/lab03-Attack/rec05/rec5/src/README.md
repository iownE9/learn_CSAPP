# Note

gcc -Og -c -g activity.c -o activity.o

objdump -d activity.o > activity.d


gcc -Og -c -g -fno-stack-protector activity.c -o activity-nsp.o

objdump -d activity-nsp.o > activity-nsp.d
