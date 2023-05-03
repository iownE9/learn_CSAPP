CC = gcc
file = signal
link = ../../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = $(file)1 $(file)2 signalprob0

all: $(PROGS)

$(file)1: $(file)1.c $(link)
$(file)2: $(file)2.c $(link)
signalprob0: signalprob0.c $(link)

clean:
	rm -rf *~ $(PROGS)*