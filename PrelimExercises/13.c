# include <stdio.h>

int main ( int argc, char **argv ) {
	int i = 10, j, k, p[10];

	printf ("enter the numbers to be sorted\n");
	for (j = 0; j < i; j++)
		scanf ("%d", &p[j]);
	for (j = 0; j < i-1; j++)
		for (k = 0; k < k-j; k++)
			if (p[k] > p[k+1]) {
				int t;
				t = p[k];
				p[k] = p[k+1];
				p[k+1] = t;
			}
	for (j = 0; j < i; j++) printf ("\t%d", p[j]);
	return 0;
}
