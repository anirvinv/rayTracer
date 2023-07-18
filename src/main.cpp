#include <iostream>

#include "point3.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

int main() {
    // Image

    const int image_width = 1600;
    const int image_height = 900;

    // Render

    // the image plane is z = 0
    // out of the image plane is positize z, into the plane is negative z
    // the camera is at viewport

    point3 viewport = point3(image_width / 2, image_height / 2, 300);

    point3 light_source =
        point3(image_width / 2 - 1000, image_height / 2 + 1500, 0);

    // objects
    point3 sphere1_center = point3(image_width / 2, image_height / 2, -1000);
    sphere sphere1 = sphere(400, sphere1_center);

    point3 sphere2_center =
        point3(image_width / 2 + 900, image_height / 2, -1000);
    sphere sphere2 = sphere(400, sphere2_center);

    point3 sphere3_center =
        point3(image_width / 2 - 900, image_height / 2, -1000);
    sphere sphere3 = sphere(400, sphere3_center);
    entity* objects[] = {&sphere1, &sphere2, &sphere3};

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rLines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            point3 pixel_point = point3(i, j, 0);
            vec3 ray_direction = pixel_point - viewport;

            ray light_ray = ray(viewport, ray_direction);
            double min_t_value = -1;
            entity* closest_object_ptr = nullptr;
            for (auto object_ptr : objects) {
                double t_value = object_ptr->intersection_t_value(light_ray);
                if (t_value > 0) {
                    if (min_t_value < 0 || t_value < min_t_value) {
                        min_t_value = t_value;
                        closest_object_ptr = object_ptr;
                    }
                }
            }

            if (min_t_value < 0) {
                std::cout << "0 0 0\n";
                continue;
            }

            point3 intersection = light_ray.get_point(min_t_value);

            vec3 shadow_ray_direction = light_source - intersection;
            ray shadow_ray = ray(intersection, shadow_ray_direction);

            // if shadow ray intersects something else before the light source,
            // then the point is in shadow --> make it black

            bool in_shadow = false;
            for (auto object_ptr : objects) {
                double t_value = object_ptr->intersection_t_value(shadow_ray);
                if (t_value > 0) {
                    in_shadow = true;
                    break;
                }
            }

            // -1 < r,g,b < 1

            double r = 0.95;
            double g = 0.32;
            double b = 0.16;

            if (in_shadow) {
                r *= 0.25;
                g *= 0.25;
                b *= 0.25;
            }

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\nDone.\n";
}
