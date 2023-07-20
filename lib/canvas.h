#ifndef CANVAS
#define CANVAS

#include <iostream>

#include "entity.h"

class Canvas {
   public:
    int width, height;
    Color* pixels;
    Canvas(int width, int height) {
        if (width % 2 != 0 || height % 2 != 0)
            throw std::invalid_argument("Canvas dimensions must be even");

        this->width = width;
        this->height = height;
        this->pixels = new Color[height * width];
    }
    void set_pixel(int x, int y, Color color) {
        // centered at (0,0)
        // bounds for x is -width/2 to width/2
        // bounds for y is -height/2 to height/2
        x += width / 2;
        y += height / 2;
        if (x >= 0 && x < width && y >= 0 && y < height)
            this->pixels[y * width + x] = color;
        else
            std::cerr << "set pixel out of bounds: " << x << ", " << y
                      << std::endl;
    }
    Color get_pixel(int x, int y) {
        x += width / 2;
        y += height / 2;
        if (x >= 0 && x < width && y >= 0 && y < height)
            return this->pixels[y * width + x];
        else
            std::cerr << "get pixel out of bounds: " << x << ", " << y
                      << std::endl;
        return {0, 0, 0};
    }
    void write_ppm() {
        std::cout << "P3\n" << width << ' ' << height << "\n255\n";
        for (int j = height - 1; j >= 0; --j) {
            std::cerr << "\rLines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < width; ++i) {
                Color pixel_color = this->pixels[j * width + i];
                std::cout << static_cast<int>(pixel_color.r * 255) << ' '
                          << static_cast<int>(pixel_color.g * 255) << ' '
                          << static_cast<int>(pixel_color.b * 255) << '\n';
            }
        }
        std::cerr << "\nDone.\n";
    }
};

#endif  // !CANVAS