# include <stdio.h>

int main () {
	unsigned int num, i, j = 2 * sizeof (int);
	char hex[2*sizeof(int)+1];
	char hexnum[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	printf ("enter the decimal number\n");
	scanf ("%d",&num);
	printf ("the original and converted hex versions of the entered decimal numbers are %x and ", num);
	for (i = 0; i < j; i++) hex[i] = '0';
	while (num > 0) {
		i = num % 16;
		num = num / 16;
		hex[j] = hexnum [i];
		j--;
	}
	hex[2*sizeof (int) + 1] = '\0';
	printf ("%s\n", hex);
	return 0;
}
