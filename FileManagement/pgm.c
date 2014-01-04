# include <stdio.h>
#include <fcntl.h>
# include <unistd.h>

int main () {
	int fp, i; char c = 'c';
	
	fp = open ("tmpfile", O_CREAT);
	for (i = 0; i < 10000; i++)
		write (fp, &c, 1);
	close (fp);
	unlink ("tmpfile");
	return 0;
}
