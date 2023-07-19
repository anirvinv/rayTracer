#ifndef RAY
#define RAY

#include "matrix.h"
#include "tuple.h"
class Ray {
   public:
    Tuple origin;
    Tuple direction;
    Ray(Tuple origin, Tuple direction);
    Tuple get_point(double t);
};

Ray::Ray(Tuple origin, Tuple direction)
    : origin(origin), direction(direction) {}

Tuple Ray::get_point(double t) { return origin + direction * t; }

Ray transform_ray(Ray other, Matrix m) {
    return Ray(m * other.origin, m * other.direction);
}

#endif  // !RAY