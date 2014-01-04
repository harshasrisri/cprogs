//DO NOT INCLUDE ANY FILEs (EX: STDIO.H, main.cpp)

void move_train(unsigned int dest);
void get_cargo(unsigned int* dest, unsigned int* ton);
void load_cargo(void);
void unload_cargo(void);

#ifndef NUM_STN
#define NUM_STN 10000
#endif

#define POS (sd[t_pos].pos)
#define DEST (sd[t_pos].dest)
#define LOAD (sd[t_pos].load)
#define DIFF (sd[t_pos].diff)

struct station_data {
	unsigned int pos;
	unsigned int dest;
	unsigned int load;
	unsigned int diff;
};

static struct station_data sd[NUM_STN];

static unsigned int serviced_stations = 0, 
					fuel = 0;

void my_move_train (int dest) {
	int temp_diff;

	fuel += ((temp_diff = t_pos - dest) >= 0 ? temp_diff : temp_diff * -1);
	move_train (dest);
	t_pos = dest;
}

void setup_route () {
	int temp_diff, i, temp_dest = 0, loaded = 0;
	int t_pos = 0, t_dst = 0;

	load_cargo ();

	for (i = 0; i < NUM_STN; i++) {
		// move the train to the current index numbered station.
		// In the first station, it moves to the same station and has no effect.
		my_move_train (i);

		// Re-building the station database compatible with this program.
		POS = i;
		get_cargo (&DEST, &LOAD);
		DIFF = (temp_diff = POS - DEST) < 0 ? (temp_diff * -1) : temp_diff;

		// In the first station or if the load is not meant for this station,
		// this line is not executed.
		// If the train is loaded, and if we have approached the destination,
		// we unload the cargo and mark that the train is not loaded.
		(loaded) && (DEST == temp_dest) && (my_unload_cargo ()) && (loaded = 0);

		// In the first station and when the train is moving unloaded, 
		// we set the destination and mark as "to be loaded"
		// If the train is loaded, this line is not executed.
		(!loaded) && (temp_dest = DEST) && (loaded = 1);

		// If the train is marked as "to be loaded" and if we are staying in
		// the same station where we collected the latest destination info, 
		// we have to check if the destination is before or after our position
		// and then load the cargo if it is ahead of us.
		(loaded) && (DEST == temp_dest) && (POS > DEST) ? loaded = 0 : my_load_cargo();
	}
}

void get_next_station () {
	int temp_diff = 0, temp_pos = 0, i;
	int t_pos = 0, t_dst = 0;

	if (!LOAD) {
		t_pos++;
		if (t_pos == NUM_STN)
			t_pos = 0;
		get_next_station ();
		return;
	}

	for (i = POS; i > POS - DIFF; i--) {
		temp_pos = t_pos - i;
		if (temp_pos < 0)
			break;
		if ((temp_diff < i + sd[temp_pos].diff) && (sd[temp_pos].load)) {
			temp_diff = i + sd[temp_pos].diff;
			t_dst = i;
		}
	}

	for (i = POS; i < POS + DIFF; i++) {
		temp_pos = t_pos + i;
		if (temp_pos > NUM_STN)
			break;
		if ((temp_diff < i + sd[temp_pos].diff) && (sd[temp_pos].load)) {
			temp_diff = i + sd[temp_pos].diff;
			t_dst = i;
		}
	}
}

unsigned int test_main(void)
{
	setup_route ();
	while (serviced_stations < NUM_STN) {
		t_dst = DEST;
		get_next_station ();
		if (t_dst != DEST)
			my_move_train (t_dst);
		load_cargo ();
		if (!LOAD) serviced_stations++;
		my_move_train (t_dst);
		unload_cargo ();
	}
	return fuel;
}
