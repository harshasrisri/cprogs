#include "prime.h"

struct thread_info {
	pthread_t thread_id;
	int thread_count;
	int skip;
	int thread_num;
	PRIME *prime_handle;
};

/* declare a mutex lock variable here */

int calculate_thrd_cnt (ull limit) {
	if (limit > 1000000000000000) return 6;
	if (limit > 1000000000000) return 5;
	if (limit > 1000000000) return 4;
	if (limit > 1000000) return 3;
	if (limit > 1000) return 2;
	if (limit > 1) return 1;
	return -1;
}

inline int checkbit (PRIME *handle, unsigned int pos) {
	char *array = handle->primes;

	if (pos == 0) return 0;
	if (pos == 1) return 0;
	if (pos == 2) return 0;
	if (!(pos & 1)) return 1;
	pos = pos >> 1;
	return (array[pos / (sizeof(array[0]) * 8)]) & (1 << (pos % (sizeof(array[0]) * 8)));
}

inline void setbit (PRIME *handle, unsigned int pos) {
	char *array = handle->primes;
	pos = pos >> 1;
	(array[pos / (sizeof(array[0]) * 8)]) |= (1 << (pos % (sizeof(array[0]) * 8)));
	return;
}

void *process_primes (void *thread_data) {
	struct thread_info *thread = (struct thread_info *) thread_data;
	PRIME *handle = thread->prime_handle;
	ull i, j, temp;

	for (i = 3 + 2 * thread->thread_num; i <= handle->limit; i += thread->skip) {
		if (is_not_prime (handle, i)) continue;

		if (i < handle->highest) continue;
		/* mutex_lock_function_here */
		handle->highest = i;
		handle->count++;
		/* mutex_unlock_function_here */

		j = 2;
		while ((temp = i * j++) < handle->limit)
			setbit (handle, temp);
	}
}

PRIME *prepare_primes (ull limit) {
	int thrd_cnt, s, i;
	void *result;
	struct thread_info *threads;
	PRIME *handle;
	pthread_attr_t attr;

	s = pthread_attr_init (&attr);

	if ((thrd_cnt = calculate_thrd_cnt (limit)) < 0) return NULL;

	handle = (PRIME *) malloc (sizeof (PRIME));

	handle->primes = (char *) calloc (limit/2/8 + 1, 1);
	handle->count = handle->highest = 2;
	handle->limit = limit;

	threads = (struct thread_info *) malloc (thrd_cnt * sizeof (struct thread_info));

	for (i = 0; i < thrd_cnt; i++) {
		threads[i].thread_count = thrd_cnt;
		threads[i].skip = thrd_cnt * 2;
		threads[i].thread_num = i;
		threads[i].prime_handle = handle;
		s = pthread_create (&threads[i].thread_id, &attr, &process_primes, (void *)(&threads[i]));
	}

	s = pthread_attr_destroy (&attr);

	for (i = 0; i < thrd_cnt; i++) {
		s = pthread_join (threads[i].thread_id, &result);
		free(result);
	}

	free ( threads);
	return handle;
}
