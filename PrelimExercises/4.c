# include <stdio.h>
# include <string.h>

void Rprint (char *x, int y)
{
	int i, l;
	l = strlen ( x );
	for(i = 0;i < y; i++) printf ("%c",* ( x + l - y + i + 1 ));
	printf("\n");
}

void Lprint (char *x, int y)
{
	int i, l;
	for(i = 0;i < y; i++) printf ("%c",* ( x + i));
	printf("\n");
}

void Mprint (char *x, int y, int z)
{
	int i;
	for(i = 0;i < y; i++) printf ("%c",*( x + z + i));
	printf ("\n");
}

int main()
{
	int c, cnt, pos;
	char src[50], *s;
	s = src;
	printf ("enter the string\n");
	while ((c = getchar ()) != EOF)
	{
		*s = c;
		s++;
	}
	*s = '\0';
	printf("\nenter the count and position values\n");
	scanf ("%d", &cnt);
	scanf ("%d", &pos);
	printf("the modified strings are\n");
	Rprint(src,cnt);
	Lprint(src,cnt);
	Mprint(src,cnt,pos);
	return 0;
}
