#include "Camera.h"

Camera::Camera()
{
	auto aspectRatio = 16.0 / 9.0;
	auto viewportHeight = 2.0;
	auto viewportWidth = aspectRatio * viewportHeight;
	auto focalLength = 1.0;

	this->origin = point3(0, 0, 0);
	this->horizontal = vec3(viewportWidth, 0, 0);
	this->vertical = vec3(0, viewportHeight, 0);

	this->viewportOrigin = this->origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength); //bottom left corner

}

Ray Camera::GetRay(double u, double v)
{
	vec3 direction = viewportOrigin + ( horizontal * u ) + ( vertical * v ) - origin;
	return Ray(origin, direction);
}
