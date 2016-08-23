#include "random.h"
#include <stdlib.h>
#include <time.h>

void init_random() {
	srand((unsigned) time(NULL));
}

void populate_array(int *array, int len, int lower, int upper) {
	for(int i = 0; i < len; i++) {
		array[i] = rand() % (upper - lower + 1);
	}
}
