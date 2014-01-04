# include "list.h"
# include <string.h>
# include <stdlib.h>

LIST *open_list () {
	register LIST *ld;
	ld = (LIST *) malloc (sizeof (LIST));
	if (!ld) return NULL;
	First = Last = Trans = NULL;
	Ntrans = 0;
	Nitems = 0;
	Dir = FWD;
	return ld;
}

int append (register LIST *ld, char *data) {
	struct item *temp;

	if (!Nitems) {
		Trans = (struct item *) malloc (sizeof (struct item) + strlen (data));
		if (!Trans) return L_FAILURE;
		Prev = NULL;
		First = Last = Trans;
	} else {
		Trans = Last;
		Next = (struct item *) malloc (sizeof (struct item) + strlen (data));
		if (!Next) return L_FAILURE;
		temp = Trans;
		Trans = Next;
		Prev = temp;
	}
	Last = Trans; Next = NULL;
	strcpy (Data, data);
	Nitems++; Ntrans++;
	return L_SUCCESS;
}

int read_first (LIST *ld, char *data) {
	if (First) {
		data = First->data;
		Ntrans++;
		Trans = First;
		return L_SUCCESS;
	} else return L_FAILURE;
}

int read_last (LIST *ld, char *data) {
	if (Last) {
		data = Last->data;
		Ntrans++;
		Trans = Last;
		return L_SUCCESS;
	} else return L_FAILURE;
}

int read_prev (LIST *ld, char *data) {

	if (Trans && Prev) {
		Trans = Prev;
		data = Data;
		Ntrans++;
		return L_SUCCESS;
	} else return L_FAILURE;
}

int read_next (LIST *ld, char *data) {

	if (Trans && Next) {
		Trans = Next;
		data = Data;
		Ntrans++;
		return L_SUCCESS;
	} else return L_FAILURE;
}

int delete (LIST *ld, char *data) {
	for (Trans = First; Trans; Trans = Next)
		if (!strcmp (data, Data)) {
			if (Trans == First) {
				First = Next;
				if (First)
					 First->prev = NULL;
				else Last = NULL;
			} else if (Trans == Last) {
				Last = Prev;
				if (Last)
					 Last->next = NULL;
				else First = NULL;
			} else {
				Prev->next = Next;
				Next->prev = Prev;
			}
			Nitems--;
			Ntrans++;
			free (Trans);
			Trans = Last;
			return L_SUCCESS;
		} 
	return L_FAILURE;
}

void close_list (LIST *ld) {

	if (First)
		for (Trans = First, Trans = Next; Trans; Trans = Next)
			if (Prev) free (Prev);
	free (ld);
}
