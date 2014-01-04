/*=====================================
  C File to simulate Shell Behavior
  =====================================*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>

char **path;

char **process_line (char *, char);
char *which (char *);
void *clean_up (char **);

int main (int argc, char **argv) {
	char *cmd_path, cmd_line[50], *line;
	char **cmd = NULL;
	int c;

	path = process_line ("/bin/:/sbin/:/usr/bin/:/usr/sbin/:/usr/local/bin/:/usr/local/sbin/:",':');

	while (1) {
		printf ("mysh$ ");
		line = cmd_line;

		while ((c = getchar ())) {
			if (c == '\n') {
				*line = '\0';
				break;
			}
			if (c == EOF) {
				fprintf (stderr, "Logout\n");
				exit (0);
			}
			*line++ = c;
		}

		if (cmd) {
			clean_up (cmd);
		}

		cmd = process_line (cmd_line, ' ');

		if ((cmd_path = which (cmd[0]))) {
			switch (fork()) {
				case 0:
					execv (cmd_path, cmd);
					fprintf (stderr, "Failed to invoke process : %s\n", cmd[0]);
					exit(1);
				case -1:
					fprintf (stderr, "mysh : Failed to fork!\n");
					continue;
				default:
					wait (NULL);
					break;
			}
		} else {
			fprintf (stderr, "mysh : %s : command not found\n", cmd[0]);
		}
	}
	return 0;
}

char **process_line (char *line, char delim) {
	char **sentence = NULL, *temp, *save, c;
	int wc = 0, white = 1;

	temp = (char *) malloc (50);
	save = temp;
	while (1) {
		c = *line++;
		if ((c == delim) || (c == '\n') || (c == '\0')) {
			white = 1;
			if (c == delim) continue;
		} 
		if (white) {
			white = 0;
			if (!(wc % 10)) {
				sentence = (char **) realloc (sentence, (wc + 10) * sizeof (char *));
			}
			*temp = '\0';
			if (*save) {
				temp = save;
				sentence[wc++] = strdup(temp);
			}
			if ((c == '\n') || (c == '\0')) break;
		}
		*temp++ = c;
	}
	if (sentence) {
		sentence[wc + 1] = '\0';
	}
	return sentence;
}

# define PATH (path[path_no])

char *which (char *cmd) {
	char *cmd_path;
	DIR *dir_desc;
	struct dirent *dir_entry;
	int path_no = 0;

	while (PATH) {
		if (!(dir_desc = opendir (PATH))) {
			fprintf (stderr, "\nCould not open : %s", PATH);
			return NULL;
		}

		while ((dir_entry = readdir(dir_desc))) {
			if (strcmp (cmd, dir_entry->d_name)) {
				continue;
			}
			cmd_path = (char *) malloc (strlen (cmd) + strlen (PATH) + 1);
			strcpy (cmd_path, PATH);
			strcat (cmd_path, cmd);
			return cmd_path;
		}
		closedir (dir_desc);
		path_no++;
	}
	return NULL;
}

void *clean_up (char **temp) {
	int count = 0;

	while (temp[count]) {
		free (temp[count++]);
	}
	free (temp[count]);
	free (temp);

	return (void *)temp;
}
