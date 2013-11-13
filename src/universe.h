#ifndef UNIVERSE_H_
#define UNIVERSE_H_

typedef struct {

	point2D pos;	// Posición del objeto
	point2D vel;	// Velocidad del objeto
	point2D acc;	// Aceleración del objeto
	double mass;	// Masa del objeto

} object;

struct _univ {

	int cant;			// Cantidad de planetas en el universo
	double ratio;		// Radio del universo
	object * objects;	// Planetas u objetos del universo

} univ;

void * load(char * name);

#endif