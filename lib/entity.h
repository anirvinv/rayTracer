#ifndef ENTITY

#define ENTITY

#include <math.h>

#include <vector>

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

typedef struct Material {
    Color color = {1, 1, 1};
    double ambient = 0.1;
    double diffuse = 0.9;
    double specular = 0.9;
    double shininess = 200.0;
} Material;

class Entity;
typedef struct Intersection {
    double t_value;
    Entity* entity;
} Intersection;
class Entity {
   public:
    Material material;
    virtual std::vector<Intersection> intersections(Ray& Ray) = 0;
    virtual Tuple get_unit_normal(Tuple point) = 0;
};

class Sphere : public Entity {
   public:
    Tuple center;
    Matrix transformation;
    double radius;
    Sphere(double radius, Tuple center)
        : center(center), transformation(identity_matrix(4)), radius(radius) {}

    std::vector<Intersection> intersections(Ray& Ray) {
        Tuple oc = Ray.origin - center;
        double a = Ray.direction.dot(Ray.direction);
        double b = 2.0 * oc.dot(Ray.direction);
        double c = oc.dot(oc) - radius * radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return std::vector<Intersection>{};
        } else {
            std::vector<Intersection> res{
                {(-b - sqrt(discriminant)) / (2.0 * a), this},
                {(-b + sqrt(discriminant)) / (2.0 * a), this}};
            return res;
        }
    }
    Tuple get_unit_normal(Tuple point) {
        Tuple x = point - center;
        x = x / radius;
        // x = (transformation.inverse()).transpose() * x;
        // x = normalize(x);
        x.w = 0;
        return x;
    }

    Sphere transform(Matrix m) {
        Sphere result = Sphere(radius, m * center);
        result.transformation = (transformation * m);
        result.material = material;
        return result;
    }
};

class Plane : public Entity {
   public:
    Tuple normal;
    Tuple point;
    Plane(Tuple normal, Tuple point) : normal(normal), point(point) {}

    std::vector<Intersection> intersections(Ray& Ray) {
        double t = (point - Ray.origin).dot(normal) / Ray.direction.dot(normal);
        if (t < 0) {
            return std::vector<Intersection>{};
        } else {
            std::vector<Intersection> res{{t, this}};
            return res;
        }
    }
    Tuple get_unit_normal(Tuple point) {
        (void)point;  // to silence compiler warning about unused parameters
        return normal;
    }
};

#endif  // !ENTITY