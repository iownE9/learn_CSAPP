CC = gcc
link = ../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = echoservert_pre

all: $(PROGS)

echoservert_pre: echoservert_pre.c sbuf.c echo_cnt.c $(link)

clean:
	rm -rf *~ $(PROGS)*