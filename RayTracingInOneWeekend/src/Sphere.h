#pragma once

#include "Hittable.h"

class Sphere : public Hittable
{
public :
	Sphere() = default;
	Sphere(point3 _center, double _radius) : center(_center), radius(_radius) {};

	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& record) const override;

public :
	point3 center;
	double radius;

};