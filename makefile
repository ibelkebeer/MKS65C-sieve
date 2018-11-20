all: sieve.c sieve.h
	gcc sieve.c -lm

run: a.out
	time ./a.out
