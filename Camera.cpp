#include "Camera.h"



Camera::Camera() :
	lower_left_corner(-2.0, -1.0, -1.0),
	horizontal(4.0, 0.0, 0.0),
	vertical(0.0, 2.0, 0.0),
	origin(0.0, 0.0, 0.0)
{
}


Camera::~Camera()
{
}


ray Camera::getRay(double u, double v) {
	return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}