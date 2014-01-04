/************************** App for List ***************************/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "list.h"

LIST *ld;

# define PRINT_MSG {fprintf (stderr, "Read Error\n");continue;} else printf ("%s\n", Data);break;

void print_list (LIST *ld) {
	char *data;

	for (Trans = First; Trans; Trans = Next)
		printf ("%s ", Data);
	putchar ('\n');
}

int main () {
	char line[40], *str, cmd, last_cmd = 0;

	if (!(ld = open_list ())) {
		fprintf (stderr, "Error opening List\n");
		exit (1);
	}
	printf ("Type \'-?\' or \'-h\' for Help contents\n");
	while (1) {
		printf ("list> ");
		fgets (line, 40, stdin);
		for (str = line; *str ==  ' ' || *str == '\t'; str++)
			;
		str[strchr (str, '\n') - str] = '\0';

		switch (*str) {
		case '\0' : continue;
		default :
			append (ld, str);
			break;
		case '.' : 
			cmd = last_cmd;
		case '-' :
			if (*str != '.') cmd = last_cmd = *++str;
			switch (cmd) {
			default : 
				fprintf (stderr, "Invalid Command\n");
				continue;
			case '?' : case 'h' : case 'H' :
				printf ("Type any name to add to list\n"
					"-r<name> to remove from list\n"
					"\'-d\' to display all list items\n"
					"\'-f\' to print the first item in list\n"
					"\'-l\' to print the last item in list\n"
					"\'-n\' to print the next list item\n"
					"\'-p\' to print the previous list item\n"
					"\'.\' to repeat last command\n"
					//"\'-s\' to sort list items\n"
					"\'-e\' to exit\n");
				break;
			case 'd' : case 'D' :
				print_list (ld);
				break;
			case 'f' : case 'F' :
				if (read_first (ld, str)) PRINT_MSG
			case 'l' : case 'L' :
				if (read_last (ld, str)) PRINT_MSG
			case 'n' : case 'N' :
				if (read_next (ld, str)) PRINT_MSG
			case 'p' : case 'P' :
				if (read_prev (ld, str)) PRINT_MSG
			case 'r' : case 'R' :
				if (delete (ld, ++str)) {
					fprintf (stderr, "%s not on list\n", str);
					continue;
				} else printf ("%s removed\n", str);
				break;
			case 'e' : case 'E' :
				print_list (ld);
				close_list (ld);
				printf ("===> End of App <===\n");
				exit (0);
			}
		}
	}
}
