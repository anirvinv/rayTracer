#ifndef RAY
#define RAY

#include "point3.h"
#include "vec3.h"

class ray {
   public:
    point3& origin;
    vec3& direction;
    ray(point3& origin, vec3& direction);
};

ray::ray(point3& origin, vec3& direction)
    : origin(origin), direction(direction) {}

#endif  // !RAY