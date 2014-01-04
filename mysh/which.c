/*=====================================
  C File to search for executable in Path
  =====================================*/

# include <header.h>

# define PATH (path[path_no])

char *which (char *cmd) {
	char *cmd_path = NULL;
	DIR *dir_desc;
	struct dirent *dir_entry;
	int path_no = 0;
	int cmd_found = 0;

	if (!path) {
		fprintf (stderr, "Path not set!\n");
		return NULL;
	}

	while (path_no < path_count) {
		if (!(dir_desc = opendir (PATH))) {
			/* fprintf (stderr, "\nCould not open : %s", PATH); */
			/* break; */
		}

		while ((dir_entry = readdir(dir_desc))) {
#ifdef CYGWIN
			if (strncmp (cmd, dir_entry->d_name, strlen(cmd))) {
#else
			if (strcmp (cmd, dir_entry->d_name)) {
#endif
				continue;
			}
			cmd_path = (char *) malloc (strlen (cmd) + strlen (PATH) + 1);
			strcpy (cmd_path, PATH);
			strcat (cmd_path, cmd);
			cmd_found = 1;
		}
		closedir (dir_desc);
		if (cmd_found)
			return cmd_path;
		path_no++;
	}
	return NULL;
}

