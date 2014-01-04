# include "aqueue.h"
# include <stdlib.h>
# include <string.h>

AQUEUE *openQa (int bytes) {
	register AQUEUE *aqd;
	
	if (bytes <= 0) return NULL;
	aqd = (AQUEUE *) malloc (sizeof (*aqd) + bytes - 1);
	Nbytes = Nfree = bytes;
	Head = Tail = Beg;
	End = Beg + Nbytes;
	return aqd;
}

int enQa (register AQUEUE *aqd, char *data, int size) {
	register int cut_piece;

	if ((size < 1) || (size > 255)) return AQ_ERROR;
	if ((size + 1) > Nfree) return AQ_FULL;
	Nfree -= size + 1;
	*Tail++ = (unsigned char) size;
	if (Tail >= End) Tail = Beg;
	if (size >= End - Tail) {
		cut_piece = End - Tail;
		memcpy (Tail, data, cut_piece);
		Tail = Beg; size -= cut_piece; data += cut_piece;
	}
	if (size) {
		memcpy (Tail, data, size);
		Tail += size;
	}
	return AQ_SUCCESS;
}

int deQa (register AQUEUE *aqd, char *data) {
	register int cut_piece;
	int size;

	if (Nfree == Nbytes) return AQ_EMPTY;
	size = (unsigned char) *Head++;
	Nfree += size + 1;
	if (Head >= End) Head = Beg;
	if (size >= End - Head) {
		cut_piece = End - Head;
		memcpy (data, Head, cut_piece);
		Head = Beg; data += cut_piece; size -= cut_piece;
	}
	if (size) {
		memcpy (data, Head, size);
		Head += size;
	}
	return AQ_SUCCESS;
}

void closeQa (AQUEUE *aqd) {

	free (aqd);
}
