# include <stdio.h>
# include <stdlib.h>

int main (int argc, char **argv) {
	if (argc != 2) {
		fprintf (stderr, "Usage: cmd <number>\n");
		exit (1);
	}

	int n = atoi (*++argv), place = 0, num[n];
	
	for (place = 0; place < n; place++)
		num[place] = place;
	if (!place) {
		fprintf (stderr, "be serious\n");
		exit (1);
	}
	for (n = 0; n < place; n++)
		/*if (!(n % 1000))*/ printf ("%d ", num[n]);
	putchar ('\n');
	return 0;
}
