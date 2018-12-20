#pragma once
#include "Hitable.h"
class HitableList :
	public Hitable
{
public:
	HitableList();
	HitableList(Hitable** l, unsigned s);
	~HitableList();

	virtual bool hit(const ray& r, double t_min, double t_max, HitRecord& rec) const;

	Hitable** list;
	unsigned list_size;
};

