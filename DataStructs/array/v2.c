# include <stdio.h>
# include <stdlib.h>

int main () {
	int place = 0, *num, nmax, sum = 0, min, max;
	
	printf ("Enter number of entries u wanna make : ");
	if (scanf ("%d", &nmax) != 1) {
		fprintf (stderr, "be serious\n");
		exit (1);
	}
	if (nmax < 1 || nmax > 25) {
		fprintf (stderr, "be serious\n");
		exit (2);
	}
	num = (int*) malloc (nmax * sizeof (int));	
	while (place < nmax)
		if (scanf ("%d", &num[place]) == 1)
			place++;
		else break;
	if (!place) {
		fprintf (stderr, "be serious\n");
		exit (1);
	}
	min = max = num[0];
	for (nmax = 0; nmax < place; nmax++) {
		printf ("%d\t", num[nmax]);
		sum += num[nmax];
		if ( num[nmax] > max ) max = num[nmax];
		if ( num[nmax] < min ) min = num[nmax];
	}
	printf ("\nSum of all : %d\nMaximum : %d\nMinimum : %d\nAverage : %d\n",
				sum, max, min, (sum/place));
	return 0;
}
