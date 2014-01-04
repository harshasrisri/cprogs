# include <stdio.h>
# include <stdlib.h>

int main (int argc, char **argv) {
	int *num, *old, n = 0, j, i, k;
	register int *src, *dst;

	sscanf (argv[1], "%d", &k);
	num = (int*) malloc (sizeof (int));
	for (j = 0; j < k; j++) {
		num[n++] = j;
		old = num;
		num = (int*) malloc (++n * sizeof (int));
		src = old;
		dst = num;
		for (i = 0; i < n; i++) *dst++ = *src++;
	}
	return 0;
}
