//C Programming Test
// Written by J. Seo (2012.4)

#include <stdio.h>
#include <stdlib.h>

extern void test_main(void);

static unsigned int station[10000][2]; // [0]: destination, [1]: cargo ton

static unsigned int train_pos;
static unsigned int train_dest;


static void build_station(void)
{
	int c;
	for (c = 0; c < 10000; )
	{
		station[c][0] = rand() % 10000;     // destination
		station[c][1] = 1 + (rand() % 100); // cargo ton

		if (station[c][0] != c) c++;
	}

	train_pos = 0; // start station
}


void move_train(unsigned int dest)
{
	train_pos = dest;
}


void get_cargo(unsigned int* dest, unsigned int* ton)
{
	*dest = station[train_pos][0];
	*ton  = station[train_pos][1];
}


void load_cargo(void)
{
	train_dest = station[train_pos][0];

	if (station[train_pos][1] <= 50)
		station[train_pos][1] = 0;
	else
		station[train_pos][1] -= 50;
}


void unload_cargo(void)
{
	train_dest = 0;
}


void main(void)
{
	build_station();
	printf ("%u", test_main());
}
