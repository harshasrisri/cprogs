/**************************************
  C File Purpose and Description Here
**************************************/

# include <stdio.h>
# include <unistd.h>

int main (int argc, char **argv) {
	//printf ("%d ", getpid());
	printf ("%s ", (fork() ? "Parent" : "Child"));
	printf ("%d\n", getpid());
	//printf ("%d ", getpid());
	printf ("%s ", (fork() ? "Parent" : "Child"));
	printf ("%d\n", getpid());
	return 0;
}
