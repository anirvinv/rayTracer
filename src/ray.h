#ifndef RAY
#define RAY

#include "vec3.h"

class Ray {
   public:
    Point3& origin;
    Vec3& direction;
    Ray(Point3& origin, Vec3& direction);
    Point3 get_point(double t);
};

Ray::Ray(Point3& origin, Vec3& direction)
    : origin(origin), direction(direction) {}

Point3 Ray::get_point(double t) {
    Point3 scaledDir = Point3(direction * t);
    return origin + scaledDir;
}
#endif  // !RAY