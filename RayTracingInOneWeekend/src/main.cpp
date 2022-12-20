#pragma once

#include "rtweekend.h"
#include "vec3.h"
#include "color.h"
#include "Ray.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"

namespace RL {
	#include "raylib.h"
}
#include <iostream>

color raycolor(const Ray& r, const HittableList& world, int bounce)
{
	if (bounce <= 0)
		return color(0, 0, 0);

	hit_record record;

	if (world.hit(r, 0, infinity, record))
	{
		point3 target = record.p + record.normal + random_in_unit_sphere();
		return 0.5 * raycolor(Ray(record.p, target - record.p), world, bounce - 1);
	}

	vec3 unit_direction = unit_vector(r.direction);
	double t = 0.5 * (unit_direction.y() + 1.0);
	color c = (1.0 - t) * color(1, 1, 1) + t * color(0.5, 0.7, 1.0);

	return c;
}

int main(int argc, char* argv[])
{
	// image
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 50;
	const int max_bounces = 40;

	RL::InitWindow(image_width, image_height, "Raytracing");

	//world 
	HittableList world;
	world.add( std::make_shared<Sphere>( point3( 0, 0, -1 ), 0.5 ) ) ;
	world.add(std::make_shared<Sphere>( point3( 0, -100.5, -1 ), 100 ) );

	// camera
	Camera camera;

	vec3* colorbuffer = new vec3[image_width * image_height];

	for(int y = image_height-1; y>=0; --y)
	{
		std::cout << "\rScanline remaining : " << y << ' ' << std::flush;
		for (int x = 0; x < image_width; x++)
		{
			color pixel_color(0, 0, 0);

			for (int s = 0; s < samples_per_pixel; s++) 
			{
				double u = ( (double)x + random_double() ) / (image_width - 1);
				double v = ( (double)y + random_double() ) / (image_height - 1);

				Ray r = camera.GetRay(u, v);
				pixel_color += raycolor(r, world, max_bounces);
			}
			colorbuffer[image_width * y + x] = vec3(
				pixel_color.x(), // / (double)samples_per_pixel, 
				pixel_color.y(), // / (double)samples_per_pixel, 
				pixel_color.z() // / (double)samples_per_pixel
			);
		}
	}

	while (!RL::WindowShouldClose())
	{
		RL::BeginDrawing();

		RL::ClearBackground(RL::RAYWHITE);

		RL::DrawText("Congrats! You created your first window!", 190, 200, 20, RL::LIGHTGRAY);
		for (int y = image_height - 1; y >= 0; --y)
		{
			for (int x = 0; x < image_width; x++)
			{
				vec3 c = create_color(colorbuffer[image_width * y + x], samples_per_pixel);
				RL::Color col;
				col.r = c.x();
				col.g = c.y();
				col.b = c.z();
				col.a = 255;
				RL::DrawPixel(x, image_height-y, col);
			}
		}

		RL::EndDrawing();
	}

	std::cerr << "\Done\n";
}
