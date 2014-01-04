typedef struct {
	int nmax;
	int size;
	int nitems;
	int dyn;
	char *ep;
	char *dp;
	char *end;
	char beg[1];
} QUEUE;

# define Nmax (qd->nmax)
# define Size (qd->size)
# define Nitems (qd->nitems)
# define Dyn (qd->dyn)
# define Ep (qd->ep)
# define Dp (qd->dp)
# define End (qd->end)
# define Beg (qd->beg)
# define Q_FULL 1
# define Q_EMPTY 1
# define Q_SUCCESS 0
# define queue_full(qd) (Nitems == Nmax)
# define queue_empty(qd) (Nitems == 0)

QUEUE *open_queue (int size, int nmax);
int enQ (QUEUE *qd, char *data);
int deQ (QUEUE *qd, char *data);
void close_queue (QUEUE *qd);
