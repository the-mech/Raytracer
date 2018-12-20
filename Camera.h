#pragma once

#include "ray.h"

class Camera
{
public:
	Camera();
	~Camera();


	ray getRay(double u, double v);

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};

