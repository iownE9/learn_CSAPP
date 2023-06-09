CC = gcc
link = ../csapp.c
helper = echo.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = sharing badcnt goodcnt goodmcnt

all: $(PROGS)

sharing: sharing.c $(link)
badcnt: badcnt.c $(link)
goodcnt: goodcnt.c $(link)
goodmcnt: goodmcnt.c $(link)

clean:
	rm -rf *~ $(PROGS)*