#include "Renderer.h"
#include <execution>

Renderer::Renderer(RenderSettings settings)
{
	this->image_width = settings.image_width;
	this->image_height = settings.image_height;
	this->aspect_ratio = settings.aspect_ratio;
	this->samples_per_pixel = settings.samples_per_pixel;
	this->max_bounces = settings.max_bounces;
}

void Renderer::Render()
{
	bRenderFinished = false;

	//world 
	HittableList world;
	world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
	world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

	// camera
	Camera camera;

	this->colorBuffer = new vec3[image_width * image_height];

#define MT 0
#if MT
	for (uint32_t i = 0; i < image_height-1; i++)
	{
		verticalIterator.push_back(image_height - i -1);
	}
	
	std::for_each(std::execution::par, verticalIterator.begin(), verticalIterator.end(), [this, &camera, &world](uint32_t y)
		{
			//std::cout << "\rMT Scanline remaining : " << y << ' ' << std::flush;
			for (int x = 0; x < image_width - 1; x++)
			{
				color pixel_color(0, 0, 0);

				for (int s = 0; s < samples_per_pixel; s++)
				{
					double u = ((double)x + random_double()) / (image_width - 1);
					double v = ((double)y + random_double()) / (image_height - 1);

					Ray r = camera.GetRay(u, v);
					pixel_color += raycolor(r, world, max_bounces);
				}

				this->colorBuffer[image_width * y + x] = vec3(
					pixel_color.x(), // / (double)samples_per_pixel, 
					pixel_color.y(), // / (double)samples_per_pixel, 
					pixel_color.z() // / (double)samples_per_pixel
				);
			}
		});
#else
	for (int y = image_height - 1; y >= 0; --y)
	{
			std::cout << "\rScanline remaining : " << y << ' ' << std::flush;
			for (int x = 0; x < image_width - 1; x++)
			{
				color pixel_color(0, 0, 0);

				for (int s = 0; s < samples_per_pixel; s++)
				{
					double u = ((double)x + random_double()) / (image_width - 1);
					double v = ((double)y + random_double()) / (image_height - 1);

					Ray r = camera.GetRay(u, v);
					pixel_color += raycolor(r, world, max_bounces);
				}

				this->colorBuffer[image_width * y + x] = vec3(
					pixel_color.x(), // / (double)samples_per_pixel, 
					pixel_color.y(), // / (double)samples_per_pixel, 
					pixel_color.z() // / (double)samples_per_pixel
				);
			}
	}
#endif

	bRenderFinished = true;
}

color Renderer::raycolor(const Ray& r, const HittableList& world, int bounce)
{
	if (bounce <= 0)
		return color(0, 0, 0);

	hit_record record;

	if (world.hit(r, 0.0001, infinity, record))
	{
		point3 target = record.p + record.normal + random_in_unit_sphere();
		return 0.5 * raycolor(Ray(record.p, target - record.p), world, bounce - 1);
	}

	vec3 unit_direction = unit_vector(r.direction);
	double t = 0.5 * (unit_direction.y() + 1.0);
	color c = (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);

	return c;
}

void Renderer::SetRendererSettings(RenderSettings settings)
{
	this->image_width = settings.image_width;
	this->image_height = settings.image_height;
	this->aspect_ratio = settings.aspect_ratio;
	this->samples_per_pixel = settings.samples_per_pixel;
	this->max_bounces = settings.max_bounces;
}
