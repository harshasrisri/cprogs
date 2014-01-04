# include <stdio.h>
# include <stdlib.h>
# define NMAX 20

int main () {
	int stack[NMAX], sp = 0;
	char line[20], *str;

	while (1) {
		if (sp == NMAX)
			printf ("p to pop, e to exit : ");
		else if (!sp)
			printf ("int to push, e to exit : ");
		else printf ("int to push, p to pop, e to exit : ");

		if (!fgets (line, 20, stdin)) exit (1);
		for (str = line; *str == ' ' || *str == '\t'; str++);

		switch (*str) {
			default : continue;
			case '\n' : continue;
			case '-': case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				if (sp == NMAX)
					printf ("Stack Full. Pop items first.\n");
				else
					stack[sp++] = atoi(str);
				continue;
			case 'p': case 'P':
				if (!sp)
					printf ("nothing to pop\n");
				else 
					printf ("%d\n", stack[--sp]);
				continue;
			case 'e': case 'E':
				if (sp) {
					printf ("stack contents are : ");
					while (sp)
						printf ("%d ", stack[--sp]);
				}
				printf ("\nend of prog\n");
				exit (0);
		}
	}
}
