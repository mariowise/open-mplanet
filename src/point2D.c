
#include <math.h>
#include <point2D.h>

double point2D_distance(point2D p1, point2D p2) {
	return (double) sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p2.y, 2));
}