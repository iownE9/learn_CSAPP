CC = gcc
# file = foo
link = ../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = cpstdin cpfile readdir statcheck

all: $(PROGS)

cpstdin: cpstdin.c $(link)
cpfile: cpfile.c $(link)
readdir: readdir.c $(link)
statcheck: statcheck.c $(link)

clean:
	rm -rf *~ $(PROGS)*