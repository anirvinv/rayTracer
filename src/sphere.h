#ifndef SPHERE

#define SPHERE

#include <math.h>

#include "point3.h"
#include "ray.h"

class entity {
   public:
    virtual double intersection_t_value(ray& ray) = 0;
    virtual vec3 get_unit_normal(point3& point) = 0;
};

class sphere : public entity {
   public:
    double radius;
    point3& center;
    sphere(double radius, point3& center);

    double intersection_t_value(ray& ray);
    vec3 get_unit_normal(point3& point);
};

sphere::sphere(double radius, point3& center) : center(center) {
    this->radius = radius;
}

double sphere::intersection_t_value(ray& ray) {
    vec3 oc = ray.origin - center;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}
vec3 sphere::get_unit_normal(point3& point) {
    vec3 x = vec3(point - center);
    x = x / radius;
    return x;
}

#endif  // !SPHERE