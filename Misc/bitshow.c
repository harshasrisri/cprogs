# include <stdio.h>

int main (int argc, char *argv[]) {
	unsigned int k = 1 << (sizeof(int) * 8 - 1);
	int i;
	sscanf (argv[1], "%d", &i);
	while (k >>= 1) 
		if (i & k) putchar('1');
		else putchar ('0');
	putchar ('\n');
	return 0;
}
