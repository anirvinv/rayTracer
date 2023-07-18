#ifndef RAY
#define RAY

#include "point3.h"
#include "vec3.h"

class ray {
   public:
    point3& origin;
    vec3& direction;
    ray(point3& origin, vec3& direction);
    point3 get_point(double t);
};

ray::ray(point3& origin, vec3& direction)
    : origin(origin), direction(direction) {}

point3 ray::get_point(double t) {
    point3 scaledDir = point3(direction * t);
    return origin + scaledDir;
}
#endif  // !RAY