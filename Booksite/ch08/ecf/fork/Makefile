CC = gcc
file = forkprob
link = ../../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = fork $(file)0 $(file)1 $(file)2 $(file)3 $(file)4 $(file)5 $(file)6 $(file)7 $(file)8

all: $(PROGS)

fork: fork.c $(link)
$(file)0: $(file)0.c $(link)
$(file)1: $(file)1.c $(link)
$(file)2: $(file)2.c $(link)
$(file)3: $(file)3.c $(link)
$(file)4: $(file)4.c $(link)
$(file)5: $(file)5.c $(link)
$(file)6: $(file)6.c $(link)
$(file)7: $(file)7.c $(link)
$(file)8: $(file)8.c $(link)

clean:
	rm -rf *~ $(PROGS)*