CC=g++
CFLAGS=-g3 -O2 -Wall -Werror

all: fib

fib: fib.o
	$(CC) $(CFLAGS) $(^) -o $(@)

fib.o: fib.C
	$(CC) $(CFLAGS) -c $(^) -o $(@)
