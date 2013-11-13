#ifndef QUADTREE_H_
#define QUADTREE_H_

typedef struct {
	int cant;
	int * objects;

	double mass;

	point2D anchor;
	double ratio;

	struct qnode * parent;

	struct qnode * NW;
	struct qnode * NE;
	struct qnode * SW;
	struct qnode * SE;
} qnode;

qnode tree;

void quadtree_init();

void quadtree_build(qnode * node);

#endif