#include <stdio.h>
#include <stdlib.h>

#include <linkedlist.h>

void push(lnode * list, void * newElem) {
	if(list->elem == NULL)
		list->elem = newElem;
	else {
		if(list->next == NULL)
			list->next = (lnode *) malloc(sizeof(lnode));
		push(list->next, newElem);
	}
}

void * get(lnode * list, int i) {
	if(i == 0)
		return list->elem;
	else
		return get(list->next, i-1);
}

int size(lnode * list) {
	int count = (list->elem != NULL) ? 1 : 0;
	lnode * tmp = list;
	while(tmp->next != NULL) {
		count++;
		tmp = tmp->next;
	}
	return count;
}

void lremove(lnode * list, int i) {
	if(i == 1) {
		lnode * tmp = list->next;
		list->next = ((lnode *) list->next)->next;
		free(tmp);
	} else
		lremove(list->next, i-1);
}
