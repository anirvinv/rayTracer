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
        Tuple translated =
            translation(image_height / 2, image_width / 2, 0) * p;
        canvas.set_pixel(translated.x, translated.y, {0.65, 0.23, 0.43});
        canvas.set_pixel(translated.x - 1, translated.y, {0.65, 0.23, 0.43});
        canvas.set_pixel(translated.x, translated.y - 1, {0.65, 0.23, 0.43});
        canvas.set_pixel(translated.x + 1, translated.y, {0.65, 0.23, 0.43});
        canvas.set_pixel(translated.x, translated.y + 1, {0.65, 0.23, 0.43});
        p = transform * p;
    }
    canvas.write_ppm();
}