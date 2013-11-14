#ifndef POINT2D_H_
#define POINT2D_H_

typedef struct {
	double x;
	double y;
} point2D;

double point2D_distance(point2D p1, point2D p2);

double point2D_module(point2D p);

#endif