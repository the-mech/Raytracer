#pragma once

#include "ray.h"

struct HitRecord {
	double t;
	vec3 p;
	vec3 normal;
};

class Hitable
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

