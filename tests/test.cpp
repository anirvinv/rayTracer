#include <algorithm>
#include <iostream>
#include <vector>

#include "../lib/entity.h"
#include "../lib/matrix.h"
#include "../lib/ray.h"
#include "../lib/transformations.h"
#include "../lib/tuple.h"

bool double_eq(double a, double b) { return abs(a - b) < Tuple::EPSILON; }

int tuple_test() {
    Tuple v1 = vector_tuple(1, 2, 3);
    Tuple v2 = vector_tuple(2, 3, 4);
    if (v1 + v2 != vector_tuple(3, 5, 7)) {
        std::cout << "v1 + v2 check failed" << std::endl;
        return 1;
    }
    if (v1 - v2 != vector_tuple(-1, -1, -1)) {
        std::cout << "v1 - v2 check failed" << std::endl;
        return 1;
    }
    if (v1 * 2 != vector_tuple(2, 4, 6)) {
        std::cout << "v1 * 2 check failed" << std::endl;
        return 1;
    }
    if (v1 / 2 != vector_tuple(0.5, 1, 1.5)) {
        std::cout << "v1 / 2 check failed" << std::endl;
        return 1;
    }
    if (v1.dot(v2) != 20) {
        std::cout << "v1 dot v2 check failed" << std::endl;
        return 1;
    }
    if (magnitude(v1) != sqrt(14)) {
        std::cout << "magnitude check failed" << std::endl;
        return 1;
    }
    if (normalize(v1) !=
        vector_tuple(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14))) {
        std::cout << "normalize check failed" << std::endl;
        return 1;
    }
    return 0;
}

int matrix_test() {
    double m1_data[] = {1, 2, 3, 5.5, 6.5, 7.5, 9, 10, 11};
    Matrix m1 = Matrix(3, 3, m1_data);

    double m2_data[] = {1, 2, 3, 5.5, 6.5, 7.5};
    Matrix m2 = Matrix(3, 2, m2_data);

    double product_data[] = {26.5, 35.5, 73.75, 103, 110.5, 155.5};
    Matrix product = Matrix(3, 2, product_data);

    double m3_data[] = {5, 6, 6, 8, 2, 2, 2, 8, 6, 6, 2, 8, 2, 3, 6, 7};
    Matrix m3 = Matrix(4, 4, m3_data);

    // clang-format off
    double m4_data[] = {1, 0, 0, 1500, 
                        0, 1, 0, 0, 
                        0, 0, 1, 0, 
                        0, 0, 0, 1};
    // clang-format on
    Matrix m4 = Matrix(4, 4, m4_data);

    if (m1 * m2 != product) {
        std::cout << "m1 * m2 != product" << std::endl;
        product.print();
        std::cout << '\n';
        (m1 * m2).print();
        return 1;
    }
    if (abs(m1.submatrix(0, 0).submatrix(0, 0).get(0, 0) - 11) >
        Tuple::EPSILON) {
        std::cout << "submatrix check failed" << std::endl;
        return 1;
    }
    if (abs(m1.determinant() - 0) > Tuple::EPSILON) {
        std::cout << "m1 determinant check failed" << std::endl;
        return 1;
    }
    if (abs(m3.determinant() - -8) > Tuple::EPSILON) {
        std::cout << "m3 determinant check failed" << std::endl;
        return 1;
    }
    if (abs(m4.determinant() - 1) > Tuple::EPSILON) {
        std::cout << "m4 determinant check failed" << std::endl;
        return 1;
    }

    return 0;
}

int sphere_intersection_test() {
    Sphere sphere = Sphere();
    Ray ray = Ray(point_tuple(0, 0, -5), vector_tuple(0, 0, 1));
    std::vector<Intersection> points = sphere.intersections(ray);
    sort(points.begin(), points.end());
    if (!(points.size() == 2 && abs(points[0].t_value - 4) < Tuple::EPSILON &&
          abs(points[1].t_value - 6) < Tuple::EPSILON)) {
        std::cout << "failed intersection check" << std::endl;
        return 1;
    }

    Ray ray2 = Ray(point_tuple(0, 0, 0), vector_tuple(0, 0, 1));
    points = sphere.intersections(ray2);
    sort(points.begin(), points.end());
    if (!(points.size() == 2 && abs(points[0].t_value - -1) < Tuple::EPSILON &&
          abs(points[1].t_value - 1) < Tuple::EPSILON)) {
        std::cout << "failed intersection check" << std::endl;
        return 1;
    }
    return 0;
}

int transformation_test() {
    Ray r = Ray(point_tuple(1, 2, 3), vector_tuple(0, 1, 0));
    Ray r2 = transform_ray(r, translation(3, 4, 5));
    if (r2.origin != point_tuple(4, 6, 8)) {
        std::cout << "Translated ray origin check failed" << std::endl;
        return 1;
    }
    if (r2.direction != vector_tuple(0, 1, 0)) {
        std::cout << "Translated ray direction check failed" << std::endl;
        return 1;
    }

    r = Ray(point_tuple(1, 2, 3), vector_tuple(0, 1, 0));
    r2 = transform_ray(r, scaling(2, 3, 4));
    if (r2.origin != point_tuple(2, 6, 12)) {
        std::cout << "Scaled ray origin check failed" << std::endl;
        return 1;
    }
    if (r2.direction != vector_tuple(0, 3, 0)) {
        std::cout << "Scaled ray direction check failed" << std::endl;
        return 1;
    }

    Sphere s = Sphere();
    s.set_transform(scaling(2, 2, 2));
    if (s.transformation != scaling(2, 2, 2)) {
        std::cout << "Transformation is not set oh sphere" << std::endl;
        return 1;
    }

    // intersetcing scaled sphere with a ray
    r = Ray(point_tuple(0, 0, -5), vector_tuple(0, 0, 1));
    std::vector<Intersection> xs = s.intersections(r);
    sort(xs.begin(), xs.end());
    if (!(xs.size() == 2 && double_eq(xs[0].t_value, 3) &&
          double_eq(xs[1].t_value, 7))) {
        std::cout << "Scaled sphere intersection failed" << std::endl;
        return 1;
    }

    // interseting transalted sphere with a ray
    s.set_transform(translation(5, 0, 0));
    xs = s.intersections(r);
    if (xs.size() != 0) {
        std::cout << "Translated sphere intersection failed" << std::endl;
        return 1;
    }

    return 0;
}

int main() {
    if (tuple_test()) {
        return 1;
    }
    if (matrix_test()) {
        return 1;
    }
    if (sphere_intersection_test()) {
        return 1;
    }
    if (transformation_test()) {
        return 1;
    }
    std::cout << "All tests passed." << std::endl;
    return 0;
}
