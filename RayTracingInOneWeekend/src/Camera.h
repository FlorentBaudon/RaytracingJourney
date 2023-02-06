#pragma once

#include "Ray.h"

class Camera
{
public :
	Camera(point3 position, vec3 lookat, vec3 vecUp, double vfov, double aspectRatio, double aperture, double focusDist);
	Ray GetRay(double u, double v);


	point3 origin;
	point3 viewportOrigin; //lower_left_corner;
	vec3 horizontal;
	vec3 vertical;

private :
	vec3 u, v, w;
	double lensRadius;

};

