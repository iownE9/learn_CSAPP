CC := gcc

override CFLAGS   := -std=c99 -Og -Wall -Wextra -Wpedantic $(CFLAGS)
override LDFLAGS  := -pthread

.PHONY: list
list:
	@echo "Targets:"
	@ls *.c | sed 's/\.c//'

falseSharing: csapp.c

.PHONY: clean
clean: $(wildcard *.c)
	$(RM) $(^:.c=)
