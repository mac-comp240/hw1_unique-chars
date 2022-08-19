# makefile for hasUniqueChars

CC = gcc

hasUniqueChars: hasUniqueChars.c test.c binary_convert.c binary_convert.h
	$(CC) -o hasUniqueChars binary_convert.c hasUniqueChars.c test.c

clean:
	rm -f hasUniqueChars
