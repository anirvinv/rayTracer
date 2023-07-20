#include "../lib/canvas.h"
#include "../lib/matrix.h"
#include "../lib/transformations.h"
#include "../lib/tuple.h"

int main() {
    const int image_height = 500, image_width = 500;
    Canvas canvas = Canvas(image_height, image_width);
    Matrix transform = rotation_z(M_PI / 6);
    Tuple p = point_tuple(30, 30, 0);
    for (int i = 0; i < 12; i++) {
        canvas.set_pixel(p.x, p.y, {0.65, 0.23, 0.43});
        canvas.set_pixel(p.x - 1, p.y, {0.65, 0.23, 0.43});
        canvas.set_pixel(p.x, p.y - 1, {0.65, 0.23, 0.43});
        canvas.set_pixel(p.x + 1, p.y, {0.65, 0.23, 0.43});
        canvas.set_pixel(p.x, p.y + 1, {0.65, 0.23, 0.43});
        p = transform * p;
    }
    canvas.write_ppm();
}