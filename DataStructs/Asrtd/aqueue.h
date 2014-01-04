typedef struct {
	char *head;
	char *tail;
	char *end;
	int nbytes;
	int nfree;
	char beg[1];
} AQUEUE;

# define Head (aqd->head)
# define Tail (aqd->tail)
# define End (aqd->end)
# define Beg (aqd->beg)
# define Nbytes (aqd->nbytes)
# define Nfree (aqd->nfree)
# define AQ_ERROR 2
# define AQ_FULL 1
# define AQ_SUCCESS 0
# define AQ_EMPTY 1

AQUEUE *openQa ( int bytes );
int enQa (register AQUEUE *aqd, char *data, int size);
int deQa (register AQUEUE *aqd, char *data);
void closeQa (AQUEUE *aqd);
