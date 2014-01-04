/************************** App for Level 2 List ***************************/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "list.h"

LIST *ld;
char *(*read_pointer)(LIST *);

# define READ() {\
	if (!(data = read_pointer (ld))) {\
		fprintf (stderr, "Read Error\n");\
		continue;\
	} else printf ("%d\n", *(int *)(data));\
}

void display_list (LIST *ld) {
	char *data;

	if ((data = read_smallest (ld))) printf ("%d ", *(int *)(data));
	while ((data = read_bigger (ld))) printf ("%d ", *(int *)(data));
	putchar ('\n');
}

int compare_int (char *x, char *y) {
	return (*(int *)(x)) - (*(int *)(y));
}

int main () {
	char line[40], *str, *data;
	int num, compare_int(char *, char *);

	ld = open_list (sizeof(int), compare_int);
	if (!(ld)) {
		fprintf (stderr, "Error opening List\n");
		exit (1);
	}
	printf ("Type ? or h for Help contents\n");
	while (1) {
		printf ("list> ");
		fgets (line, 40, stdin);
		for (str = line; *str ==  ' ' || *str == '\t'; str++)
			;
		str[strchr (str, '\n') - str] = '\0';

		switch (*str) {
		case '\0' : continue;
		case '0' : case '1' : case '2' : case '3' : case '4' : 
		case '5' : case '6' : case '7' : case '8' : case '9' : 
			num = atoi (str);
			insert (ld, (char *)(&num));
			break;
		default : 
			fprintf (stderr, "Invalid Command : %s\n", str);
			continue;
		case '?' : case 'h' : case 'H' :
			printf ("Type any num to add to list\n"
				"\'f\' to print the first item\n"
				"\'p' to print the previous item\n"
				"r<num> to remove num\n"
				"\'d\' to display all items\n"
				"\'n\' to print the next item\n"
				"\'l\' to print the last item\n"
				"\'e\' to print list and exit\n");
			break;
		case 'f' :
			read_pointer = read_smallest;
			READ();
			break;
		case 'p' :
			read_pointer = read_smaller;
			READ();
			break;
		case 'l' :
			read_pointer = read_biggest;
			READ();
			break;
		case 'n' :
			read_pointer = read_bigger;
			READ();
			break;
		case 'r' : case 'R' :
			for (++str ; *str ==  ' ' || *str == '\t'; str++)
				;
			if (!*str) {
				fprintf (stderr, "what to remove?\n");
				break;
			}
			num = atoi (str);
			if (delete (ld, (char*)(&num))) {
				fprintf (stderr, "%d not on list\n", num);
				continue;
			} else printf ("%d removed\n", num);
			break;
		case 'c' : case 'C' :
			read_pointer = read_current;
			READ();
			break;
		case 'e' : case 'E' :
		case 'd' : case 'D' :
			display_list (ld);
			if ((*str == 'e') || (*str == 'E')) {
				close_list (ld);
				printf ("===> End of App <===\n");
				exit (0);
			}
		}
	}
}
