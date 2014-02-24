# Makefile to generate dhtest
#	$*: the target name, without a suffix.
#	$@: the target name.
#	$^: a list of the sources, in alphabetical order, with duplicates removed.
#	$+: all the sources, in the original order.
#	$<: the first source.

#prefix?=$(DESTDIR)/usr

CC=gcc
CFLAGS?=-Wall -O3 -g --std=c99 -D_SVID_SOURCE -D_POSIX_SOURCE -D_BSD_SOURCE
#CFLAGS=-Wall -fno-stack-protector
#CFLAGS?=  -O0 -Wall -ggdb

ARCH := $(shell getconf LONG_BIT)
ifeq ($(ARCH),64)
CFLAGS += -m32
endif

%.o: %.c headers.h
	$(CC) $(CFLAGS) -c $< -o $@

dhtest: dhtest.o functions.o
	$(CC) $(CFLAGS) dhtest.o functions.o -o dhtest

test: test.o
	$(CC) $(CFLAGS) test.o -o test

#.PHONY: install
#install: dhtest
#	install -d $(prefix)/sbin
#	install -m 0755 dhtest $(prefix)/sbin

clean:
	rm -f dhtest *.o
