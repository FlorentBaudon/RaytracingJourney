#include "Sphere.h"

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& record) const
{
	vec3 oc = r.origin - center;

	//double a = dot(r.direction, r.direction);
	//double b = 2.0 * dot(oc, r.direction);
	//double c = dot(oc, oc) - radius * radius;
	//Optimized/Simplified version
	double a = r.direction.length_squared();
	double half_b = dot(oc, r.direction);
	double c = oc.length_squared() - radius * radius;

	double discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return false;

	//Square root a very expensive, we cache the result to avoid many sqrt calculations
	double sqrtd = sqrt(discriminant);

	double t = (-half_b - sqrtd) / a;
	if (t < t_min || t > t_max)
	{
		//find second solution
		t = (-half_b + sqrtd) / a;
		if (t < t_min || t > t_max)
			return false;
	}
	record.t = t;
	record.p = r.at(t);
	vec3 outward_normal = (r.at(t) - center) / radius;
	record.set_face_normal(r, outward_normal);

	return true;
}
