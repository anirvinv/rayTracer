#include <iostream>

#include "point3.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

int main() {
    // // Image

    // const int image_width = 256;
    // const int image_height = 256;

    // // Render

    // std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // for (int j = image_height - 1; j >= 0; --j) {
    //     std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    //     for (int i = 0; i < image_width; ++i) {
    //         auto r = double(i) / (image_width - 1);
    //         auto g = double(j) / (image_height - 1);
    //         auto b = 0.25;

    //         int ir = static_cast<int>(255.999 * r);
    //         int ig = static_cast<int>(255.999 * g);
    //         int ib = static_cast<int>(255.999 * b);

    //         std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    //     }
    // }
    // std::cerr << "\nDone.\n";

    point3 s1_center = point3(5, 5, 5);
    sphere s1 = sphere(0.5, s1_center);

    point3 ray_origin = point3(0, 0, 0);
    vec3 ray_direction = vec3(1, 1, 1);
    ray ray1 = ray(ray_origin, ray_direction);
    double t_value = s1.intersection_t_value(ray1);
    std::cout << t_value << std::endl;
}
