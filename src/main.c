#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _OPENMP
	#include <omp.h>
#endif

#include <getpar.h>
#include <point2D.h>
#include <universe.h>
#include <quadtree.h>
#include <linkedlist.h>
#include <arraylist.h>


int main(int argc, char * argv[]) {

	getpar(argc, argv); // Obtención de parámetros
	load(par.i); // Carga del archivo de entrada

	int i, times;

	while(times < (par.T / par.t)) {
		// printf("Iniciando\n");
		quadtree_init();

		// printf("Construyendo arbol\n");
		quadtree_build(&tree);

		// printf("Calculando posiciones\n");
		for(i = 0; i < tree.cant; i++) {
			quadtree_barnes_hut(&tree, tree.objects[i]);
		}

		// printf("Copiando nuevo universo\n");
		_copy(&univ, &univ2);
		printf("(%.3E, %.3E)\n", univ.objects[0].pos.x, univ.objects[0].pos.y);

		times++;
	}

	return EXIT_SUCCESS;
}