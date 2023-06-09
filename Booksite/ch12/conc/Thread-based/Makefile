CC = gcc
link = ../csapp.c
helper = echo.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = hello echoservert

all: $(PROGS)

hello: hello.c $(link)
echoservert: echoservert.c $(helper) $(link)

clean:
	rm -rf *~ $(PROGS)*