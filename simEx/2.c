# include <stdio.h>

int main () {
	float i;
	for (i = 300; i >= 0; i--)
		printf ("%3.0f farenheit = %3.3f celsius\n", i, (i - 32) * 5 / 9);
	return 0;
}
