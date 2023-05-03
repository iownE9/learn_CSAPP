CC = gcc
file = waitforsignal
link = ../../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = $(file) sigsuspend

all: $(PROGS)

$(file): $(file).c $(link)
sigsuspend: sigsuspend.c $(link)

clean:
	rm -rf *~ $(PROGS)*