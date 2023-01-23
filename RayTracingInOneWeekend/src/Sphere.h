#pragma once

#include "Hittable.h"

class Sphere : public Hittable
{
public :
	Sphere() = default;
	Sphere(point3 _center, double _radius, std::shared_ptr<Material> _mat) : center(_center), radius(_radius), mat_ptr(_mat) {};

	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& record) const override;

public :
	point3 center;
	double radius;
	std::shared_ptr<Material> mat_ptr;
};