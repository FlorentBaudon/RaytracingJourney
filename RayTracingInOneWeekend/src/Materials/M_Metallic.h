#pragma once

#pragma once

#include "Material.h"

class Metallic : public Material
{
public:
	Metallic(const color& a) : albedo(a) {};

	virtual bool Scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override
	{
		vec3 reflected = reflect(r_in.direction, rec.normal);

		scattered = Ray(rec.p, reflected);
		attenuation = albedo;

		return dot(scattered.direction, rec.normal) > 0;
	}

public:
	color albedo;
};
