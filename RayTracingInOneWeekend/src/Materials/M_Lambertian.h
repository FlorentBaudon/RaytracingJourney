#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const color& a) : albedo(a) {};

	virtual bool Scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override
	{
		vec3 scatter_direction = rec.normal + random_unit_vector();

		//prevent scatter direction == 0;
		if (scatter_direction.near_zero())
		{
			scatter_direction = rec.normal;
		}


		scattered = Ray(rec.p, scatter_direction);
		attenuation = albedo;

		return true;
	}

public:
	color albedo;
};