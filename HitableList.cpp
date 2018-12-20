#include "HitableList.h"



HitableList::HitableList()
{
}

HitableList::HitableList(Hitable ** l, unsigned s):list(l),list_size(s)
{
}


HitableList::~HitableList()
{
}

bool HitableList::hit(const ray & r, double t_min, double t_max, HitRecord & rec) const
{
	HitRecord tmp_rec;

	bool hit_any = false;

	double closest_so_far = t_max;

	//iterate over list with Hitables
	//and find nearest hit
	for (unsigned i = 0; i < list_size; i++) {


		if (list[i]->hit(r, t_min, closest_so_far, tmp_rec)) {
			hit_any = true;
			closest_so_far = tmp_rec.t;
			rec = tmp_rec;
		}

	}

	return hit_any;
}
