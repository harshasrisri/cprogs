# include <stdio.h>

int main()
{
	int c,flag=0;
	char src[50], *s;
	s = src;
	printf("enter string\n");
	while ((c = getchar ()) != EOF)
	{
	 	*s = c; s++;
		if (c == 'u') flag = 1;
		if ( flag == 1 && c == 'n' && c == 'i' && c == 'x' )
			flag = 1;
		else {flag = 0; continue;}
	}
	*s = '\0';
	if ( flag == 1 ) printf("\n %s is a valid string \n", src);
	else printf("\ntry again\n");
	return 0;
}
