#include <iostream>

#include "../lib/canvas.h"
#include "../lib/entity.h"
#include "../lib/ray.h"
#include "../lib/tuple.h"

int main() {
    // Image

    const int image_width = 1600;
    const int image_height = 900;

    // Render

    // the image Plane is z = 0
    // out of the image Plane is positize z, into the Plane is negative z
    // the camera is at viewport

    Tuple viewport = point(image_width / 2, image_height / 2, -500);

    Tuple light_source =
        point(image_width / 2 - 1000, image_height / 2 + 1500, 0);

    // spheres
    Sphere sphere1 =
        Sphere(400, point(image_width / 2, image_height / 2, 1000));
    sphere1.color = {0.95, 0.32, 0.16};

    Sphere sphere2 =
        Sphere(400, point(image_width / 2 + 900, image_height / 2, 1000));
    sphere2.color = {0.16, 0.95, 0.32};

    Sphere sphere3 =
        Sphere(400, point(image_width / 2 - 900, image_height / 2, 1000));
    sphere3.color = {0.16, 0.32, 0.95};

    Sphere sphere4 =
        Sphere(200, point(image_width / 2, image_height / 2 - 100, 500));
    sphere4.color = {0.65, 0.56, 0.32};

    // floor
    Plane floor_plane = Plane(vector(0, 1, 0), point(0, -400, 1000));
    floor_plane.color = {0.45, 0.25, 0.25};

    Entity* entities[] = {&sphere1, &sphere2, &sphere3, &sphere4, &floor_plane};

    Canvas canvas = Canvas(image_width, image_height);

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            Tuple pixel_point = point(i, j, 0);
            Tuple ray_direction = pixel_point - viewport;

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
                canvas.set_pixel(i, j, {0, 0, 0});
                continue;
            }

            Tuple intersection = light_ray.get_point(min_t_value);
            Tuple normal = closest_object_ptr->get_unit_normal(intersection);

            Tuple shadow_ray_direction = normalize(light_source - intersection);

            double dot_product = std::max(
                (double)0,
                shadow_ray_direction.dot(normal));  // this is cos(theta)

            // -1 < r,g,b < 1
            double r = closest_object_ptr->color.r;
            double g = closest_object_ptr->color.b;
            double b = closest_object_ptr->color.g;

            r *= dot_product;
            g *= dot_product;
            b *= dot_product;

            canvas.set_pixel(i, j, {r, g, b});
        }
    }

    canvas.write_ppm();
}
