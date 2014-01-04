# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define Prev (this->prev)
# define Next (this->next)
# define Data (this->data)
			
struct item {
	struct item *prev;
	struct item *next;
	char data[1];
};

void print_list (struct item *this) {

	for ( ; this; this = Next)
		printf ("%s ", Data);
	putchar ('\n');
	return;
}

int main () {
	struct item *this, *first, *last, *temp;
	char line[40], *str;
	int items = 0, del = 0;

	this = first = last = temp = NULL;
	printf ("Type \'-h\' or \'-?\' for help\n");
	while (1) {
		printf ("list> ");
		fgets (line, 40, stdin);
		for (str = line; *str == ' ' || *str == '\t'; str++)
			;
		str[strchr(str, '\n') - str] = '\0';

		switch (*str) {
		case '\0' : continue;
		default :
			if (!items) {
				this = (struct item *) malloc (
							sizeof (struct item) + strlen (str) );
				Prev = NULL;
				first = this;
			} else {
				Next = (struct item *) malloc (
							sizeof (struct item) + strlen (str) );
				temp = this;
				this = Next;
				Prev = temp;
			}
			last = this;
			Next = NULL;
			strcpy (Data, str);
			items++;
			break;

		case '-' :
			switch (*++str) {
				default :
					fprintf (stderr, "Invalid command\n");
					break;
				case 'h' : case '?' : case 'H' :
					printf ("Type any name to add to list\n"
						"-r<name> to remove from list\n"
						"\'-p\' to print list items\n"
						"\'-s\' to sort list items\n"
						"\'-b\' to print debug report\n"
						"\'-e\' to exit\n");
					break;
				case 'p' : case 'P' :
					print_list (first);
					break;
				case 's' : case 'S' :
					//sort_list (first);
					break;
				case 'b' : case 'B' :
					temp = this;
					if (items) {
						int i = 1;
						for (this = first; this; this = Next, i++)
							printf ("%d\t%s\t%p\t%p\t%p\n", 
										i, Data, Prev, this, Next);
					}
					this = temp;
					break;
				case 'e' : case 'E' :
					print_list (first);
					printf ("===>End of App<===\n");
					exit(0);
				case 'r' : case 'R' :
					if (!(*++str)) continue;
					temp = this;
					for (this = first; this; this = Next)
						if (!strcmp (str, Data)) {
							if ( this == first ) {
								first = Next;
								if ( first )
									 first->prev = NULL;
								else last = NULL;
							} else if ( this == last ) {
								last = Prev;
								if ( last )
									 last->next = NULL;
								else first = NULL;
							} else {
								Prev->next = Next;
								Next->prev = Prev;
							}
							items--;
							printf ("%s removed\n", Data);
							free (this);
							del = 1;
							break;
						} 
					if (!del) this = temp;
					break;
			}
		}
	}
}
