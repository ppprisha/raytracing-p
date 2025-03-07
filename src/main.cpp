// author: prisha sujin kumar
// desc: main class to execute program

// our libraries
#include "utilities.h" // replaces need for other includes
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

using namespace std;

int main() {

	// world
	hittable_list world;

	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.8));
	world.add(make_shared<sphere>(point3(0.0, -1000, 0.0), 1000, material_ground));

	for (int a = -5; a < 5; a++) {
		for (int b = -3; b < 3; b++) {
			auto choose_mat = random_double();
			point3 center(a + 0.8*random_double(), 0.3, b + 0.9*random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.7) {
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
					//auto center2 = center + vec3(0, random_double(0, 0.5), 0);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else if (choose_mat < 1.0) {
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else {
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	
	auto material1 = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(5, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.7, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material3));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 1200;
	cam.samples_per_pixel = 100;
	cam.max_depth = 20;
	cam.vfov = 20; // add wide angle camera - higher number is more zoomed out
	
	cam.lookfrom = point3(13, 2, 3);
	cam.lookat = point3(0, 0, 0);
	cam.vup = vec3(0, 1, 0);
	
	cam.defocus_angle = 0.6;
	cam.focus_dist = 10;

	cam.render(world);
}
