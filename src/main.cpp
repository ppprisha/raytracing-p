// author: prisha sujin kumar

// include statements
// third party libraries
// std libraries
#include <iostream>
// our libraries

int main() {
	int image_width = 256;
	int image_height = 256;

	// rendering
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++) { // generates values for rows
		for (int i = 0; i < image_width; i++) { // generates values columns
			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.0;

			// scale to fit between 0 and 255
			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
}
