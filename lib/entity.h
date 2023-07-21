#ifndef ENTITY

#define ENTITY

#include <math.h>

#include <vector>

#include "ray.h"
#include "tuple.h"

bool double_eq(double a, double b) { return abs(a - b) < Tuple::EPSILON; }
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
    bool operator==(Color other) {
        return double_eq(this->r, other.r) && double_eq(this->g, other.g) &&
               double_eq(this->b, other.b);
    }
    bool operator!=(Color other) { return !(*this == other); }
    void print() {
        std::cout << "Color(" << r << ", " << g << ", " << b << ")"
                  << std::endl;
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
    Entity* entity_ptr;

    Intersection(double t_value, Entity* entity_ptr)
        : t_value(t_value), entity_ptr(entity_ptr) {}

    bool operator<(Intersection& other) { return t_value < other.t_value; }
} Intersection;
class Entity {
   public:
    Matrix transformation;
    Matrix inverse_trans;
    Material material;
    Entity()
        : transformation(identity_matrix(4)),
          inverse_trans(identity_matrix(4)) {}
    virtual ~Entity() {}
    virtual std::vector<Intersection> intersections(Ray& Ray) = 0;
    virtual Tuple get_unit_normal(Tuple point) = 0;
};

class Sphere : public Entity {
   public:
    Tuple center;
    double radius;
    Sphere() : Entity(), center(point_tuple(0, 0, 0)), radius(1) {
        (void)center;
    }
    ~Sphere() {}
    std::vector<Intersection> intersections(Ray& ray) {
        Ray ray2 = transform_ray(ray, inverse_trans);

        Tuple oc = ray2.origin - center;
        double a = ray2.direction.dot(ray2.direction);
        double b = 2.0 * oc.dot(ray2.direction);
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
        // apply the inverse transformation to the point
        // to get the point in object space
        // then subtract the center of the sphere
        // and normalize the resulting vector
        point = inverse_trans * point;
        Tuple normal = point - center;
        normal.w = 0;
        normal = normalize(normal);
        return normal;
    }
    void set_transform(Matrix m) {
        this->transformation = m;
        this->inverse_trans = m.inverse();
    }
    Sphere transform(Matrix m) {
        Sphere result = Sphere();
        result.transformation = (transformation * m);
        result.inverse_trans = transformation.inverse();
        result.material = material;
        return result;
    }
};

#endif  // !ENTITY