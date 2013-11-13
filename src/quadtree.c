
#include <stdio.h>
#include <stdlib.h>
#include <point2D.h>
#include <universe.h>
#include <arraylist.h>
#include <quadtree.h>

// Procedimiento para inicializar el primer nodo del árbol
void quadtree_init() {
	tree.cant = univ.cant;
	tree.objects = (int *) malloc(sizeof(int) * tree.cant);
	tree.mass = 0.0f;
	int i;
	for(i = 0; i < tree.cant; i++)
		tree.objects[i] = i;
	for(i = 0; i < tree.cant; i++)
		tree.mass += univ.objects[i].mass;

	tree.anchor.x = 0;
	tree.anchor.y = 0;
	tree.ratio = univ.ratio;

	// printf("Árbol inicializado con 5 objetos y una masa de %.3e kilos\n", tree.mass);
}

int control;

// Procedimiento para propagar recursivamente el árbol y construirlo
void quadtree_build(qnode * node) {
	qnode * nw,* ne,* sw,* se;
	// Si el nodo tiene mas de un elemento hay que expandirlo
	if(node->cant > 1) {
		// Se almacenan los nuevos nodos
		node->NW = (qnode *) malloc(sizeof(qnode)); nw = node->NW;
		node->NE = (qnode *) malloc(sizeof(qnode)); ne = node->NE;
		node->SW = (qnode *) malloc(sizeof(qnode)); sw = node->SW;
		node->SE = (qnode *) malloc(sizeof(qnode)); se = node->SE;		

		// New ratios
		nw->ratio = node->ratio / 2;
		ne->ratio = node->ratio / 2;
		sw->ratio = node->ratio / 2;
		se->ratio = node->ratio / 2;

			// NW
			nw->anchor.x = node->anchor.x - nw->ratio;
			nw->anchor.y = node->anchor.y + nw->ratio;

			// NE
			ne->anchor.x = node->anchor.x + ne->ratio;
			ne->anchor.y = node->anchor.y + ne->ratio;

			// SW
			sw->anchor.x = node->anchor.x - sw->ratio;
			sw->anchor.y = node->anchor.y - sw->ratio;

			// SE
			se->anchor.x = node->anchor.x + se->ratio;
			se->anchor.y = node->anchor.y - se->ratio;

		// printf("nw anchor (%.2E, %.2E)\n", nw->anchor.x, nw->anchor.y);
		// printf("NW anchor (%.2E, %.2E)\n", ((qnode *) node->NW)->anchor.x, ((qnode *) node->NW)->anchor.y);

		int i, li;
		printf("\nVector padre tiene ");
		array_print(node->objects, node->cant);
		printf("Anchor= (%.2E, %.2E)\n", node->anchor.x, node->anchor.y);
		for(i = 0; i < node->cant; i++) {

			li = node->objects[i];

			// if(node->objects[i] == 3) {
			// 	printf("\t\tIs %.3E less then %.3E ? %s \n", node->anchor.x, univ.objects[li].pos.x, (node->anchor.x < univ.objects[li].pos.x) ? "true" : "false");
			// }

			if(
				univ.objects[li].pos.x < node->anchor.x && univ.objects[li].pos.y >= node->anchor.y) {
				// NW
					((qnode *) node->NW)->objects = array_push(((qnode *) node->NW)->objects, &((qnode *) node->NW)->cant, node->objects[i]);
					// printf("\tEnviando a NW el objeto nro. %d\n", i);

			} else if(
				univ.objects[li].pos.x >= node->anchor.x && univ.objects[li].pos.y >= node->anchor.y) {
				// NE
					((qnode *) node->NE)->objects = array_push(((qnode *) node->NE)->objects, &((qnode *) node->NE)->cant, node->objects[i]);
					// printf("\tEnviando a NE el objeto nro. %d\n", i);

			} else if(
				univ.objects[li].pos.x < node->anchor.x && univ.objects[li].pos.y < node->anchor.y) {
				// SW
					((qnode *) node->SW)->objects = array_push(((qnode *) node->SW)->objects, &((qnode *) node->SW)->cant, node->objects[i]);
					// printf("\tEnviando a SW el objeto nro. %d\n", i);

			} else if(
				univ.objects[li].pos.x >= node->anchor.x && univ.objects[li].pos.y < node->anchor.y) {
				// SE
					((qnode *) node->SE)->objects = array_push(((qnode *) node->SE)->objects, &((qnode *) node->SE)->cant, node->objects[i]);
					// printf("\tEnviando a SE el objeto nro. %d\n", i);

			} else {
				printf("* Error: I can't locate the point into quadtree node.\n");
				exit(1);
			}

		}

		printf("\tNW(%d): ", ((qnode *) node->NW)->cant);
		array_print(((qnode *) node->NW)->objects, ((qnode *) node->NW)->cant);

		printf("\tNE(%d): ", ((qnode *) node->NE)->cant);
		array_print(((qnode *) node->NE)->objects, ((qnode *) node->NE)->cant);
		
		printf("\tSW(%d): ", ((qnode *) node->SW)->cant);
		array_print(((qnode *) node->SW)->objects, ((qnode *) node->SW)->cant);

		printf("\tSE(%d): ", ((qnode *) node->SE)->cant);
		array_print(((qnode *) node->SE)->objects, ((qnode *) node->SE)->cant);
		
		// control++;
		// if(control == 8)
		// 	exit(0);		

		quadtree_build(node->NW);
		quadtree_build(node->NE);
		quadtree_build(node->SW);
		quadtree_build(node->SE);

	}
}