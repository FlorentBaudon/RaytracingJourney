#pragma once

#include "rtweekend.h"
#include "vec3.h"
#include "color.h"
#include "Ray.h"
#include "Sphere.h"
#include "HittableList.h"
#include <iostream>

//double hit_sphere(const point3& center, double radius, const Ray& r)
//{
//	vec3 oc = r.origin - center;
//
//	//double a = dot(r.direction, r.direction);
//	//double b = 2.0 * dot(oc, r.direction);
//	//double c = dot(oc, oc) - radius * radius;
//	//Optimized/Simplified version
//	double a = r.direction.length_squared();
//	double half_b = dot(oc, r.direction);
//	double c = oc.length_squared() - radius * radius;
//
//	double discriminant = half_b * half_b - a * c;
//
//	if (discriminant > 0)
//	{
//		return  (-half_b - sqrt(discriminant) ) /  a ;
//	}
//	else 
//	{
//		return -1.0;
//	}
//
//}

color raycolor(const Ray& r, const HittableList& world)
{
//
//	Sphere sphere(point3(0, 0, -1), 0.5);
//	hit_record record;
//	if(sphere.hit(r, 0, 1000, record))
//	{
//		return color(record.normal.x() + 1, record.normal.y() + 1, record.normal.z() + 1) / 2.0; // remap -1;1 to 0;1
//	}
//
//	vec3 unit_direction = unit_vector(r.direction);
//
//	double t = 0.5 * (unit_direction.y() + 1.0);
//
//	color c = (1.0 - t) * color(1, 1, 1) + t * color(0.5, 0.7, 1.0);
//
//	return c;
	hit_record record;
	if (world.hit(r, 0, 10, record))
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

	//world 
	HittableList world;
	world.add( std::make_shared<Sphere>( point3( 0, 0, -1 ), 0.5 ) ) ;
	world.add(std::make_shared<Sphere>( point3( 2, 0, -1 ), 2 ) );

	// camera
	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	point3 camera_origin = point3(0, 0, 0);
	vec3 horizontal = vec3(viewport_width, 0, 0);
	vec3 vertical = vec3(0, viewport_height, 0);
	point3 viewport_origin = camera_origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length); //bottom left corner


	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	//std::cin.get();

	for(int j = image_height-1; j>=0; --j)
	{
		std::cerr << "\rScanline remaining : " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++)
		{
			double u = (double)i / (image_width - 1);
			double v = (double)j / (image_height - 1);
			
			vec3 direction = viewport_origin + ( u * horizontal ) + ( v * vertical ) - camera_origin;

			Ray r(camera_origin, direction);
			
			color pixel_color = raycolor(r, world);

			write_color(std::cout, pixel_color);
		}
	}

	std::cerr << "\Done\n";
}
