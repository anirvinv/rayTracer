#include <iostream>
#include <vector>

#include "../lib/canvas.h"
#include "../lib/entity.h"
#include "../lib/lighting.h"
#include "../lib/ray.h"
#include "../lib/transformations.h"
#include "../lib/tuple.h"

int main() {
    // Image

    const int image_width = 1600;
    const int image_height = 900;

    // Render

    // the image Plane is z = 0
    // out of the image Plane is positize z, into the Plane is negative z
    // the camera is at viewport

    Tuple viewport = point_tuple(image_width / 2, image_height / 2, -700);

    Light light_source = {point_tuple(image_width / 2, 2000, -1000),
                          {2.3, 2.3, 2.3}};

    // spheres
    Sphere sphere1 =
        Sphere(400, point_tuple(image_width / 2, image_height / 2, 1000));
    sphere1.material.color = {0.95, 0.32, 0.16};

    Sphere sphere2 = sphere1.transform(translation(1500, 0, 0));
    sphere2.material.color = {0.16, 0.95, 0.32};

    Sphere sphere3 = sphere1.transform(translation(-1500, 0, 0));
    sphere3.material.color = {0.16, 0.32, 0.95};
    sphere3.material.specular = 2;
    sphere3.material.shininess = 100;

    Sphere sphere4 =
        Sphere(200, point_tuple(image_width / 2, image_height / 2 - 100, 500));
    sphere4.material.color = {0.65, 0.56, 0.32};
    Sphere sphere5 = Sphere(
        200, point_tuple(image_width / 2 + 500, image_height / 2 - 200, 300));
    sphere5.material.color = {0.15, 0.56, 0.32};
    Sphere sphere6 = Sphere(
        200, point_tuple(image_width / 2 - 500, image_height / 2 - 300, 200));
    sphere6.material.color = {0.65, 0.36, 0.82};
    Sphere sphere7 =
        Sphere(200, point_tuple(image_width / 2, image_height / 2 - 400, 100));
    sphere7.material.color = {0.2, 0.6, 0.12};

    // floor
    Plane floor_plane =
        Plane(vector_tuple(0, 1, 0), point_tuple(0, -400, 1000));

    floor_plane.material.color = {0.45, 0.25, 0.25};

    Plane wall1 = Plane(vector_tuple(1, 0, 0), point_tuple(-800, 0, 1000));
    wall1.material.color = {0.45, 0.25, 0.25};
    Plane wall2 = Plane(vector_tuple(-1, 0, 0), point_tuple(2400, 0, 1000));
    wall2.material.color = {0.45, 0.25, 0.25};

    Entity* entities[] = {&sphere1, &sphere2, &sphere3,     &sphere4, &sphere5,
                          &sphere6, &sphere7, &floor_plane, &wall1,   &wall2};

    Canvas canvas = Canvas(image_width, image_height);

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            Tuple pixel_point = point_tuple(i, j, 0);
            Tuple ray_direction = pixel_point - viewport;

            Ray light_ray = Ray(viewport, ray_direction);
            double min_t_value = -1;
            Entity* closest_object_ptr = nullptr;
            for (auto object_ptr : entities) {
                std::vector<Intersection> intersections =
                    object_ptr->intersections(light_ray);
                if (intersections.size() != 0) {
                    for (auto intersection : intersections) {
                        if (min_t_value < 0 ||
                            (intersection.t_value < min_t_value &&
                             intersection.t_value > 0)) {
                            min_t_value = intersection.t_value;
                            closest_object_ptr = object_ptr;
                        }
                    }
                }
            }

            if (min_t_value < 0) {
                canvas.set_pixel(i, j, {0, 0, 0});
                continue;
            }

            Tuple intersection = light_ray.get_point(min_t_value);
            Tuple normal = closest_object_ptr->get_unit_normal(intersection);

            Tuple shadow_ray_direction =
                normalize(light_source.position - intersection);

            double dot_product = std::max(
                (double)0,
                shadow_ray_direction.dot(normal));  // this is cos(theta)

            // -1 < r,g,b < 1
            double r = closest_object_ptr->material.color.r;
            double g = closest_object_ptr->material.color.b;
            double b = closest_object_ptr->material.color.g;

            r *= dot_product;
            g *= dot_product;
            b *= dot_product;

            canvas.set_pixel(
                i, j,
                lighting(closest_object_ptr->material, light_source,
                         intersection, shadow_ray_direction, normal));
        }
    }

    canvas.write_ppm();
}
