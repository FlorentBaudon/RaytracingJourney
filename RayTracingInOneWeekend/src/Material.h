#pragma once

#include "rtweekend.h"
#include "vec3.h"
#include "Hittable.h"
//#include "Ray.h"

class Ray;

class Material
{
public :
	virtual bool Scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const = 0;
};
