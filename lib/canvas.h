#ifndef CANVAS
#define CANVAS

#include <iostream>

#include "entity.h"

class Canvas {
   public:
    int width, height;
    Color* pixels;
    Canvas(int width, int height) {
        this->width = width;
        this->height = height;
        this->pixels = new Color[height * width];
    }
    void set_pixel(int x, int y, Color color) {
        if (x >= 0 && x < width && y >= 0 && y < height)
            this->pixels[y * width + x] = color;
        else
            std::cerr << "Pixel out of bounds: " << x << ", " << y << std::endl;
    }
    Color get_pixel(int x, int y) { return this->pixels[y * width + x]; }
    void write_ppm() {
        std::cout << "P3\n" << width << ' ' << height << "\n255\n";
        for (int j = height - 1; j >= 0; --j) {
            std::cerr << "\rLines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < width; ++i) {
                Color pixel_color = this->get_pixel(i, j);
                std::cout << static_cast<int>(pixel_color.r * 255) << ' '
                          << static_cast<int>(pixel_color.g * 255) << ' '
                          << static_cast<int>(pixel_color.b * 255) << '\n';
            }
        }
        std::cerr << "\nDone.\n";
    }
};

#endif  // !CANVAS