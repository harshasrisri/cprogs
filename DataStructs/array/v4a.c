# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main (int argc, char **argv) {
	int *num, n = 0, j, k;

	sscanf (argv[1], "%d", &k);
	num = (int*) malloc (sizeof (int));
	for (j = 0; j < k; j++) {
		num[n++] = j;
		if (!(n % 10)) num = (int*) realloc ((char*)num, (n+10) * sizeof (int));
	}
	return 0;
}
