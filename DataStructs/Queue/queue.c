# include "queue.h"
# include <stdlib.h>
# include <string.h>

QUEUE *open_queue (int size, int nmax) {
	register QUEUE *qd;

	if ((size < 0) || (nmax < 0)) return NULL;
	
	qd = (QUEUE*) malloc (sizeof (QUEUE) + nmax * size - 1);
	if (!nmax) {
		Dyn = 1;
		nmax = 20;
	} else Dyn = 0;
	Nitems = 0;
	Size = size;
	Nmax = nmax;
	Ep = Dp = Beg;
	End = Beg + size * nmax;
	return qd;
}

int enQ (QUEUE *qd, char *data) {
	
	if (queue_full(qd)) {
		if (Dyn) {
			return Q_FULL;
		}
		else return Q_FULL;
	}
	memcpy (Ep, data, Size);
	Ep += Size;
	if (Ep >= End) Ep = Beg;
	Nitems++;
	return Q_SUCCESS;
}

int deQ (QUEUE *qd, char *data) {

	if (queue_empty(qd)) return Q_EMPTY;
	memcpy (data, Dp, Size);
	Dp += Size;
	if (Dp >= End) Dp = Beg;
	Nitems--;
	return Q_SUCCESS;
}

void close_queue (QUEUE *qd) {

	free (qd);
}
