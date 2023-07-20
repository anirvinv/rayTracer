#include <iostream>
#include <vector>

#include "../lib/canvas.h"
#include "../lib/entity.h"
#include "../lib/lighting.h"
#include "../lib/ray.h"
#include "../lib/transformations.h"
#include "../lib/tuple.h"

int main() {
    const int image_width = 1000;
    const int image_height = 1000;

    // the image Plane is z = 10 --> casts silhouette of images SO image plane
    // is behind the images.
    // out of the image Plane is positize z, into the Plane
    // is negative z the camera is at viewport

    Tuple viewport = point_tuple(0, 0, -5000);

    Light light_source = {point_tuple(0, 1000, -1000), {2.3, 2.3, 2.3}};

    // spheres
    Sphere sphere1 = Sphere();
    sphere1.set_transform(scaling(50, 50, 50));
    Sphere sphere2 = Sphere();
    sphere2.set_transform(translation(100, 100, 0) * scaling(30, 30, 30));
    sphere2.material.color = {0.2, 0.8, 0.2};

    Sphere sphere3 = Sphere();
    sphere3.set_transform(translation(-100, 100, 0) * scaling(30, 30, 30));
    sphere3.material.color = {0.2, 0.2, 0.8};

    Entity* entities[] = {&sphere1, &sphere2, &sphere3};

    Canvas canvas = Canvas(image_width, image_height);

    for (int j = -1 * image_height / 2; j < image_height / 2; j++) {
        for (int i = -1 * image_width / 2; i < image_width / 2; i++) {
            // for each pixel, cast a ray from the viewport to the pixel
            // and see if it intersects with any of the objects
            // if it does, color the pixel with the color of the object
            // if it doesn't, color the pixel black

            Tuple pixel_point = point_tuple(i, j, 10000);
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

            canvas.set_pixel(
                i, j,
                lighting(closest_object_ptr->material, light_source,
                         intersection, shadow_ray_direction, normal));
        }
    }

    canvas.write_ppm();
}
