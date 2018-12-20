#include "Sphere.h"

#include <math.h>

Sphere::Sphere() 
{
};

Sphere::Sphere(const vec3& pcenter, const double pradius) :
	center(pcenter),
	radius(pradius) {
};

Sphere::~Sphere() {
};

bool Sphere::hit(const ray& r, double t_min, double t_max, HitRecord& rec) const {
	vec3 diff = r.origin - center;
	double a = vec3::dot(r.direction, r.direction);
	double b = 2.0 * vec3::dot(r.direction, diff);
	double c = vec3::dot(diff, diff) - radius * radius;

	double discriminant = b * b - 4 * a*c;

	if (discriminant > 0.0) {
		double t = (-b - std::sqrt(b*b - 4 * a*c)) / (2 * a);

		if (t<t_max && t> t_min) {
			rec.t = t;
			rec.p = r.p(t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}

		t = (-b + std::sqrt(b*b - 4 * a*c)) / (2 * a);

		if (t<t_max && t> t_min) {
			rec.t = t;
			rec.p = r.p(t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}

	}

	return false;
}