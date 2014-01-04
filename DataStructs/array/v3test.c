# include <stdio.h>
# include <stdlib.h>

int main (int argc, char **argv) {
	int *num, *old, n = 0, j, i, k;

	sscanf (argv[1], "%d", &k);
	num = (int*) malloc (sizeof (int));
		for (j = 0; j < k; j++) {
			num[n++] = j;
			old = num;
			num = (int*) malloc (++n * sizeof (int));
			for (i = 0; i < n; i++) num[i] = old[i];
		}
	free (num);
	free (old);
	return 0;
}
