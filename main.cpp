#include <iostream>
#include <fstream>
#include <vector>

#define LODEPNG_COMPILE_CPP
#define LODEPNG_COMPILE_DISK
#define LODEPNG_COMPILE_ENCODER
#include "lodepng.h"

#include <random>
#include "vec3.hpp"
#include "ray.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include <random>


//raytracer conventions
// x-right
// y-up
// z-out of screen
// => right handed coordinate system


//berechne mittels vektoralgebra
// strahl parameterform in kugelgleichung eingesetzt
// umgeformt
// t mittels mitternachtsformel berechnen

/* ohne annahmen

vec3 diff = r.origin - position;
double a = vec3::dot(r.direction, r.direction);
double b = 2.0 * vec3::dot(r.direction, diff);
double c = vec3::dot(diff, diff) - radius * radius;

double discriminant = b * b - 4 * a*c;

if (discriminant < 0.0) // square root is imaginary, thus no collision
return -1.0;
else
{
double t1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
double t2 = (-b - std::sqrt(discriminant)) / (2.0 * a);
return std::min(t1, t2); // take minimum for the first hit
}
/+
 mit der annahme, dass die richtung des strahls einen einheitsvektor darstellt, vereinfacht sich die rechnung,
 da dadurch a = 1 wird
 TODO ^
+/


*/

double hit_sphere(const vec3& center, const double radius, const ray& r) {

	vec3 diff = r.origin - center;
	double a = vec3::dot(r.direction, r.direction);
	double b = 2.0 * vec3::dot(r.direction, diff);
	double c = vec3::dot(diff, diff) - radius * radius;

	double discriminant = b * b - 4 * a*c;

	if (discriminant < 0.0) // square root is imaginary, thus no collision
		return -1.0;
	else
	{
		double t1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
		double t2 = (-b - std::sqrt(discriminant)) / (2.0 * a);
		return std::min(t1, t2); // take minimum for the first hit
	}
}

vec3 color(const ray& r, Hitable* world ) {
	HitRecord rec;
	if (world->hit(r, 0.0, DBL_MAX, rec))
	{
		//std::cout << normal_vec << std::endl;
		//std::cout << normal_vec << std::endl;
		//std::cout << hitpoint.z-sphere_origin.z<< std::endl;
		return 0.5*vec3(rec.normal.x+1.0,rec.normal.y+1.0,rec.normal.z+1.0);//shift normals from -1..1 to 0..1
	}
	else {
		double t = 0.5*(r.direction.y + 1.0); //bring y component from -1..1 to 0..1
		return(1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);//blends white to blue
	}
}

int main(int argc, char** argv) {
	//simple_gradient();

	// randomness

	std::uniform_real_distribution<double> rnd(0.0, 1.0);
	std::mt19937_64 rndgen;

	Sphere s;

	int nx = 800;
	int ny = 400;
	int ns = 100;

	std::vector<unsigned char> img_data;
	img_data.reserve(nx*ny * 3);
	//compare img data
	//comparing rounding schemes
	//std::vector<unsigned char> img_data_comp;
	//img_data_comp.reserve(nx*ny * 3);

	//std::ofstream outfile("image.ppm");

	//ppm p3 is ascii columns rows max color
	//outfile << "P3\n" << nx << " " << ny << " 255\n";

	//thats all in camera class
	//vec3 lower_left_corner(-2.0, -1.0, -1.0);
	//vec3 horizontal(4.0, 0.0, 0.0);
	//vec3 vertical(0.0, 2.0, 0.0);
	//vec3 origin(0.0, 0.0, 0.0);

	Hitable* list[2];
	list[0] = new Sphere(vec3(0.0, 0.0, -1.0), 0.5);
	list[1] = new Sphere(vec3(0, -100.5, -1), 100);
	HitableList world(list,2);

	Camera cam;

	//(u,v)=(0,1) upper left corner
	for (int i = ny - 1; i >= 0; i--) {
		for (int j = 0; j < nx; j++) {


			vec3 c(0.0);

			//num_samples
			for (int s = 0; s < ns; s++) {

				double u = (double)(j+rnd(rndgen)) / (double)nx;
				double v = (double)(i+rnd(rndgen)) / (double)ny;

				ray r = cam.getRay(u, v);

				c += color(r,&world);

			}

			unsigned r, g, b;

			c /= (double)ns;

			r = unsigned(255.99 * c.r);
			g = unsigned(255.99 * c.g);
			b = unsigned(255.99 * c.b);

			//outfile << r << " " << g << " " << b << "\n";
			img_data.push_back(r);
			img_data.push_back(g);
			img_data.push_back(b);

			//comp data
			//r = unsigned(255 * c.r);
			//g = unsigned(255 * c.g);
			//b = unsigned(255 * c.b);

			//img_data_comp.push_back(r);
			//img_data_comp.push_back(g);
			//img_data_comp.push_back(b);
		}
	}

	//for (int i = 0; i < img_data.size(); i++) {
	//	/*if (img_data[i] != img_data_comp[i]) {
	//		std::cout << "not identical" << std::endl;
	//	}*/
	//	img_data[i] -= img_data_comp[i];
	//}


	lodepng::encode("image.png", img_data, nx, ny, LCT_RGB);
	//lodepng::encode("image_diff.png", img_data_comp, nx, ny, LCT_RGB);
	//std::cin.get();
	return EXIT_SUCCESS;
}


void simple_gradient() {

	int nx = 1920;
	int ny = 1080;

	vec3 a;

	a.x = 5.0;
	a.y = 3.3;

	a.z = 2.6;

	std::cout << a.r << a.g << a.b;

	std::ofstream outfile("image.ppm");

	//ppm p3 is ascii columns rows max color
	outfile << "P3\n" << nx << " " << ny << " 255\n";


	for (int i = ny - 1; i >= 0; i--) {
		for (int j = 0; j < nx; j++) {

			vec3 c((double)j / nx, (double)i / ny, 0.2);

			unsigned r, g, b;

			r = unsigned(255.99 * c.r);
			g = unsigned(255.99 * c.g);
			b = unsigned(255.99 * c.b);

			outfile << r << " " << g << " " << b << "\n";

		}
	}
}