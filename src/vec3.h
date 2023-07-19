#ifndef VEC3
#define VEC3

class Point3 {
   public:
    long double x, y, z;
    Point3(long double x, long double y, long double z);
    Point3 operator+(const Point3& other) const {
        return Point3(x + other.x, y + other.y, z + other.z);
    }
    Point3 operator-(const Point3& other) const {
        return Point3(x - other.x, y - other.y, z - other.z);
    }
};

class Vec3 {
   public:
    long double x, y, z;
    Vec3(long double x, long double y, long double z);
    Vec3(Point3 point) : x(point.x), y(point.y), z(point.z) {}
    long double dot(const Vec3 other);

    Vec3 operator+(const Vec3 other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }
    Vec3 operator-(const Vec3 other) const { return *this + (other * -1); }
    Vec3 operator*(const long double& other) const {
        return Vec3(x * other, y * other, z * other);
    }
    Vec3 operator/(const long double& other) const {
        return *this * (1 / other);
    }
    bool operator==(const Vec3 other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    explicit operator Point3() const { return Point3(x, y, z); }
};

Vec3::Vec3(long double x, long double y, long double z) : x(x), y(y), z(z) {}
long double Vec3::dot(const Vec3 other) {
    return x * other.x + y * other.y + z * other.z;
}

Point3::Point3(long double x, long double y, long double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

#endif  // !VEC3