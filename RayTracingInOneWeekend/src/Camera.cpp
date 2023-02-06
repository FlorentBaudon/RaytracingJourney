#include "Camera.h"

Camera::Camera(point3 position = point3(0,0,0), point3 lookat = point3(0,0,-1), vec3 vecUp = vec3(0,1,0), double vfov=90.0, double aspectRatio = (16.0/9.0), double aperture = 2, double focusDist = 1)
{
	double theta = degrees_to_radians(vfov);
	auto viewportHeight = 1.0 * theta;
	auto viewportWidth = aspectRatio * viewportHeight;
	auto focalLength = 1.0;

	w = unit_vector(position - lookat); //front vector on projected plane
	u = unit_vector(cross(vecUp, w)); //right vector on projected plane
	v = cross(w, u); // up vector on projected plane

	this->origin = position;
	this->horizontal = focusDist * viewportWidth * u;
	this->vertical = focusDist * viewportHeight * v;

	this->viewportOrigin = this->origin - horizontal / 2 - vertical / 2 - focusDist * w; //bottom left corner

	lensRadius = aperture / 2;

}

Ray Camera::GetRay(double u, double v)
{
	vec3 random = lensRadius * random_in_unit_disk();
	vec3 offset = vec3(u * random.x(), v * random.y(), 0);
	vec3 direction = viewportOrigin + ( horizontal * u ) + ( vertical * v ) - origin - offset;
	return Ray(origin + offset, direction);
}
