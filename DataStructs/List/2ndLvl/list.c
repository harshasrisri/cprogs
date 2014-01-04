# include "list.h"
# include <string.h>
# include <stdlib.h>

LIST *open_list (int size, int (*compare)(char *, char*)) {
	register LIST *ld;
	ld = (LIST *) malloc (sizeof (LIST));
	if (!ld) return NULL;
	Smallest = Biggest = Trans = NULL;
	Ntrans = 0;
	Nitems = 0;
	Compare = compare;
	Size = size;
	return ld;
}

int insert (register LIST *ld, char *data) {
	struct item *temp;

	Trans = (struct item *) malloc (sizeof (struct item) + Size - 1);
	if (!Trans)
		return L_FAILURE;
	memcpy (Data, data, Size);

	if (!Nitems) {
		Smallest = Biggest = Trans;
		Smaller = Bigger = NULL;
	} else if ((*Compare)(Data, Smallest->data) <= 0) {
		Bigger = Smallest; Smaller = NULL;
		Smallest->smaller = Trans; Smallest = Trans;
	} else if ((*Compare)(Data, Biggest->data) >= 0) {
		Smaller = Biggest; Bigger = NULL;
		Biggest->bigger = Trans; Biggest = Trans;
	} else {
		for (temp = Smallest; (*Compare)(Data, temp->bigger->data) >=0; 
														temp = temp->bigger);
		Bigger = temp->bigger; Smaller = temp;
		temp->bigger->smaller = Trans; temp->bigger = Trans;
	}
	Nitems++; Ntrans++;
	return L_SUCCESS;
}

char *read_smallest (LIST *ld) {

	if (!Nitems) return NULL;
	if (Smallest) {
		Trans = Smallest;
		Ntrans++;
		return Data;
	} else return NULL;
}

char *read_biggest (LIST *ld) {

	if (!Nitems) return NULL;
	if (Biggest) {
		Trans = Biggest;
		Ntrans++;
		return Data;
	} else return NULL;
}

char *read_smaller (LIST *ld) {

	if (!Nitems) return NULL;
	if (Smaller) {
		Trans = Smaller;
		Ntrans++;
		return Data;
	} else return NULL;
}

char *read_bigger (LIST *ld) {

	if (!Nitems) return NULL;
	if (Bigger) {
		Trans = Bigger;
		Ntrans++;
		return Data;
	} else return NULL;
}

char *read_current (LIST *ld) {

	if (!Nitems) return NULL;
	if (Trans) {
		Ntrans++;
		return Data;
	} else return NULL;
}

int delete (LIST *ld, char *data) {
	for (Trans = Smallest; Trans; Trans = Bigger)
		if ((*Compare)(Data, data) == 0) {
			if (Trans == Smallest) {
				Smallest = Bigger;
				if (Smallest)
					 Smallest->smaller = NULL;
				else Biggest = NULL;
			} else if (Trans == Biggest) {
				Biggest = Smaller;
				if (Biggest)
					 Biggest->bigger = NULL;
				else Smallest = NULL;
			} else {
				Smaller->bigger = Bigger;
				Bigger->smaller = Smaller;
			}
			Nitems--;
			Ntrans++;
			free (Trans);
			Trans = Biggest;
			return L_SUCCESS;
		} 
	return L_FAILURE;
}

void close_list (LIST *ld) {

	if ((Trans = Smallest))
		for (Trans = Bigger; Trans; Trans = Bigger)
			if (Smaller)
				free (Smaller);
	free (ld);
}
