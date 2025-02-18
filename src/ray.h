// author: prisha sujin kumar

#ifndef RAY_H
#define RAY_H

// include statements
// third party statements
// std libraries
// our libraries
#include "vec3.h"

class ray {
	public:
		ray() {}
		ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
		
		const point3& origin() const { // return immutable ref to their members
			return orig;
		}

		const vec3& direction() const { // return immutble ref to their members
			return dir;
		}

		point3 at(double t) const {
			return orig + t*dir;
		}

	private:
		point3 orig;
		vec3 dir;
};

#endif


