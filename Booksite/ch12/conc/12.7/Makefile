CC = gcc
link = ../csapp.c
CFLAGS = -Og
LDLIBS = -lpthread

PROGS = ctime_ts norace race rand_r rand

all: $(PROGS)

ctime_ts: ctime_ts.c $(link)
norace: norace.c $(link)
race: race.c $(link)
rand_r: rand_r.c
rand: rand.c

clean:
	rm -rf *~ $(PROGS)*