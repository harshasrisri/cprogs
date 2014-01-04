/*=====================================
  C header file for MY Shell Program
  =====================================*/

# ifndef SH_HEAD_DEF
# define SH_HEAD_DEF

# define MAX_LINE_SIZE 1024

# define CMD_PATHS "/bin/:/sbin/:/usr/bin/:/usr/sbin/:/usr/local/bin/:/usr/local/sbin/:"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>

int line_2_words (char ***, char *, char);
char *which (char *);
void kick_start (void);
char *get_cmd (void);
char **free_up (int, char **);

extern char **path;
extern int path_count;

#endif //SH_HEAD_DEF
