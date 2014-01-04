struct item {
	struct item *next;
	struct item *prev;
	char data[1];
};

typedef struct {
	struct item *first;
	struct item *last;
	struct item *trans;
	int ntrans;
	int nitems;
	int dir;
} LIST;

# define Prev (Trans->prev)
# define Next (Trans->next)
# define Data (Trans->data)
# define First (ld->first)
# define Last (ld->last)
# define Trans (ld->trans)
# define Ntrans (ld->ntrans)
# define Nitems (ld->nitems)
# define Dir (ld->dir)

# define L_SUCCESS 0
# define L_FAILURE 1
# define FWD 0
# define REV 1

LIST *open_list ();
int append (LIST *ld, char *data);
int read_first (LIST *ld, char *data);
int read_last (LIST *ld, char *data);
int read_prev (LIST *ld, char *data);
int read_next (LIST *ld, char *data);
int delete (LIST *ld, char *data);
void close_list (LIST *ld);
