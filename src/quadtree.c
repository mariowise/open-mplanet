
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include <getpar.h>
#include <point2D.h>
#include <universe.h>
#include <arraylist.h>
#include <quadtree.h>

// #define DDEBUG 0

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

// Procedimiento para inicializar el primer nodo del árbol
qnode * quadtree_init() {
	qnode * node = (qnode *) malloc(sizeof(qnode));
	node->cant = univ.cant;
	node->objects = (int *) malloc(sizeof(int) * node->cant);
	node->mass = 0.0f;
	int i;
	for(i = 0; i < node->cant; i++)
		node->objects[i] = i;
	
	node->anchor.x = 0;
	node->anchor.y = 0;
	node->ratio = univ.ratio;
	return node;
}

// Libera la memoria de un árbol
void quadtree_destroy(qnode * node) {
	if(node->objects != NULL) {
		free(node->objects);
	}

	if(node->NW != NULL) {
		quadtree_destroy(node->NW);
		free(node->NW);
	}
	if(node->NE != NULL) {
		quadtree_destroy(node->NE);
		free(node->NE);
	}
	if(node->SW != NULL) {
		quadtree_destroy(node->SW);
		free(node->SW);
	}
	if(node->SE != NULL) {
		quadtree_destroy(node->SE);
		free(node->SE);
	}
}

// Procedimiento para propagar recursivamente el árbol y construirlo
void quadtree_build(qnode * node) {
	printf("%s", KYEL);
	qnode * nw,* ne,* sw,* se;
	// Si el nodo tiene mas de un elemento hay que expandirlo
	if(node->cant > 1) {
		// Se almacenan los nuevos nodos
		node->NW = (qnode *) malloc(sizeof(qnode)); 
		node->NE = (qnode *) malloc(sizeof(qnode)); 
		node->SW = (qnode *) malloc(sizeof(qnode)); 
		node->SE = (qnode *) malloc(sizeof(qnode));

			nw = node->NW;
			ne = node->NE;
			sw = node->SW;
			se = node->SE;

			nw->cant = 0;
			ne->cant = 0;
			sw->cant = 0;
			se->cant = 0;

			nw->objects = NULL;
			ne->objects = NULL;
			sw->objects = NULL;
			se->objects = NULL;

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
					#ifdef DDEBUG
					printf("\tEnviando a NW el objeto nro. %d en dirección %p (%d)\n", i, ((qnode *) node->NW)->objects, ((qnode *) node->NW)->cant);
					#endif
					nw->objects = (int *) array_push(nw->objects, &nw->cant, li);
					#ifdef DDEBUG
					printf("\tOK\n");
					#endif

			} else if(
				univ.objects[li].pos.x >= node->anchor.x && univ.objects[li].pos.y >= node->anchor.y) {
				// NE
					#ifdef DDEBUG
					printf("\tEnviando a NE el objeto nro. %d en dirección %p (%d)\n", i, ((qnode *) node->NE)->objects, ((qnode *) node->NE)->cant);
					#endif
					ne->objects = (int *) array_push(ne->objects, &ne->cant, li);
					#ifdef DDEBUG
					printf("\tOK\n");
					#endif

			} else if(
				univ.objects[li].pos.x < node->anchor.x && univ.objects[li].pos.y < node->anchor.y) {
				// SW
					#ifdef DDEBUG
					printf("\tEnviando a SW el objeto nro. %d en dirección %p (%d)\n", i, ((qnode *) node->SW)->objects, ((qnode *) node->SW)->cant);
					#endif
					sw->objects = (int *) array_push(sw->objects, &sw->cant, li);
					#ifdef DDEBUG
					printf("\tOK\n");
					#endif

			} else if(
				univ.objects[li].pos.x >= node->anchor.x && univ.objects[li].pos.y < node->anchor.y) {
				// SE
					#ifdef DDEBUG
					printf("\tEnviando a SE el objeto nro. %d en dirección %p (%d)\n", i, ((qnode *) node->SE)->objects, ((qnode *) node->SE)->cant);
					#endif
					se->objects = (int *) array_push(se->objects, &se->cant, li);
					#ifdef DDEBUG
					printf("\tOK\n");
					#endif

			} else {
				printf("* Error: I can't locate the point into quadtree node.\n");
				exit(1);
			}

		}

		#ifdef DDEBUG
		printf("\tNW(%d:%d)\t%p\t: ", ((qnode *) node->NW)->cant, nw->cant, ((qnode *) node->NW)->objects);
		array_print(((qnode *) node->NW)->objects, ((qnode *) node->NW)->cant);

		printf("\tNE(%d:%d)\t%p\t: ", ((qnode *) node->NE)->cant, ne->cant, ((qnode *) node->NE)->objects);
		array_print(((qnode *) node->NE)->objects, ((qnode *) node->NE)->cant);
		
		printf("\tSW(%d:%d)\t%p\t: ", ((qnode *) node->SW)->cant, sw->cant, ((qnode *) node->SW)->objects);
		array_print(((qnode *) node->SW)->objects, ((qnode *) node->SW)->cant);

		printf("\tSE(%d:%d)\t%p\t: ", ((qnode *) node->SE)->cant, se->cant, ((qnode *) node->SE)->objects);
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
	printf("%s", KNRM);
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
		double forceBetweenThem = 6.67384E-11 * (univ.objects[T->objects[0]].mass) / (r * r);
		point2D * direction = point2D_direction(univ.objects[Ci].pos, univ.objects[T->objects[0]].pos);
		direction->x = direction->x * forceBetweenThem;
		direction->y = direction->y * forceBetweenThem;

		// printf("Direccion entre Ci= %d y Obj= %d (%.0E, %.0E)\n", Ci, T->objects[0], direction->x, direction->y);

		// a(t)
		univ.objects[Ci].acc.x += direction->x;
		univ.objects[Ci].acc.y += direction->y;

		return;

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