CC=gcc
CFLAGS=-Wall -g

all: frequency
frequency: trie.c
	$(CC) $(CFLAGS) -o frequency trie.c

.PHONY: clean all

clean:
	rm -f frequency