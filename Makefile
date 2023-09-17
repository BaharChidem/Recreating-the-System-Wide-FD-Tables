# Makefile for Assignment 2

CC = gcc
CFLAGS = -Wall -Werror

all: showFDtables

showFDtables: print_s.o link-list.o a2.o
	$(CC) $(CFLAGS) -o $@ $^

.%o:%.c a2.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm *.o showFDtables
clean_txt:
	rm compositeTable.txt 
clean_bin:
	rm compositeTable.bin