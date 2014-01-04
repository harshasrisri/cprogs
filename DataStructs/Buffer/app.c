# include <stdio.h>
# include <stdlib.h>
# include "buff.h"
# include <string.h>
# define NMAX 10

int main (int argc, char **argv) {
	BUFF *bd;
	char line[20], *str;
	int num, nmax;

	if (argc == 1) nmax = NMAX;
	else nmax = atoi (*++argv);

	if (!(bd = open_buff (nmax))) {
		fprintf (stderr, "Invalid size specified\n");
		exit (1);
	}
	printf ("\n Enter a char to write," 
					" o<num> to read num no. of chars, 'exit' to exit\n");

	while (1) {
		if (buff_full(qd))
			printf ("read only: ");
		else if (buff_empty(qd))
			printf ("write only: ");
		else printf ("read/write: ");

		if (!fgets (line, 20, stdin)) exit (1);
		for (str = line; *str == ' ' || *str == '\t'; str++)
			;
		if (!strncmp(str, "exit", 4)) {
			if (!buff_empty(bd)) printf ("Remaning buffer elements : ");
			while (!buff_empty(bd))
				printf ("%c ", rd_buff(bd));
			printf ("\n===>End of App<===\n");
			exit (0);
		}

		switch (*str) {
			case '\n' : continue;
			case 'o': case 'O':
				if ((num = atoi (str + 1))) {
					while (num--) {
						if (!buff_empty(bd)) printf ("%c\n", rd_buff(bd));
						else {
							printf ("Buffer Empty\n");
							num = -1;
							break;
						}
					}
					if (num == -1) continue;
				}
			default	: 
				if (wrt_buff (bd, *str))
					printf ("Buffer Full. read out items first.\n");
				break;
		}
	}
}
