#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _OPENMP
	#include <omp.h>
#endif
#include <math.h>
#include <time.h>

#include <getpar.h>
#include <point2D.h>
#include <universe.h>
#include <quadtree.h>
#include <linkedlist.h>
#include <arraylist.h>

#define NR 1.0E+08

void test() {

	point2D orig;
		orig.x = 0;
		orig.y = 0;

	point2D point;
		point.x = -1;
		point.y = 1;

	point2D * tongo = point2D_direction(point, orig);

	printf("tongo = (%.3f, %.3f) module = %.3f\n", 
		tongo->x, tongo->y, point2D_module(*tongo));

	exit(0);
}

int main(int argc, char * argv[]) {

	// test();

	getpar(argc, argv); // Obtención de parámetros
	load(par.i); // Carga del archivo de entrada

	visu_start_window();

	int i, times;

	while(times < (par.T / par.t)) {
		// printf("Iniciando\n");
		quadtree_init();

		printf("(%.0f, %.0f)", univ.objects[1].pos.x / NR, univ.objects[1].pos.y / NR);
		printf("\tspeed = (%.0E, %.0E)", univ.objects[1].vel.x, univ.objects[1].vel.y);
		printf("\tacc = (%.0E, %.0E)", univ.objects[1].acc.x, univ.objects[1].acc.y);
		printf("\t[%.1E]\n", point2D_module(univ.objects[1].acc));

		quadtree_build(&tree);		
		for(i = 0; i < tree.cant; i++)
			quadtree_barnes_hut(&tree, tree.objects[i]);
		gravitation(&univ, &univ2);
		
		visu_draw_universe();
		
		_copy(&univ, &univ2);		

		usleep(1E+3 * 10);
		times++;
	}

	return EXIT_SUCCESS;
}