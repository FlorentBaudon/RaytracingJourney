#include "Renderer.h"
#include "Materials/MaterialLib.h"

#include <execution>

#define MT 0

Renderer::Renderer(RenderSettings settings)
{
	this->image_width = settings.image_width;
	this->image_height = settings.image_height;
	this->aspect_ratio = settings.aspect_ratio;
	this->samples_per_pixel = settings.samples_per_pixel;
	this->max_bounces = settings.max_bounces;
}

void Renderer::StartRender()
{
	std::cout << "Start Render" << std::endl;
	StopRender();
	renderThread = std::thread{&Renderer::Render, this};
}

void Renderer::StopRender()
{
	if (!bRenderFinished || renderThread.joinable())
	{
		std::cout << "Push stop" << std::endl;
		bRenderStopped = true;
		renderThread.join();
		bRenderStopped = false;
	}
}

void Renderer::Render()
{
	bRenderFinished = false;

	//world 
	HittableList world;
	std::shared_ptr<Material> ground = std::make_shared<Lambertian>(point3(0.8, 0.8, 0));
	std::shared_ptr<Material> sphereCenter = std::make_shared<Lambertian>(point3(0.7, 0.3, 0.3));
	std::shared_ptr<Material> sphereLeft = std::make_shared<Dielectric>(1.5);
	std::shared_ptr<Material> sphereRight = std::make_shared<Metallic>(color(0.8, 0.8, 0.8), 1.0f);
	
	world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100, ground));
	world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5, sphereCenter));
	world.add(std::make_shared<Sphere>(point3(-1, 0, -1), 0.5, sphereLeft));
	world.add(std::make_shared<Sphere>(point3(1, 0, -1), 0.5, sphereRight));

	// camera
	point3 cPosition = point3(-2, 2, 1);
	point3 lookat = point3(0, 0, -1);
	vec3 vup = vec3(0, 1, 0);
	double distFocus = (lookat - cPosition).length();
	double aperture = 2.0;

	Camera camera(cPosition, lookat, vup, 20, 16.0/9.0, aperture, distFocus);

	this->colorBuffer = new vec3[image_width * image_height];

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
				/* Stop threading*/
				if (bRenderStopped == true)
				{
					bRenderFinished = true;
					return;
				}
				/*****************/

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
		//std::cout << "\rScanline remaining : " << y << ' ' << std::flush;
		for (int x = 0; x < image_width - 1; x++)
		{
			/* Stop threading*/
			if (bRenderStopped == true)
			{
				bRenderFinished = true;
				return;
			}
			/*****************/

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
		Ray scattered;
		color attenuation;
		if( record.mat_ptr->Scatter(r, record, attenuation, scattered) )
			return attenuation * raycolor(scattered, world, bounce - 1);

		return color(0, 0, 0);
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
