#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_ // STF586687

void * array_push(void * list, int * size, int newInt);

void * array_remove(void * list, int * size, int it);

void array_print(void * list, int size);

int array_find(void * list, int size, int number);

#endif