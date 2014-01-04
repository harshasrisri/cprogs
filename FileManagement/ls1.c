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
	printf ("%s ", month[(time_stat->tm_mon)-1]);
	printf ((time_stat->tm_mday < 10) ? "0" : "");
	printf ("%d ", time_stat->tm_mday);
	printf ((time_stat->tm_hour < 10) ? "0" : "");
	printf ("%d:", time_stat->tm_hour);
	printf ((time_stat->tm_min < 10) ? "0" : "");
	printf ("%d ", time_stat->tm_min);
}

void list_files (int flags, char *arg) {
	int len = 100;
	char *old_dir;
	DIR *dp;
	struct dirent *diren;
	struct stat *stats;

	if (!(dp = opendir(arg))) {
		fprintf (stderr, "%s: No such directory\n", arg);
		return;
	}
	while (!getcwd (old_dir, len)) {
		old_dir = realloc (old_dir, len += 100);
		continue;
	}
	if (chdir(arg)) {
		fprintf (stderr, "%s: Could not open directory\n", arg);
		return;
	}

	printf ("%s:\n", arg);
	stats = malloc (sizeof(struct stat));

	while ((diren = readdir(dp)) != NULL) {
		if (stat(diren->d_name, stats)) {
			fprintf (stderr,
				"Could not determine stats for \"%s\"\n", diren->d_name);
			continue;
		}
		if (!(flags & 0x08) && diren->d_name[0] == '.') continue;
		if (flags & 0x02) printf ("%10ld ", stats->st_ino);
		if (flags & 0x01) long_view (stats);
		printf ("%s", diren->d_name);
		printf ((flags & 0x01) ? "\n" : "  ");
	}

	if (flags & 0x04) {
		rewinddir(dp);
		while ((diren = readdir(dp)) != NULL) {
			printf ("\n\n");
			if (stat(diren->d_name, stats)) {
				fprintf (stderr,
					"Could not determine stats for \"%s\"\n", diren->d_name);
				continue;
			}
			if (!(S_IFDIR & stats->st_mode)) 
				continue;
			if (!strcmp(diren->d_name, ".") || !strcmp(diren->d_name, "..")) 
				continue;
			list_files (flags, diren->d_name);
		}
	}
	free (stats);
	closedir(dp);
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
