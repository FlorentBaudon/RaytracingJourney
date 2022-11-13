#pragma once

#include "Ray.h"

class Camera
{
public :
	Camera();
	Ray GetRay(double u, double v);


	point3 origin;
	point3 viewportOrigin; //lower_left_corner;
	vec3 horizontal;
	vec3 vertical;

};

