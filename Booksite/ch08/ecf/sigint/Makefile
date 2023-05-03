CC = gcc
file = sigint
link = ../../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = $(file)

all: $(PROGS) $(PROGS)safe

$(file): $(file).c $(link)
$(file)safe: $(file)safe.c $(link)

clean:
	rm -rf *~ $(PROGS)*