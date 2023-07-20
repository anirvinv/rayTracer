#ifndef TUPLE
#define TUPLE

#include "math.h"

class Tuple {
   public:
    static constexpr double EPSILON = 0.000001;

   public:
    enum { VECTOR, POINT };
    double x, y, z;
    int w;
    // w=0 for vector_tuple, w=1 for point_tuple

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
    void print() const {
        std::cerr << x << " " << y << " " << z << " " << w << std::endl;
    }
};

Tuple point_tuple(double x, double y, double z) {
    return Tuple(x, y, z, Tuple::POINT);
}
Tuple vector_tuple(double x, double y, double z) {
    return Tuple(x, y, z, Tuple::VECTOR);
}
double magnitude(const Tuple& t) { return sqrt(t.dot(t)); }
Tuple normalize(const Tuple& t) { return t / magnitude(t); }
Tuple cross(const Tuple& a, const Tuple& b) {
    return vector_tuple(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                        a.x * b.y - a.y * b.x);
}

Tuple reflect(const Tuple& in, const Tuple& normal) {
    return in - normal * 2 * in.dot(normal);
}

#endif  // !TUPLE