# include <stdio.h>

int main () {
	int i;

	printf ("Press Ctrl+C to stop\n");
	while (1)
		for (i = 0; i <= 999; i++)
			printf ("%3d\b\b\b", i);
	return 0;
}
