# Makefile to generate dhtest

#prefix?=$(DESTDIR)/usr

CC=gcc
CFLAGS?=-Wall -O3 -g --std=c99 -D_SVID_SOURCE -D_POSIX_SOURCE -D_BSD_SOURCE

#CFLAGS=-Wall -fno-stack-protector
#CFLAGS?=  -O0 -Wall -ggdb

%.o: %.c headers.h
	$(CC) $(CFLAGS) -o $@ -c $<

dhtest: dhtest.o functions.o
	$(CC) dhtest.o functions.o -o dhtest

test: test.o
	$(CC) test.o -o test

#install: dhtest
#	install -d $(prefix)/sbin
#	install -m 0755 dhtest $(prefix)/sbin

clean:
	rm -f dhtest *.o

#.PHONY: install
