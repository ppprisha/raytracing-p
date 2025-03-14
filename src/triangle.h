#ifndef TRIANGLE_H
#define TRIANGLE_H

// author: prisha sujin kumar
// desc: handles triangle creation

// our libraries
#include "hittable.h"
#include "vec3.h"

class triangle : public hittable {
	public:
		triangle(point3 v_0, point3 v_1, point3 v_2, shared_ptr<material> mat)
			: v0(v_0), v1(v_1), v2(v_2), mat(mat) {}
		bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
			vec3 edge1 = v1 - v0;
			vec3 edge2 = v2 - v0;
			vec3 h = cross(r.direction(), edge2);
			double a = dot(edge1, h);

			if (a > -1e-6 && a < 1e-6) {
				return false;
			}

			double f = 1.0 / a;
			vec3 s = r.origin() - v0;
			double u = f * dot(s, h);
			if (u < 0.0 || u > 1.0) {
				return false;
			}

			vec3 q = cross(s, edge1);
			double v = f * dot(r.direction(), q);
			if (v < 0.0 || u + v > 1.0) {
				return false;
			}

			double t = f * dot(edge2, q);
			if (!ray_t.contains(t)) {
				return false;
			}

			rec.t = t;
			rec.p = r.at(t);
			rec.normal = unit_vector(cross(edge1, edge2));
			rec.mat = mat;
			return true;
		}

		aabb bounding_box() const override {
			point3 min_point = min(v0, min(v1, v2));
			point3 max_point = max(v0, max(v1, v2));
			return aabb(min_point, max_point);
		}
	private:
		point3 v0;
		point3 v1;
		point3 v2;
		shared_ptr<material> mat;
		aabb bbox;
};

#endif // TRIANGLE_H


