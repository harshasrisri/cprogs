# include <stdio.h>
# include <stdlib.h>
# define NMAX 20

int main () {
	int place = 0, num[NMAX], n;
	
	while (place < NMAX)
		if (scanf ("%d", &num[place]) == 1)
			place++;
		else break;
	if (!place) {
		fprintf (stderr, "be serious\n");
		exit (1);
	}
	for (n = 0; n < place; n++)
		printf ("%d\t", num[n]);
	return 0;
}
