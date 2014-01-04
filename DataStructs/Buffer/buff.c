# include "buff.h"
# include <stdlib.h>
# include <string.h>

BUFF *open_buff (int nmax) {
	register BUFF *bd;

	if (nmax < 0) return NULL;
	
	bd = (BUFF*) malloc (sizeof (BUFF) + nmax - 1);
	Nitems = 0;
	Nmax = nmax;
	Wrt = Rd = Beg;
	End = Beg + nmax;
	return bd;
}

int wrt_buff (BUFF *bd, char data) {
	
	if (buff_full(bd)) return BUFF_FULL;
	*Wrt++ = data;
	if (Wrt >= End) Wrt = Beg;
	Nitems++;
	return BUFF_SUCCESS;
}

char rd_buff (BUFF *bd) {

	int data = *Rd++;
	Nitems--;
	if (Rd >= End) Rd = Beg;
	return data;
}

void close_buff (BUFF *bd) {

	free (bd);
}
