CC = gcc
file = foo
link = ../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = $(file)

all: $(PROGS)

$(file): $(file).c $(link)

clean:
	rm -rf *~ $(PROGS)*