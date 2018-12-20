#pragma once
#include "Hitable.h"
class Sphere :
	public Hitable
{
public:
	Sphere();
	Sphere(const vec3& pcenter, const double pradius);
	~Sphere();

	virtual bool hit(const ray& r, double t_min, double t_max, HitRecord& rec) const;

	vec3 center;
	double radius;
};

