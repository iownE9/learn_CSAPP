CC = gcc
link = ../csapp.c
helper = echo.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = echoserverp hellobug

all: $(PROGS)

echoserverp: echoserverp.c $(helper) $(link)
hellobug: hellobug.c $(link)

clean:
	rm -rf *~ $(PROGS)*