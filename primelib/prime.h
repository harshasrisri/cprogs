#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef unsigned long long ull;

typedef struct {
	ull limit;
	char *primes;
	int highest;
	int count;
} PRIME;

extern PRIME* prepare_primes (ull limit);

#define is_prime(x,y) (!checkbit(x,y))
#define is_not_prime(x,y) (checkbit(x,y))
