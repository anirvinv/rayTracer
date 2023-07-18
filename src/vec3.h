#ifndef VEC3

#define VEC3

#include "point3.h"
class vec3 {
   public:
    double x, y, z;
    vec3(double x, double y, double z);

    double dot(const vec3& other);

    vec3 operator+(const vec3& other) const {
        return vec3(x + other.x, y + other.y, z + other.z);
    }
    vec3 operator-(const vec3& other) const { return *this + (other * -1); }
    vec3 operator*(const double& other) const {
        return vec3(x * other, y * other, z * other);
    }
    vec3 operator/(const double& other) const { return *this * (1 / other); }
    bool operator==(const vec3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

vec3::vec3(double x, double y, double z) : x(x), y(y), z(z) {}

double vec3::dot(const vec3& other) {
    return x * other.x + y * other.y + z * other.z;
}
#endif  // !VEC3