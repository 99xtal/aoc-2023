CC=clang
CFLAGS=-std=c99 -Wall -Wextra -pedantic

main: main.c arith.o
	$(CC) $(CFLAGS) -o main main.c arith.o

arith.o: arith.h arith.c
	$(CC) $(CFLAGS) -c arith.c
