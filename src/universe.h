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
	double mass;		// Masa total del universo

} univ, univ2;

void * load(char * name);

void _copy(struct _univ * u1, struct _univ * u2);

#endif