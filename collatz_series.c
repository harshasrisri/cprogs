# include <stdio.h>
# include <stdlib.h>

#define LIMIT 1000000

struct peak {
	unsigned int num;
	unsigned int length;
};

struct peak peaks[1000];
short lengths[LIMIT];
unsigned int max_peak;

void find_peaks () {
	unsigned int i, cur_len;
	unsigned long long j;

	for (i = 2; i < LIMIT; i++) {
		j = i;
		cur_len = 0;

		while (j > 1) {
			if (j < LIMIT && lengths[j] > 0) {
				cur_len += lengths[j];
				break;
			}

			if (j & 1)
				j += (j << 1) + 1;
			else
				j >>= 1;

			cur_len++;
		}

		lengths[i] = cur_len;

		if (cur_len > peaks[max_peak].length) {
			max_peak++;
			peaks[max_peak].num = i;
			peaks[max_peak].length = cur_len;
		}
	}
}

unsigned int find_max_below (unsigned int num) {
	unsigned int low = 0, mid;
	unsigned int high = max_peak;

	while (high >= low) {
		mid = (high + low) >> 1;
		if (num == peaks[mid].num) {
			low = mid;
			break;
		}

		else if (num > peaks[mid].num)
			low = mid + 1;

		else high = mid - 1;
	}
	return peaks[low-1].num;
}

int main (int argc, char **argv) {
	unsigned int num;

	find_peaks();
	
	while ((*++argv) && (num = atoi(*argv)))
		printf ("%u\n", find_max_below (num));

	return 0;
}
