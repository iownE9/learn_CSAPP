CC = gcc
link = ../csapp.c
helper = echo.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = select echoservers

all: $(PROGS)

select: select.c $(helper) $(link)
echoservers: echoservers.c $(link)

clean:
	rm -rf *~ $(PROGS)*