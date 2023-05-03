CC = gcc
file = waitprob
link = ../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = $(file)0 $(file)1 $(file)3

all: $(PROGS)

$(file)0: $(file)0.c $(link)
$(file)1: $(file)1.c $(link)
$(file)3: $(file)3.c $(link)

clean:
	rm -rf *~ $(PROGS)*