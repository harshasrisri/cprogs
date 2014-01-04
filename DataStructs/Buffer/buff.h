typedef struct {
	int nmax;
	int nitems;
	char *wrt;
	char *rd;
	char *end;
	char beg[1];
} BUFF;

# define Nmax (bd->nmax)
# define Wrt (bd->wrt)
# define Rd (bd->rd)
# define End (bd->end)
# define Beg (bd->beg)
# define Nitems (bd->nitems)
# define BUFF_FULL 1
# define BUFF_SUCCESS 0
# define buff_full(bd) (Nitems == Nmax)
# define buff_empty(bd) (!Nitems)

BUFF *open_buff (int nmax);
int wrt_buff (BUFF *bd, char data);
char rd_buff (BUFF *bd);
void close_buff (BUFF *bd);
