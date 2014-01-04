# include <stdio.h>
# include <stdlib.h>
# include "stack.h"
# include <string.h>

int main (int argc, char **argv) {
	STACK *sd;
	char line[20], *str;
	float num;
	int nmax;

	if (argc != 2) {
		fprintf (stderr, "Usage:a.out [num | -d]" 
				" where num = size of stack, -d = dynamic\n");
		exit (0);
	}

	if (!strcmp (*++argv, "-d")) nmax = 0;
	else nmax = atoi (*argv);

	if (!(sd = open_stack (sizeof(int), nmax))) {
		fprintf (stderr, "Invalid sizes specified\n");
		exit (1);
	}

	if (!(sd = open_stack (sizeof(float), nmax))) {
		fprintf (stderr, "Invalid sizes specified\n");
		exit (1);
	}
	while (1) {
		if (stack_full(sd) && nmax)
			printf ("p to pop, e to exit : ");
		else if (stack_empty(sd))
			printf ("num to push, e to exit : ");
		else printf ("num to push, p to pop, e to exit : ");

		if (!fgets (line, 20, stdin)) exit (1);
		for (str = line; *str == ' ' || *str == '\t'; str++);

		switch (*str) {
			default : continue;
			case '\n' : continue;
			case '-': case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9': case '.':
				num = atof (str);
				if (push (sd, (char*) &num))
					printf ("Stack Full. Pop items first.\n");
				break;
			case 'p': case 'P':
				if (pop (sd, (char*) &num))
					printf ("nothing to pop\n");
				else
					printf ("%f\n", num);
				break;
			case 'e': case 'E':
				if (!stack_empty(sd)) {
					printf ("remaining stack contents : ");
					while (!stack_empty(sd)) {
						pop (sd, (char*) &num);
						printf ("%f ", num);
					}
				}
				printf ("\nEnd of program\n");
				exit (0);
		}
	}
}
