# include "tree.h"
# include <stdlib.h>
# include <string.h>

/* ******************************************* *
 * ************ General functions ************ *
 * ******************************************* */
TREE *open_tree (int size, int (*compare)()) {
	register TREE *td;

	td = (TREE *) malloc (sizeof (TREE));
	Size = size;
	Compare = compare;
	return td;
}

int how_many (register struct node *node) {
	if (!node) return 0;
	if (!Left) return 1;
	return (how_many(Left) + how_many(Right));
}

int navigate (TREE *td, void (*action)(), void *app_data) {
	traverse (Root, action, app_data);
	return T_SUCCESS;
}

void traverse (struct node *node, void (*action)(), void *app_data) {
	if (!node) return;
	if (!Left) (*action) (Data, app_data);
	else {
		traverse (Left, action, app_data);
		traverse (Right, action, app_data);
	}
}

void free_tree (struct node *node) {
	if (!node) return;
	if (Left) free_tree (Left);
	if (Right) free_tree (Right);
	if (node) free (node);
}

char find_leaf (TREE *td, char *data) {
	struct node *node;

	for (node = Root; node; ) {
		if (Compare (Data, data) < 0) {
			node = Left;
			continue;
		} else if (Compare (Data, data) > 0) {
			node = Right;
			continue;
		} else return T_SUCCESS;
	}
	return T_FAILURE;
}

/* ******************************************* *
 * ************ Removal functions ************ *
 * ******************************************* */
char remove_leaf (TREE *td, char *data) {
	int nol;
	int n, counter = 0;

	if (!find_leaf (td, data)) return T_FAILURE;

	n = nol = tree_to_array (td);
	for (Pos = Array; nol; nol--, Pos += Size)
		if (!Compare (Pos, data)) break;

	while (nol - 1) {
		*(int *)Pos = *(int *) (Pos + Size);
		Pos += Size;
		nol--;
	}

	Root = array_to_tree (Array, Size, n-1, &counter);
	free (Array);
	return T_SUCCESS;
}

/* ******************************************* *
 * *********** Addition functions ************ *
 * ******************************************* */
int add_leaf (TREE *td, char *new_data) {
	void place_leaf (char *, void *);
	int n, counter = 0;

	n = how_many(Root);
	Array = malloc (++n * Size);
	Pos = Array; 
	New_data = new_data;
	Leaf_added = 0;

	traverse (Root, place_leaf, (void *) td);
	if (!Leaf_added) memcpy (Pos, New_data, Size);
	free_tree (Root);
	Root = array_to_tree (Array, Size, n, &counter);
	free (Array);
	return T_SUCCESS;
}

void place_leaf (char *old, void *x) {
	register TREE *td = (TREE *) x;
	if ((!Leaf_added) && (Compare (New_data, old) > 0)) {
		memcpy (Pos, New_data, Size);
		Pos += Size;
		Leaf_added = 1;
	}
	memcpy (Pos, old, Size);
	Pos += Size;
}

/* ******************************************* *
 * ******** Array <-> Tree functions ********* *
 * ******************************************* */
struct node *array_to_tree (char *array, int size, int n, int *pcounter) {
	register struct node *node;
	int nleft = n/2;

	node = (struct node *) malloc (sizeof (*node) + size - 1);
	if (n == 1) {
		memcpy (Data, array, size);
		Left = Right = NULL;
		return node;
	}

	if ((n & 1) && (++*pcounter & 1)) nleft++;

	Left = array_to_tree (array, size, nleft, pcounter);
	Right = array_to_tree (array + (nleft * size), size, n-nleft, pcounter);
	memcpy (Data, array + (nleft-1) * size, size);
	return node;
}

void copy_leaf_to_array (char *old, void *x) {
	register TREE *td = (TREE *) x;
	memcpy (Pos, old, Size);
	Pos += Size;
}

int tree_to_array (TREE *td) {
	void copy_leaf_to_array(char*, void*);
	int n;

	n = how_many (Root);
	Array = malloc (n * Size);
	Pos = Array;
	traverse (Root, copy_leaf_to_array, (void *)td);
	return n;
}
