#pragma once

#pragma once

#include "Material.h"

class PBR : public Material
{
public:
	PBR(const color& a, const float r, const float m) : albedo(a), roughness(r), metallic(m) {};

	virtual bool Scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override
	{
		vec3 scatter_direction = reflect(r_in.direction, rec.normal) * metallic;
		scatter_direction += roughness * random_unit_vector();


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
	float roughness;
	float metallic;
};
