#pragma once

#include "rtweekend.h"
#include "vec3.h"
#include "color.h"
#include "Ray.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"
#include <iostream>

color raycolor(const Ray& r, const HittableList& world)
{
	hit_record record;
	if (world.hit(r, 0, infinity, record))
	{
		return 0.5 * (record.normal + color(1, 1, 1));
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
	const int samples_per_pixel = 10;

	//world 
	HittableList world;
	world.add( std::make_shared<Sphere>( point3( 0, 0, -1 ), 0.5 ) ) ;
	world.add(std::make_shared<Sphere>( point3( 0, -100.5, -1 ), 100 ) );

	// camera
	Camera camera;

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	//std::cin.get();

	for(int j = image_height-1; j>=0; --j)
	{
		std::cerr << "\rScanline remaining : " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++)
		{
			color pixel_color(0, 0, 0);

			for (int s = 0; s < samples_per_pixel; s++) 
			{
				double u = ( (double)i + random_double() ) / (image_width - 1);
				double v = ( (double)j + random_double() ) / (image_height - 1);

				Ray r = camera.GetRay(u, v);
				pixel_color += raycolor(r, world);
			}

			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\Done\n";
}
