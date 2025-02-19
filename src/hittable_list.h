// author: prisha sujin kumar

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

// include statements
// third party libraries
// std libraries
#include <vector>
// our libraries
#include "hittable.h"


class hittable_list : public hittable {
	public:
		std::vector<shared_ptr<hittable>> objects; // shared_ptr<type> is pointer to allocated type
							   // shared pointers are used bc it lets mult geometries to share common instance

		hittable_list() {}
		hittable_list(shared_ptr<hittable> object) {
			add(object);
		}

		void clear() {
			objects.clear();
		}

		void add(shared_ptr<hittable> object) {
			objects.push_back(object);
		}

		bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
			hit_record temp_rec;
			bool hit_anything = false;
			auto closest_so_far = ray_tmax;

			for (const auto& object : objects) {
				if (object -> hit(r, ray_tmin, closest_so_far, temp_rec)) {
					hit_anything = true;
					closest_so_far = temp_rec.t;
					rec = temp_rec;
				}
			}

			return hit_anything;
		}
};

#endif
