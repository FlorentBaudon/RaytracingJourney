#pragma once

#include "Hittable.h"	

#include <vector>
#include <memory>

class HittableList: public Hittable
{
public:
	HittableList() {};
	HittableList(std::shared_ptr<Hittable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

	// Inherited via Hittable
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& record) const override;


public :
	std::vector<std::shared_ptr<Hittable>> objects;
};