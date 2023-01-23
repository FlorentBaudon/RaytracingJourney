#pragma once

#pragma once

#include "Material.h"

class Metallic : public Material
{
public:
	Metallic(const color& a, const float& roughness) : albedo(a), roughness(roughness){};

	virtual bool Scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override
	{
		vec3 reflected = reflect(r_in.direction, rec.normal);

		scattered = Ray(rec.p, reflected + roughness * random_in_unit_sphere() );
		attenuation = albedo;

		return dot(scattered.direction, rec.normal) > 0;
	}

public:
	color albedo;
	float roughness = 1.0f;
};
