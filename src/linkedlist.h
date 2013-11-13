#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct {
	void * elem;
	struct lnode * next;
} lnode;

void push(lnode * list, void * newElem);

void * get(lnode * list, int i);

int size(lnode * list);

void lremove(lnode * list, int i);

#endif