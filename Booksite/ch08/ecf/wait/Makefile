CC = gcc
file = waitpid
link = ../../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = $(file)1 $(file)2

all: $(PROGS)

$(file)1: $(file)1.c $(link)
$(file)2: $(file)2.c $(link)

clean:
	rm -rf *~ $(PROGS)*