#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <getpar.h>
#include <point2D.h>
#include <universe.h>

// Obtiene los parámetros con getopt
void getpar(int argc, char * argv[]) {
	int opt, i, flag = 0;
	
	// Punto de partida para la recepción de parámetros
	for(i = 0; i < 5; i++)
		par.check[i] = 0;
	
	while ((opt = getopt(argc, argv, "i:o:T:t:h:")) != -1) {
		switch (opt) {
			case 'i':
				par.i = (char *) malloc(sizeof(char) * strlen(optarg));
				strcpy(par.i, optarg);
				par.check[0] = 1;
				break;
			case 'o':
				par.o = (char *) malloc(sizeof(char) * strlen(optarg));
				strcpy(par.o, optarg);
				par.check[1] = 1;
				break;
			case 'T':
				par.T = (float) atof(optarg);
				par.check[2] = 1;	
				break;
			case 't':
				par.t = (float) atof(optarg);
				par.check[3] = 1;
				break;
			case 'h':
				par.h = atoi(optarg);
				par.check[4] = 1;
				break;
			default:
				fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	// Verificación de ingreso de parámetros
	for(i = 0; i < 5; i++) {
		if(par.check[i] != 1) {
			flag = 1;
			switch(i) {
				case 0:
					printf("* Error: el parámetro 'i' es obligatorio y no fue proporcionado.\n");
					break;
				case 1:
					printf("* Error: el parámetro 'o' es obligatorio y no fue proporcionado.\n");
					break;
				case 2:
					printf("* Error: el parámetro 'T' es obligatorio y no fue proporcionado.\n");
					break;
				case 3:
					printf("* Error: el parámetro 't' es obligatorio y no fue proporcionado.\n");
					break;
				case 4:
					printf("* Error: el parámetro 'h' es obligatorio y no fue proporcionado.\n");
					break;
			}
		}
	}

	if(flag == 1)
		exit(0);
	
	if (optind != argc) {
		fprintf(stderr, "Expected argument after options %d != %d\n", optind, argc);
		exit(EXIT_FAILURE);
	}
}

// Muestra los parámetros ingresados en la consola
void printpar() {
	printf(" -i: %s\n", par.i);
	printf(" -o: %s\n", par.o);
	printf(" -T: %.2f\n", par.T);
	printf(" -t: %.2f\n", par.t);
	printf(" -h: %d\n", par.h);
}

// Escriba el archivo de salida
void printOutput() {
	FILE * fd = fopen(par.o, "w");
	fprintf(fd, "%d\n", univ.cant);
	fprintf(fd, "%.2E\n", univ.ratio);
	int i;
	for(i = 0; i < univ.cant; i++) {
		fprintf(fd, "%.3E %.3E %.3E %.3E %.3E", 
			univ.objects[i].pos.x,
			univ.objects[i].pos.y,
			univ.objects[i].vel.x,
			univ.objects[i].vel.y,
			univ.objects[i].mass);
		if(i != (univ.cant-1))
			fprintf(fd, "\n");

	}
	close(fd);
}