# include "stack.h"
# include <stdlib.h>
# include <string.h>

STACK *open_stack (int size, int nmax) {
	register STACK *sd;

	if ((nmax < 0) || (size < 0)) return NULL;

	sd = (STACK *) malloc (sizeof (*sd));
	if (!nmax) {
		sd->dyn = 1;
		nmax = 20;
	} else sd->dyn = 0;
	sd->beg = malloc (nmax * size);
	sd->sp = sd->beg;
	sd->nmax = nmax;
	sd->size = size;
	sd->end = sd->beg + nmax * size;
	return sd;
}

int push (STACK *sd, char *item) {

	if (stack_full(sd)) {
		if (sd->dyn) {
			int tmp;
	
			tmp = sd->sp - sd->beg;
			sd->beg = realloc (sd->beg, sd->nmax += 20);
			sd->sp = sd->beg + tmp;
		}
		else return S_FULL;
	}
	memcpy (sd->sp, item, sd->size);
	sd->sp += sd->size;
	return 0;
}

int pop (STACK *sd, char *item) {

	if (stack_empty(sd)) return S_EMPTY;
	sd->sp -= sd->size;
	memcpy (item, sd->sp, sd->size);
	return 0;
}

int peek (STACK *sd, char *item) {

	if (stack_empty(sd)) return S_EMPTY;
	item = sd->sp - sd->size;
	return 0;
}
