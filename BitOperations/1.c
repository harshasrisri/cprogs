# include <stdio.h>

int main () {

	int num = -1, size = 1;
	while (num <<= 1) size++;
	printf ("size of integer = %d %d \n", size, num);
	return 0;
}
