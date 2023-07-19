#ifndef ENTITY

#define ENTITY

#include <math.h>

#include "ray.h"
#include "vec3.h"

typedef struct Color {
    double r;
    double g;
    double b;
} Color;

class Entity {
   public:
    Color color = {0.95, 0.32, 0.16};
    virtual long double intersection_t_value(Ray& Ray) = 0;
    virtual Vec3 get_unit_normal(Point3 point) = 0;
};

class Sphere : public Entity {
   public:
    double radius;
    Point3 center;
    Sphere(double radius, Point3 center);

    long double intersection_t_value(Ray& Ray);
    Vec3 get_unit_normal(Point3 point);
};

class Plane : public Entity {
   public:
    Vec3 normal;
    Point3 point;
    Plane(Vec3 normal, Point3 point);

    long double intersection_t_value(Ray& Ray);
    Vec3 get_unit_normal(Point3 point);
};

Sphere::Sphere(double radius, Point3 center) : center(center) {
    this->radius = radius;
}

long double Sphere::intersection_t_value(Ray& Ray) {
    Vec3 oc = Vec3(Ray.origin - center);
    double a = Ray.direction.dot(Ray.direction);
    double b = 2.0 * oc.dot(Ray.direction);
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}
Vec3 Sphere::get_unit_normal(Point3 point) {
    Vec3 x = Vec3(point - center);
    x = x / radius;
    return x;
}

Plane::Plane(Vec3 normal, Point3 point) : normal(normal), point(point) {}
Vec3 Plane::get_unit_normal(Point3 point) { return normal; }
long double Plane::intersection_t_value(Ray& Ray) {
    long double t = (static_cast<Vec3>(point - Ray.origin)).dot(normal) /
                    Ray.direction.dot(normal);
    if (t < 0) {
        return -1.0;
    } else {
        return t;
    }
}

#endif  // !ENTITY