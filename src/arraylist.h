#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_ // STF586687

int * array_push(int * list, int * size, int newInt);

void * array_remove(void * list, int * size, int it);

void array_print(int * list, int size);

int array_find(void * list, int size, int number);

#endif