
#include <math.h>
#include <point2D.h>

double point2D_distance(point2D p1, point2D p2) {
	return (double) sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p2.y, 2));
}

double point2D_module(point2D p) {
	return (double) sqrt(pow(p.x, 2) + pow(p.y, 2));
}

point2D * point2D_direction(point2D p1, point2D p2) {
	point2D * tongo = (point2D *) malloc(sizeof(point2D));
	double r = point2D_distance(p1, p2);
	tongo->x = (p2.x - p1.x) / r;
	tongo->y = (p2.y - p1.y) / r;
	return tongo;
}
