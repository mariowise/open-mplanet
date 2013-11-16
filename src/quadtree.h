#ifndef QUADTREE_H_
#define QUADTREE_H_

typedef struct _qnode {
	int cant;
	int * objects;

	double mass;
	point2D massCentre;

	point2D anchor;
	double ratio;

	struct qnode * parent;

	struct _qnode * NW;
	struct _qnode * NE;
	struct _qnode * SW;
	struct _qnode * SE;
} qnode;

qnode * tree;
qnode nextTree;
double Threshold;

qnode * quadtree_init();

void quadtree_destroy(qnode * node);

void quadtree_build(qnode * node);

void quadtree_print(qnode * node, int base);

void quadtree_barnes_hut(qnode * T, int Ci);

#endif