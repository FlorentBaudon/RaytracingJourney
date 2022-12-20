#include "Renderer.h"

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
	// image
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 20;
	const int max_bounces = 4;

	//world 
	HittableList world;
	world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
	world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

	// camera
	Camera camera;

	this->colorBuffer = new vec3[image_width * image_height];

	for (int y = image_height - 1; y >= 0; --y)
	{
		std::cout << "\rScanline remaining : " << y << ' ' << std::flush;
		for (int x = 0; x < image_width; x++)
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
