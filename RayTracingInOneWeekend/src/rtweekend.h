#pragma once

#include <cmath>
#include <memory>
#include <limits>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}

inline double random_double()
{
	// return random[0;1[
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator; //mersenne twister generator
	return distribution(generator);
}

inline double random_double(double min, double max)
{
	// return random[min;max[
	return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max)
{
	if (x < min) return min;
	if (x > max) return max;

	return x;
}
