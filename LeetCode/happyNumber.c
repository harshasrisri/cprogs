#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>

int reduce (int n) {
	int sum = 0;
	while (n) {
		sum += (n % 10) * (n % 10);
		n /= 10;
	}
	return sum;
}

bool isHappy(int n) {
	static char first = 1, *happiness;

	if (first) {
		happiness = (char *) calloc (1000, sizeof(char));
		first = 0;
	}

	printf ("%d ", n);

	if (n == 0) return false;
	if (n == 1) return true;

	while (n > 1000) n = reduce (n);
	
	if (happiness[n] != 0) {
		if (happiness[n] > 0) return true;
		if (happiness[n] < 0) return false;
	} else {
		if (isHappy(reduce(n))) {
			happiness[n] = 1;
			return true;
		} else {
			happiness[n] = -1;
			return false;
		}
	}
}

int main (int argc, char **argv) {
	int i;

	/* if (isHappy(i = atoi(argv[1]))) printf ("%d - Happy\n", i); */

	for (i = 0; i < atoi (argv[1]); i++) {
		if (isHappy(i)) printf ("- Happy");
		printf ("\n");
	}

	return 0;
}
