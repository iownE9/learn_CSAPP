CC       := gcc
CFLAGS   := -std=c11 -g -Og -Werror -Wall -Wextra -Wpedantic -Wconversion
CFLAGS   += -Wstrict-prototypes -Wmissing-prototypes -Wwrite-strings
CPPFLAGS := -D_GNU_SOURCE=1

SOURCES  := $(wildcard *.c)
PROGRAMS := $(SOURCES:.c=)

.PHONY: list
list:
	@echo "Targets:"
	@printf '  %s\n' $(PROGRAMS) all

.PHONY: all
all: $(PROGRAMS)

bounds: benchmark.h
faults: benchmark.h
timings: benchmark.h

.PHONY: clean
clean:
	-rm -f $(PROGRAMS)
	-rm -f vm-concepts.tar

vm-concepts.tar: benchmark.h Makefile $(SOURCES)
	tar cf $@ $^
