#ifndef TRANSFORMATIONS
#define TRANSFORMATIONS

#include <math.h>

#include "matrix.h"

Matrix translation(double x, double y, double z) {
    double res_data[] = {1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1};
    Matrix res = Matrix(4, 4, res_data);
    return res;
}

Matrix scaling(double x, double y, double z) {
    double res_data[] = {x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1};
    Matrix res = Matrix(4, 4, res_data);
    return res;
}

Matrix rotation_x(double radians) {
    // clockwise towards the x axis

    // clang-format off
    double res_data[] = {1, 0, 0, 0, 
                         0,cos(radians), -sin(radians), 0, 
                         0, sin(radians), cos(radians), 
                         0, 0, 0, 0, 1
                         };
    // clang-format on

    Matrix res = Matrix(4, 4, res_data);
    return res;
}
Matrix rotation_y(double radians) {
    // clock wise towards the y axis

    // clang-format off
    double res_data[] = {cos(radians), 0, sin(radians), 0, 
                         0, 1, 0, 0, 
                         -sin(radians), 0, cos(radians), 0, 
                         0, 0, 0, 1
                         };
    // clang-format on

    Matrix res = Matrix(4, 4, res_data);
    return res;
}
Matrix rotation_z(double radians) {
    // clockwise towards z axis

    // clang-format off

    double res_data[] = {cos(radians), -sin(radians), 0, 0, 
                         sin(radians), cos(radians), 0, 0, 
                         0, 0, 1, 0, 
                         0, 0, 0, 1
                         };
    // clang-format on

    Matrix res = Matrix(4, 4, res_data);
    return res;
}

Matrix shearing(double xy, double xz, double yx, double yz, double zx,
                double zy) {
    // clang-format off
    double res_data[] = {1, xy, xz, 0, 
                         yx, 1, yz, 0, 
                         zx, zy, 1, 0, 
                         0, 0, 0, 1
                         };
    // clang-format on
    Matrix res = Matrix(4, 4, res_data);
    return res;
}

#endif  // !TRANSFORMATIONS
