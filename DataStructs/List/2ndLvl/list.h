struct item {
	struct item *bigger;
	struct item *smaller;
	char data[1];
};

typedef struct {
	struct item *smallest;
	struct item *biggest;
	struct item *trans;
	int ntrans;
	int nitems;
	int size;
	int (*compare)(char *, char*);
} LIST;

# define Smaller (Trans->smaller)
# define Bigger (Trans->bigger)
# define Data (Trans->data)
# define Smallest (ld->smallest)
# define Biggest (ld->biggest)
# define Trans (ld->trans)
# define Size (ld->size)
# define Ntrans (ld->ntrans)
# define Nitems (ld->nitems)
# define Compare (ld->compare)

# define L_SUCCESS 0
# define L_FAILURE 1

LIST *open_list (int size, int (*compare)(char *, char *));
int insert (LIST *ld, char *data);
char *read_current (LIST *ld);
char *read_smallest (LIST *ld);
char *read_biggest (LIST *ld);
char *read_smaller (LIST *ld);
char *read_bigger (LIST *ld);
int delete (LIST *ld, char *data);
void close_list (LIST *ld);
