// author: prisha sujin kumar
// desc: main class to execute program

// our libraries
#include "utilities.h" // replaces need for other includes
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "triangle.h"
#include "bvh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <iostream>

using namespace std;

int main() {

	// world
	hittable_list world;

	auto floor = make_shared<sphere>(
			point3(0, -1500, 0),
		       	1000.0,
			make_shared<lambertian>(color(0.2, 0.2, 0.2))
	);
	world.add(floor);

	auto light = make_shared<sphere>(
    		point3(0, 10, 5),  // Position above tree
    			2.0,               // Size
    			make_shared<diffuse_light>(color(15, 15, 15)) // Brightness
		);
	world.add(light);

	// obj logic !
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;
	
	std::string mtl_dir = "./"; // Path to MTL folder
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, "batarang.obj", mtl_dir.c_str())) {
    		std::cerr << "OBJ Error: " << err << std::endl;
    		return 1;
	}

	std::unordered_map<std::string, shared_ptr<material>> material_map;

	auto default_mat = make_shared<lambertian>(color(0.85, 0.50, 0.20));

	for (const auto& mtl : materials) {
    		color albedo(mtl.diffuse[0], mtl.diffuse[1], mtl.diffuse[2]);
    
    		double roughness = 1.0 - (mtl.shininess / 1000.0);

    		if (mtl.illum == 2) { 
        		material_map[mtl.name] = make_shared<metal>(albedo, roughness);
    		} else { 
        		material_map[mtl.name] = make_shared<lambertian>(albedo);
    		}		
	}
	
	for (const auto& shape : shapes) {
    		size_t index_offset = 0;
    		for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
    	    		int material_id = shape.mesh.material_ids[f];
        		shared_ptr<material> mat = default_mat;
        
        		if (material_id >= 0) { // -1 means no material
            			std::string mtl_name = materials[material_id].name;
            			if (material_map.count(mtl_name)) {
                			mat = material_map[mtl_name];
            			}
        		}
				
			tinyobj::index_t idx0 = shape.mesh.indices[index_offset++];
			tinyobj::index_t idx1 = shape.mesh.indices[index_offset++];
			tinyobj::index_t idx2 = shape.mesh.indices[index_offset++];

			point3 v0(
				attrib.vertices[3 * (idx0.vertex_index - 1)],
				attrib.vertices[3 * (idx0.vertex_index - 1) + 1],
				attrib.vertices[3 * (idx0.vertex_index - 1) + 2]
			);
			
			point3 v1(
				attrib.vertices[3 * (idx1.vertex_index - 1)],
				attrib.vertices[3 * (idx1.vertex_index - 1) + 1],
				attrib.vertices[3 * (idx1.vertex_index - 1) + 2]
			);

			point3 v2(
				attrib.vertices[3 * (idx2.vertex_index - 1)],
				attrib.vertices[3 * (idx2.vertex_index - 1) + 1],
				attrib.vertices[3 * (idx2.vertex_index - 1) + 2]
			);

			double scale = 5;
        		double angle = degrees_to_radians(30);
        		point3 offset(0, 1.5, 0);

			v0 = rotate_x(v0 * scale, angle) + offset;
			v1 = rotate_x(v1 * scale, angle) + offset;
			v2 = rotate_x(v2 * scale, angle) + offset;


			world.add(make_shared<triangle>(v0, v1, v2, mat));
		}
	}


	world = hittable_list(make_shared<bvh_node>(world));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 1920;
	cam.samples_per_pixel = 500;
	cam.max_depth = 16;
	cam.vfov = 45; // add wide angle camera - higher number is more zoomed out
	
	cam.lookfrom = point3(0, 5, 15);
	cam.lookat = point3(0, 2, 0);
	cam.vup = vec3(0, 1, 0);
	
	cam.defocus_angle = 0.0;
	cam.focus_dist = 5.0;

	cam.render(world);
}
