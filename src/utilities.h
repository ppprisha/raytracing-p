// author: prisha sujin kumar

#ifndef UTILITIES_H
#define UTILITIES_H

// include statements
// third party libraries
// std libraries
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>


// usings
using std::make_shared;
using std::shared_ptr;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions !
inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

inline double random_double() {
	return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
	return min + (max-min)*random_double();
}

// our libraries - PUT AT END TO AVOID CIRCULAR DEPENDENCY!!!!
#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"


#endif


