#include <stdio.h>
#include <stdlib.h>

int main () {
	int N = 50000 + rand() % 50000;
	int U = N + rand() % N;
	int C = N + rand() % N;
	int i;

	printf ("%d\n", N);

	for (i = 0; i < U; i++)
		printf ("%d,%d\n", rand() % N, rand() % N);

	printf ("-\n");

	for (i = 0; i < C; i++)
		printf ("%d,%d\n", rand() % N, rand() % N);

	return 0;
}
