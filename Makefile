CC=clang
CFLAGS=-Wall -Wextra -pedantic

prob1a: prob1a.c
	$(CC) $(CFLAGS) -o prob1a prob1a.c

prob1b: prob1b.c
	$(CC) $(CFLAGS) -o prob1b prob1b.c

prob2: prob2.c
	$(CC) $(CFLAGS) -o prob2 prob2.c

prob3: prob3.c
	$(CC) $(CFLAGS) -o prob3 prob3.c

prob4: prob4.c
	$(CC) $(CFLAGS) -o prob4 prob4.c

prob5: prob5.c
	$(CC) $(CFLAGS) -o prob5 prob5.c

prob6: prob6.c
	$(CC) $(CFLAGS) -o prob6 prob6.c

prob7: prob7.c
	$(CC) $(CFLAGS) -o prob7 prob7.c

prob8: prob8.c arith.o
	$(CC) $(CFLAGS) -o prob8 prob8.c arith.o

prob9: prob9.c
	$(CC) $(CFLAGS) -o prob9 prob9.c

arith.o: lib/arith.h lib/arith.c
	$(CC) $(CFLAGS) -c lib/arith.c

clean:
	rm *.o prob1a prob1b prob2 prob3 prob4 prob5 \
		prob6 prob7 prob8 prob9 prob 10