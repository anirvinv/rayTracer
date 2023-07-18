#ifndef POINT3
#define POINT3

#include "vec3.h"

class point3 {
   public:
    double x, y, z;
    point3(double x, double y, double z);
    point3(vec3 v) : x(v.x), y(v.y), z(v.z){};
    point3 operator+(const point3& other) const {
        return point3(x + other.x, y + other.y, z + other.z);
    }
    point3 operator-(const point3& other) const {
        return point3(x - other.x, y - other.y, z - other.z);
    }
    operator vec3() { return vec3(x, y, z); }
};

point3::point3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

#endif  // !POINT3