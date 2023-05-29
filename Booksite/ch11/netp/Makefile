CC = gcc
link = ../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = hostinfo echoclient echoserveri

all: $(PROGS)

hostinfo: hostinfo.c $(link)
echoclient: echoclient.c $(link) 
echoserveri: echoserveri.c $(link) echo.c

clean:
	rm -rf *~ $(PROGS)*