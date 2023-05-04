CC = gcc
file = foobar
link = ../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = $(file) $(file)2 $(file)3

all: $(PROGS)

$(file): $(file).c $(link)
$(file)2: $(file)2.c $(link)
$(file)3: $(file)3.c $(link)

clean:
	rm -rf *~ $(PROGS)*