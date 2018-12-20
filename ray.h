#pragma once

#include "vec3.hpp"	

//ray direction is normalized
class ray
{
public:
	ray() {};

	ray(const vec3& porigin, const vec3& pdirection):
		origin(porigin),
		direction(pdirection)
	{
		direction.normalize();
	}

	~ray() {};

	vec3 p(double t) const {
		return origin + t* direction;
	}

	vec3 origin;
	vec3 direction;
};

