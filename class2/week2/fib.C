#include <stdio.h>

int main(int argc, char *argv[]) {
	int fib[10];

	fib[0] = 0;
	fib[1] = 1;

	for (int i = 2; i < 10; ++i) fib[i] = fib[i-1] + fib[i-2];
	for (int i = 0; i < 6; ++i) {
		printf("%d\n", fib[i]);
	}

	return(0);
}
