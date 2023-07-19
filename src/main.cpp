#include <iostream>

#include "entity.h"
#include "ray.h"
#include "vec3.h"

int main() {
    // Image

    const int image_width = 1600;
    const int image_height = 900;

    // Render

    // the image Plane is z = 0
    // out of the image Plane is positize z, into the Plane is negative z
    // the camera is at viewport

    Point3 viewport = Point3(image_width / 2, image_height / 2, 500);

    Point3 light_source =
        Point3(image_width / 2 - 1000, image_height / 2 + 1500, 0);

    // spheres
    Sphere sphere1 =
        Sphere(400, Point3(image_width / 2, image_height / 2, -1000));
    sphere1.color = {0.95, 0.32, 0.16};

    Sphere sphere2 =
        Sphere(400, Point3(image_width / 2 + 900, image_height / 2, -1000));
    sphere2.color = {0.16, 0.95, 0.32};

    Sphere sphere3 =
        Sphere(400, Point3(image_width / 2 - 900, image_height / 2, -1000));
    sphere3.color = {0.16, 0.32, 0.95};

    Sphere sphere4 =
        Sphere(200, Point3(image_width / 2, image_height / 2 - 100, -500));
    sphere4.color = {0.65, 0.56, 0.32};

    // floor
    Plane floor_plane = Plane(Vec3(0, 1, 0), Point3(0, -400, -1000));
    floor_plane.color = {0.45, 0.25, 0.25};

    Entity* entities[] = {&sphere1, &sphere2, &sphere3, &sphere4, &floor_plane};

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rLines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Point3 pixel_point = Point3(i, j, 0);
            Vec3 ray_direction = Vec3(pixel_point - viewport);

            Ray light_ray = Ray(viewport, ray_direction);
            double min_t_value = -1;
            Entity* closest_object_ptr = nullptr;
            for (auto object_ptr : entities) {
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

            Point3 intersection = light_ray.get_point(min_t_value);
            Vec3 normal = closest_object_ptr->get_unit_normal(intersection);

            Vec3 shadow_ray_direction =
                normalize(static_cast<Vec3>(light_source - intersection));

            double dot_product = std::max(
                (long double)0,
                shadow_ray_direction.dot(normal));  // this is cos(theta)

            // -1 < r,g,b < 1
            double r = closest_object_ptr->color.r;
            double g = closest_object_ptr->color.b;
            double b = closest_object_ptr->color.g;

            r *= dot_product;
            g *= dot_product;
            b *= dot_product;

            int ir = static_cast<int>(255 * r);
            int ig = static_cast<int>(255 * g);
            int ib = static_cast<int>(255 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\nDone.\n";
}
