#ifndef TUPLE
#define TUPLE

#include "math.h"

class Tuple {
   public:
    static constexpr double EPSILON = 0.000001;

   public:
    enum { vector, point };
    double x, y, z;
    int w;
    // w=0 for vector, w=1 for point

    Tuple(double x, double y, double z, int w) : x(x), y(y), z(z), w(w) {}
    Tuple operator+(const Tuple& other) const {
        return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    Tuple operator-(const Tuple& other) const {
        return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    Tuple operator*(const double& other) const {
        return Tuple(x * other, y * other, z * other, w * other);
    }
    Tuple operator/(const double& other) const {
        return Tuple(x / other, y / other, z / other, w / other);
    }
    bool operator==(const Tuple& other) const {
        return abs(x - other.x) < EPSILON && abs(y - other.y) < EPSILON &&
               abs(z - other.z) < EPSILON && w == other.w;
    }
    bool operator!=(const Tuple& other) const { return !(*this == other); }
    double dot(const Tuple& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
};

Tuple point(double x, double y, double z) {
    return Tuple(x, y, z, Tuple::point);
}
Tuple vector(double x, double y, double z) {
    return Tuple(x, y, z, Tuple::vector);
}
double magnitude(const Tuple& t) { return sqrt(t.dot(t)); }
Tuple normalize(const Tuple& t) { return t / magnitude(t); }
Tuple cross(const Tuple& a, const Tuple& b) {
    return vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                  a.x * b.y - a.y * b.x);
}

#endif  // !TUPLE