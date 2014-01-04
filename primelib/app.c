#include <stdio.h>
#include "prime.h"

int main (int argc, char **argv) {
	PRIME *prime = prepare_primes (atoll(argv[1]));
	return 0;
}
