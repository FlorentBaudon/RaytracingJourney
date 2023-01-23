#pragma once

#include "Ray.h"

class Material;

struct hit_record
{
	point3 p;
	vec3 normal;
	double t;
	bool front_face;

	std::shared_ptr<Material> mat_ptr;

	inline void set_face_normal(const Ray& r, const vec3& outward_normal)
	{
		front_face = dot(r.direction, outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable 
{
public:
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& record) const = 0;
};