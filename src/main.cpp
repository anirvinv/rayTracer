#include <iostream>
#include <vector>

#include "../lib/canvas.h"
#include "../lib/entity.h"
#include "../lib/lighting.h"
#include "../lib/ray.h"
#include "../lib/transformations.h"
#include "../lib/tuple.h"
#include "../lib/world.h"

int main() {
    const int image_width = 1000;
    const int image_height = 1000;

    // the image Plane is z = 10 --> casts silhouette of images SO image plane
    // is behind the images.
    // out of the image Plane is positize z, into the Plane
    // is negative z the camera is at viewport

    Tuple viewport = point_tuple(0, 0, -5000);

    Light light_source = {point_tuple(-1000, 1000, -1000), {1, 1, 1}};

    // spheres
    Sphere sphere1 = Sphere();
    sphere1.set_transform(scaling(50, 50, 50));
    sphere1.material.color = {0.8, 0.2, 0.2};
    Sphere sphere2 = Sphere();
    sphere2.set_transform(translation(100, 100, 0) * scaling(30, 30, 30));
    sphere2.material.color = {0.2, 0.8, 0.2};

    Sphere sphere3 = Sphere();
    sphere3.set_transform(translation(-100, 100, 0) * scaling(30, 30, 30));
    sphere3.material.color = {0.2, 0.2, 0.8};

    Entity* entities[] = {&sphere1, &sphere2, &sphere3};
    World world =
        World(std::vector<Entity*>(entities, entities + 3), light_source);

    Canvas canvas = Canvas(image_width, image_height);

    for (int j = -image_height / 2; j < image_height / 2; j++) {
        for (int i = -image_width / 2; i < image_width / 2; i++) {
            // for each pixel, cast a ray from the viewport to the pixel
            // and see if it intersects with any of the objects
            // if it does, color the pixel with the color of the object
            // if it doesn't, color the pixel black
            Tuple pixel_point = point_tuple(i, j, 10000);
            Tuple ray_direction = pixel_point - viewport;
            Ray light_ray = Ray(viewport, ray_direction);
            canvas.set_pixel(i, j, color_at(world, light_ray));
        }
    }

    canvas.write_ppm();
}
