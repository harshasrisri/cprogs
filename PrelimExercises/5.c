# include <stdio.h>
# include <string.h>

void Rprint (char *in, char *out, int count)
{
	int i, l;
	char *out1;
	l = strlen ( in );
	for(i = 0;i < count; i++) 
	{
		out = in + l - count + i + 1;
		printf ("%c",*out);
	}
	printf("\n");
	*out = '\0';
}

void Lprint (char *in, char *out, int count)
{
	int i, l;
	for(i = 0;i < count; i++) 
	{
		printf ("%c",* ( in + i));
		out = in + i;
	}
	printf("\n");
	*out = '\0';
}

void Mprint (char *in, char *out, int count, int z)
{
	int i;
	for(i = 0;i < count; i++) 
	{
		printf ("%c",*( in + z + i));
		out = in + z + i;
	}
	printf ("\n");
	*out = '\0';
}

void Xcopy (char *in, char *out, int count, int posi, int offset)
{
	switch (offset)
	{
	case 0 :	printf("the modified string is\n");
				Rprint(in, out, count);
				break;
				
	case 1 :	printf("the modified string is\n");
				Lprint(in, out, count);
				break;
				
	case 2 :	printf("the modified string is\n");
				Mprint(in, out, count, posi);
				break;
				
	default :	printf("enter valid offset and try again!\n");
				exit(0);
				
	}
}
int main()
{
	int c, cnt, pos, offset;
	char src[50], *s, dst[50];
	s = src;
	printf ("enter the string\n");
	while ((c = getchar ()) != EOF)
	{
		*s = c;
		s++;
	}
	*s = '\0';
	printf("\nenter the count, position and offset values\n");
	scanf ("%d%d%d", &cnt, &pos, &offset);
	Xcopy(src,dst,cnt,pos,offset);
	printf("%s",dst);
	return 0;
}
