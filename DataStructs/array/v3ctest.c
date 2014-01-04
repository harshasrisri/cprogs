# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main (int argc, char **argv) {
	int *num, *old, n = 0, j, k;

	sscanf (argv[1], "%d", &k);
	num = (int*) malloc (sizeof (int));
	for (j = 0; j < k; j++) {
		num[n++] = j;
		old = num;
		num = (int*) malloc (++n * sizeof (int));
		memcpy ( (char*)num, (char*)old, n * sizeof (int));
	}
	return 0;
}
