#ifndef GETPAR_H_
#define GETPAR_H_

struct _par {
	
	char * i; 	// Archivo con la configuración inicial del universo	
	char * o; 	// Archivo con la configuración final del universo	
	float T;	// Tiempo de simulación	
	float t;	// Intervalo de tiempo	
	int h; 		// Número máximo de hebras

	int check[5];

} par;

void getpar(int argc, char * argv[]);

void printpar();

#endif