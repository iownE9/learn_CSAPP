CC = gcc
file = hex2dd
link = ../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = $(file)

all: $(PROGS)

$(file): $(file).c $(link)

clean:
	rm -rf *~ $(PROGS)*