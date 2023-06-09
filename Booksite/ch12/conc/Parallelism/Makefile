CC = gcc
link = ../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = psum-mutex psum-array psum-local

all: $(PROGS)

psum-mutex: psum-mutex.c $(link)
psum-array: psum-array.c $(link)
psum-local: psum-local.c $(link)

clean:
	rm -rf *~ $(PROGS)*