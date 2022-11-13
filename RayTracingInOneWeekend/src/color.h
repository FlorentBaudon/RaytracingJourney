#pragma once

#include "vec3.h"

#include <iostream>

void write_color(std::ostream& out, color pixel_color, int samples_per_pixels) 
{

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();
    
    r /= (double)samples_per_pixels;
    g /= (double)samples_per_pixels;
    b /= (double)samples_per_pixels;

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>( 255.999 * clamp(r, 0.0, 0.999) ) << ' '
        << static_cast<int>( 255.999 * clamp(g, 0.0, 0.999) ) << ' '
        << static_cast<int>( 255.999 * clamp(b, 0.0, 0.999) ) << '\n';
}
