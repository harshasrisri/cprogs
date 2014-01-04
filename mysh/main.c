/*=====================================
  C File to fork a new process in MY Shell
  =====================================*/

# include <header.h>

char **path = 0;
int path_count = 0;

int main (int main_argc, char **main_argv) {
	char *cmd_path;
	char **argv = NULL;
	int argc, i;

	path_count = line_2_words (&path, CMD_PATHS,':');

	/* for (i = 0; i < path_count; i++) */
	/* 	printf ("%d : %s\n", i, path[i]); */

	while (1) {
		printf ("mysh$ ");

		if (argv)
			argv = free_up (argc, argv);

		if (!(argc = line_2_words (&argv, get_cmd (), ' '))) {
			continue;
		}

		if ((cmd_path = which (argv[0]))) {
			switch (fork()) {
				case 0:
					execv (cmd_path, argv);
					fprintf (stderr, "Failed to invoke process : %s\n", argv[0]);
					continue;
				case -1:
					fprintf (stderr, "mysh : Failed to fork!\n");
					continue;
				default:
					wait (NULL);
					break;
			}
		} else {
			fprintf (stderr, "mysh : %s : command not found\n", argv[0]);
		}
	}
	return 0;
}

char **free_up (int argc, char **argv) {

	argc--;
	do {
		if (argv[argc])
			free (argv[argc]);
	} while (argc--);
	if (argv)
		free (argv);
	return NULL;
}
