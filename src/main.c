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
	quadtree_init();
	quadtree_build(&tree);

	

	return EXIT_SUCCESS;
}