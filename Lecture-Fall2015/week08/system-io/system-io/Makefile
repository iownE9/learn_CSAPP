CC     := gcc
CFLAGS := -std=c99 -g -Og -Werror -Wall -Wextra -Wpedantic
CFLAGS += -Wstrict-prototypes -Wmissing-prototypes -Wwrite-strings

ALL    := unixcat three timing doublecat childcat

.PHONY: all
all: $(ALL)

.PHONY: clean
clean:
	-rm -f $(ALL) $(ALL:=.o) $(ALL:=.s)
