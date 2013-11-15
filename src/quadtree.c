
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include <getpar.h>
#include <point2D.h>
#include <universe.h>
#include <arraylist.h>
#include <quadtree.h>

// #define DDEBUG 0

// Procedimiento para inicializar el primer nodo del árbol
void quadtree_init() {
	tree.cant = univ.cant;
	tree.objects = (int *) malloc(sizeof(int) * tree.cant);
	tree.mass = 0.0f;
	int i;
	for(i = 0; i < tree.cant; i++)
		tree.objects[i] = i;
	// for(i = 0; i < tree.cant; i++)
	// 	tree.mass += univ.objects[i].mass;

	tree.anchor.x = 0;
	tree.anchor.y = 0;
	tree.ratio = univ.ratio;

	// printf("Árbol inicializado con 5 objetos y una masa de %.3e kilos\n", tree.mass);
}

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

			// Nuevas coordenadas del centro de cada cuadrante
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

		int i, li;

		// Cálulo del centro de masa de la constelación
		for(i = 0; i < node->cant; i++) {
			li = node->objects[i];
			node->massCentre.x += univ.objects[li].pos.x * univ.objects[li].mass / univ.mass;
			node->massCentre.y += univ.objects[li].pos.y * univ.objects[li].mass / univ.mass;

			node->mass += univ.objects[li].mass;
		}

		#ifdef DDEBUG
		printf("\nVector padre tiene ");
		array_print(node->objects, node->cant);
		printf("Anchor= (%.2E, %.2E) Mass= %.3E Centre= (%.3E, %.3E)\n", node->anchor.x, node->anchor.y, node->mass, node->massCentre.x, node->massCentre.y);
		#endif

		for(i = 0; i < node->cant; i++) {

			li = node->objects[i];

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

		#ifdef DDEBUG
		printf("\tNW(%d): ", ((qnode *) node->NW)->cant);
		array_print(((qnode *) node->NW)->objects, ((qnode *) node->NW)->cant);

		printf("\tNE(%d): ", ((qnode *) node->NE)->cant);
		array_print(((qnode *) node->NE)->objects, ((qnode *) node->NE)->cant);
		
		printf("\tSW(%d): ", ((qnode *) node->SW)->cant);
		array_print(((qnode *) node->SW)->objects, ((qnode *) node->SW)->cant);

		printf("\tSE(%d): ", ((qnode *) node->SE)->cant);
		array_print(((qnode *) node->SE)->objects, ((qnode *) node->SE)->cant);
		#endif
		// control++;
		// if(control == 8)
		// 	exit(0);		

		quadtree_build(node->NW);
		quadtree_build(node->NE);
		quadtree_build(node->SW);
		quadtree_build(node->SE);

	} else if(node->cant == 1) {

		#ifdef DDEBUG
		printf("\nVector padre tiene ");
		array_print(node->objects, node->cant);
		#endif

		int li = node->objects[0];
		node->massCentre.x += univ.objects[li].pos.x * univ.objects[li].mass / univ.mass;
		node->massCentre.y += univ.objects[li].pos.y * univ.objects[li].mass / univ.mass;

		node->mass += univ.objects[li].mass;		

		#ifdef DDEBUG
		printf("Anchor= (%.2E, %.2E) Mass= %.3E Centre= (%.3E, %.3E)\n", node->anchor.x, node->anchor.y, node->mass, node->massCentre.x, node->massCentre.y);
		#endif
	}
}

// Muestra el árbol por niveles
void quadtree_print(qnode * node, int base) {
	int i;
	for(i = 0; i < base; i++)
		printf("    ");
	array_print(node->objects, node->cant);
	if(node->NW != NULL)
		quadtree_print(node->NW, base+1);
	if(node->NE != NULL)
		quadtree_print(node->NE, base+1);
	if(node->SW != NULL)
		quadtree_print(node->SW, base+1);
	if(node->SE != NULL)
		quadtree_print(node->SE, base+1);
}

// Ejecuta el procedimiento de barnes-hut
void quadtree_barnes_hut(qnode * T, int Ci) {
	if(T == NULL) {
		printf("* Error: I cant do barnes-hut from null pointer.\n");
		exit(1);
	} else if(T->cant == 0)
		return;


	double r = point2D_distance(univ.objects[Ci].pos, univ.objects[T->objects[0]].pos);

	// Si es un nodo externo
	if(T->cant == 1 && T->objects[0] != Ci) {
		double forceBetweenThem = 6.674E-11 * (univ.objects[Ci].mass * univ.objects[T->objects[0]].mass) / (r * r);
		// printf("\tforce = %.3E\n", forceBetweenThem);
		point2D * direction = point2D_direction(univ.objects[Ci].pos, univ.objects[T->objects[0]].pos);
		double accModule = forceBetweenThem / univ.objects[Ci].mass;
		direction->x *= accModule;
		direction->y *= accModule;

		// # CRITICAL #############################################
		// a(t)
		univ2.objects[Ci].acc.x = direction->x;
		univ2.objects[Ci].acc.y = direction->y;
		// ########################################################

		return;
	// }
	// if(point2D_distance(univ.objects[Ci].pos, univ.objects[T->objects[0]].pos) > Threshold) {

	} else if(T->cant == 1 && T->objects[0] == Ci) {
		return;

	} else {
		if(T->NW != NULL)
			quadtree_barnes_hut(T->NW, Ci);
		if(T->NE != NULL)
			quadtree_barnes_hut(T->NE, Ci);
		if(T->SW != NULL)
			quadtree_barnes_hut(T->SW, Ci);
		if(T->SE != NULL)
			quadtree_barnes_hut(T->SE, Ci);
	}
}