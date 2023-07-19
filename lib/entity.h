#ifndef ENTITY

#define ENTITY

#include <math.h>

#include "ray.h"
#include "tuple.h"

typedef struct Color {
    double r;
    double g;
    double b;

    Color operator+(Color other) {
        Color result = {this->r + other.r, this->g + other.g,
                        this->b + other.b};
        return result;
    }
    Color operator*(double scalar) {
        Color result = {this->r * scalar, this->g * scalar, this->b * scalar};
        return result;
    }
    Color operator*(Color other) {
        Color result = {this->r * other.r, this->g * other.g,
                        this->b * other.b};
        return result;
    }

} Color;

class Entity {
   public:
    Color color = {0.95, 0.32, 0.16};
    virtual double intersection_t_value(Ray& Ray) = 0;
    virtual Tuple get_unit_normal(Tuple point) = 0;
};

class Sphere : public Entity {
   public:
    double radius;
    Tuple center;
    Sphere(double radius, Tuple center) : center(center) {
        this->radius = radius;
    }

    double intersection_t_value(Ray& Ray) {
        Tuple oc = Ray.origin - center;
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
    Tuple get_unit_normal(Tuple point) {
        Tuple x = point - center;
        x = x / radius;
        return x;
    }

    Sphere transform(Matrix m) {
        Sphere result = Sphere(radius, m * center);
        result.color = color;
        return result;
    }
};

class Plane : public Entity {
   public:
    Tuple normal;
    Tuple point;
    Plane(Tuple normal, Tuple point) : normal(normal), point(point) {}

    double intersection_t_value(Ray& Ray) {
        double t = (point - Ray.origin).dot(normal) / Ray.direction.dot(normal);
        if (t < 0) {
            return -1.0;
        } else {
            return t;
        }
    }
    Tuple get_unit_normal(Tuple point) {
        (void)point;  // to silence compiler warning about unused parameters
        return normal;
    }
};

#endif  // !ENTITY