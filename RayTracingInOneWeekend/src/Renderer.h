#pragma once

#include "rtweekend.h"
#include "vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"
#include <thread>

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
	Renderer() = default;
	Renderer(RenderSettings settings);
	
	// Members
	vec3* colorBuffer;
	bool bRenderFinished = true;
	bool bRenderStopped = false;

	//Functions
	void SetRendererSettings(RenderSettings settings);
	void StartRender();
	void StopRender();

	

private:
	// Members
	double aspect_ratio;
	int image_width;
	int image_height;
	int samples_per_pixel;
	int max_bounces;

	std::thread renderThread;
	std::vector<uint32_t> verticalIterator;

	//Functions
	void Render();
	color raycolor(const Ray& r, const HittableList& world, int bounce);

	void random_scene(HittableList& world);
};

