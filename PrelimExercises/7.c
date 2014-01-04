# include <stdio.h>

int main ()
{
	int c, flag = 0, comment = 0;
	char src[250],*s;
	s = src;
	printf("enter the string\n");
	while ((c = getchar ()) != EOF)
	{
		*s = c;
		if (comment == 0 && c == '/') 
		{
			flag = 1;
			s++;	
			continue;
		}
		if (comment == 0 && flag == 1 && c == '*')
		{
			*s = '/';
			s++;
			flag = 0;
			comment = 1;
			continue;
		}
		if (comment == 1 && c == '\n') 
		{
			s++;*s = '/';
			s++;*s = '/';
		}
		if (comment == 1 && c == '*') 
		{
			flag = 1;
			s++;
			continue;
		}
		if (comment == 1 && flag == 1 && c == '/')
		{
			s--;
			*s = '\n';
			flag = 0;
			comment = 0;
		}
		s++;
	}
	*s = '\0';
	printf("\nthe modified string is:\n%s\n",src);
	return 0;
}
