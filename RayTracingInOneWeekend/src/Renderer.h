#pragma once

#include "rtweekend.h"
#include "vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"

struct RenderSettings
{
	double aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = 300;
	int samples_per_pixel = 20;
	int max_bounces = 4;

	RenderSettings(double width, int height, int ratio, int samples, int bounces) 
		: image_width(width), image_height(height), aspect_ratio(ratio), samples_per_pixel(samples), max_bounces(bounces)
	{}
};

class Renderer
{
public :
	Renderer(RenderSettings settings);
	void Render();
	vec3* colorBuffer;

	color raycolor(const Ray& r, const HittableList& world, int bounce);
private:
	double aspect_ratio;
	int image_width;
	int image_height;
	int samples_per_pixel;
	int max_bounces;
};

