#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getpar.h>
#include <point2D.h>
#include <universe.h>

// Lee el archivo de entrada y construye el universo
void * load(char * name) {
	FILE * fd;
	char * line = (char *) malloc(sizeof(char));
	size_t len;
	ssize_t read;

	if((fd = fopen(name, "r")) == NULL) {
		printf("* Error: I can't read file '%s'.\n", name);
		exit(1);
	}

	// Lectura de la primera linea: Número de cuerpos del universo
	if((read = getline(&line, &len, fd)) == -1) {
		printf("* Error: I can't read the first line of '%s'.\n", name);
		exit(1);
	}

		univ.cant = atoi(line);
		// printf("%d\n", univ.cant);

		// Se reserva memoria para los objetos en el universo
		univ.objects = (object *) malloc(sizeof(object) * univ.cant);

	// Lectura de la segunda linea: Número igual al radio del universo
	if((read = getline(&line, &len, fd)) == -1) {
		printf("* Error: I can't read the second line of '%s'.\n", name);
		exit(1);
	}

		univ.ratio = (double) atof(line);
		// printf("%.3e\n", univ.ratio);

	int i = 0, j = 0;
	char * token;
	while((read = getline(&line, &len, fd)) != -1) {

		// Primer vector
		token = strtok(line, " ");
		univ.objects[i].pos.x = (double) atof(token); // printf("%.3e ", univ.objects[i].pos.x);
		token = strtok(NULL, " ");
		univ.objects[i].pos.y = (double) atof(token); // printf("%.3e ", univ.objects[i].pos.y);

		// Segundo vector
		token = strtok(NULL, " ");
		univ.objects[i].vel.x = (double) atof(token); // printf("%.3e ", univ.objects[i].vel.x);
		token = strtok(NULL, " ");
		univ.objects[i].vel.y = (double) atof(token); // printf("%.3e ", univ.objects[i].vel.y);

			univ.objects[i].acc.x = 0.0f; 
			univ.objects[i].acc.y = 0.0f;

		// Masa del objeto
		token = strtok(NULL, " \n\r\t");
		univ.objects[i].mass = (double) atof(token); // printf("%.3e\n", univ.objects[i].mass);

		// Se incrementa la masa del universo
		univ.mass += univ.objects[i].mass;
		
		i++;

	}

	_copy(&univ2, &univ);
}

void _copy(struct _univ * u1, struct _univ * u2) {
	u1->cant 	= u2->cant;
	u1->ratio 	= u2->ratio;
	u1->mass 	= u2->mass;
	
	if(u1->objects != NULL) 
		free(u1->objects);
	
	u1->objects = (object *) malloc(sizeof(object) * u1->cant);

	int i;
	for(i = 0; i < u1->cant; i++) {
		u1->objects[i].pos.x = u2->objects[i].pos.x;
		u1->objects[i].pos.y = u2->objects[i].pos.y;
		u1->objects[i].vel.x = u2->objects[i].vel.x;
		u1->objects[i].vel.y = u2->objects[i].vel.y;
		u1->objects[i].acc.x = u2->objects[i].acc.x;
		u1->objects[i].acc.y = u2->objects[i].acc.y;
		u1->objects[i].mass = u2->objects[i].mass;		
	}
}