// author: prisha sujin kumar

#ifndef COLOR_H
#define COLOR_H

// include statements
// third party libraries
// std libraries
#include <iostream>

// our libraries
#include "vec3.h"

using color = vec3;

// replaces logic in main to generate colors
void write_color(std::ostream& out, const color& pixel_color) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	int rbyte = int(255.999 * r);
	int gbyte = int(255.999 * g);
	int bbyte = int(255.999 * b);

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
