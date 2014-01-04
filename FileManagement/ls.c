# define _GNU_SOURCE
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include <ctype.h>

void print_ids (char *path, int id) {
	FILE *fp;
	char *line = NULL;
	size_t num;
	ssize_t read;

	fp = fopen (path, "r");
	while ((read = getline(&line, &num, fp)) != -1) {
		int i;
		char name[20], *p;

		for ( i = 0, p = line; *p && *p != ':'; p++, i++ )
			name[i] = *p;
		if ( !*p ) continue;
		name[i] = '\0';
		for ( ++p; *p && *p != ':'; p++ ) ;
		if ( !*p ) continue;
		if ( id == atoi (++p) ) {
			printf ( "%s  ", name );
			break;
		}
	}
	if (line) free (line);
	fclose (fp);
}

const char month[12][4] = {
	"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
};

void long_view (struct stat *stats) {
	struct tm *time_stat;

	putchar ((S_IFDIR & stats->st_mode) ? 'd' : '-');
	putchar ((S_IRUSR & stats->st_mode) ? 'r' : '-');
	putchar ((S_IWUSR & stats->st_mode) ? 'w' : '-');
	putchar ((S_IXUSR & stats->st_mode) ? 'x' : '-');
	putchar ((S_IRGRP & stats->st_mode) ? 'r' : '-');
	putchar ((S_IWGRP & stats->st_mode) ? 'w' : '-');
	putchar ((S_IXGRP & stats->st_mode) ? 'x' : '-');
	putchar ((S_IROTH & stats->st_mode) ? 'r' : '-');
	putchar ((S_IWOTH & stats->st_mode) ? 'w' : '-');
	putchar ((S_IXOTH & stats->st_mode) ? 'x' : '-');
	printf ("  ");

	printf ("%4d ", stats->st_nlink);
	print_ids ("/etc/passwd", stats->st_uid);
	print_ids ("/etc/group", stats->st_gid);
	printf ("%10ld ", stats->st_size);

	time_stat = localtime(&(stats->st_ctime));
	printf ("%s ", month[(time_stat->tm_mon)]);
	printf ((time_stat->tm_mday < 10) ? "0" : "");
	printf ("%d ", time_stat->tm_mday);
	printf ((time_stat->tm_hour < 10) ? "0" : "");
	printf ("%d:", time_stat->tm_hour);
	printf ((time_stat->tm_min < 10) ? "0" : "");
	printf ("%d ", time_stat->tm_min);
}

# define LEN	1000

void list_files (int flags, char *curr_dir) {
	int nod = 0;
	char old_dir [LEN];
	DIR *dp;
	struct dirent *diren;
	struct stat *stats;
	char **dlist = NULL;

	if (!(dp = opendir(curr_dir))) {
		fprintf (stderr, "%s: No such file or directory\n", curr_dir);
		return;
	}
	if ( getcwd ( old_dir, LEN ) == NULL ) {
		exit ( 1 );
	}
	if (chdir(curr_dir)) {
		fprintf (stderr, "%s: Could not open directory\n", curr_dir);
		return;
	}

	printf ("%s:\n", curr_dir);
	stats = malloc (sizeof(struct stat));

	while ((diren = readdir(dp))) {
		if (!diren) {
			printf ("\n\n");
			break;
		}
		if (stat(diren->d_name, stats)) {
			fprintf (stderr,
				"Could not determine stats for \"%s\"\n", diren->d_name);
			continue;
		}
		if ((flags & 0x04) && S_ISDIR(stats->st_mode)) {
			if (!strcmp(diren->d_name, ".") || !strcmp(diren->d_name, ".."))
				continue;
			if (!(flags & 0x08) && diren->d_name[0] == '.')
				continue;
			dlist = realloc (dlist, ++nod * sizeof(char *));
			dlist[nod - 1] = strdup (diren->d_name);
		}
		if (!(flags & 0x08) && diren->d_name[0] == '.') continue;
		if (flags & 0x02) printf ("%10ld ", stats->st_ino);
		if (flags & 0x01) long_view (stats);
		printf ("%s", diren->d_name);
		printf ((flags & 0x01) ? "\n" : "  ");
	}
	free (stats);
	closedir(dp);
	if (nod) {
		int i;

		for (i = 0; i < nod; i++) {
			list_files (flags, dlist[i]);
			free (dlist[i]);
		}
	}
	free (dlist);
	chdir ( old_dir );
}

int main (int argc, char **argv) {
	int flags = 0, nof = 0;

	while(*++argv) {
		if (**argv == '-') {
			while (*++*argv) {
				if (**argv == 'l') flags |= 0x01;
				if (**argv == 'i') flags |= 0x02;
				if (**argv == 'R') flags |= 0x04;
				if (**argv == 'a') flags |= 0x08;
			}
			continue;
		}
		else {
			list_files (flags, *argv);
			nof++;
		}
	}
	if (!nof)
		list_files (flags, ".");
	putchar ('\n');
	return 0;
}
