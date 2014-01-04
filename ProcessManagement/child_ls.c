/**************************************
Prog to run 'ls -l' as its child proc
**************************************/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

int main (int argc, char **argv) {
	switch (fork()) {
		case -1:
			fprintf (stderr, "Could not fork!\n");
			exit (1);
		case 0:
			execl ("/bin/ls", "ls", "-l", NULL);
			exit(0);
		default:
		    printf ("This is the parent process\n");
		    break;
    }
    wait(NULL);
    return 0;
}
