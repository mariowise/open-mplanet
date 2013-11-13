
#include <stdio.h>
#include <stdlib.h>
#include <arraylist.h>

void * array_push(void * list, int * size, int newInt) {
	list = realloc(list, sizeof(int) * (*size+1));
	((int *) list)[*size] = newInt;
	size[0]++;
	return list;
}

void * array_remove(void * list, int * size, int it) {
	void * tmp = (void *) malloc(sizeof(int) * (*size-1));
	int i, j = 0;
	for(i = 0; i < *size; i++) {
		if(i != it)
			((int *)tmp)[j++] = ((int *) list)[i];
	}
	free(list);
	list = tmp;
	(*size)--;
	return list;
}

void array_print(void * list, int size) {
	int i;
	printf("(");
	for(i = 0; i < size; i++) {
		printf("%d", ((int *) list)[i]);
		if(i != (size-1))
			printf(", ");
	}
	printf(")\n");
}

