#include <iostream>

#include "../lib/entity.h"
#include "../lib/matrix.h"
#include "../lib/ray.h"
#include "../lib/transformations.h"
#include "../lib/tuple.h"

int tuple_test() {
    Tuple v1 = vector(1, 2, 3);
    Tuple v2 = vector(2, 3, 4);
    if (v1 + v2 != vector(3, 5, 7)) {
        std::cout << "v1 + v2 check failed" << std::endl;
        return 1;
    }
    if (v1 - v2 != vector(-1, -1, -1)) {
        std::cout << "v1 - v2 check failed" << std::endl;
        return 1;
    }
    if (v1 * 2 != vector(2, 4, 6)) {
        std::cout << "v1 * 2 check failed" << std::endl;
        return 1;
    }
    if (v1 / 2 != vector(0.5, 1, 1.5)) {
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
    if (normalize(v1) != vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14))) {
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

    return 0;
}

int transform_test() {
    Ray ray = Ray(point(0, 0, 0), vector(0, 0, 1));
    Sphere sphere = Sphere(1, point(1, 1, 1));
    Sphere translated = sphere.transform(translation(-1, -1, -1));

    if (translated.intersection_t_value(ray) == -1) {
        return 0;
    }
    return 1;
    return 0;
}

int main() {
    if (tuple_test()) {
        return 1;
    }
    if (matrix_test()) {
        return 1;
    }
    if (transform_test()) {
        return 1;
    }
    std::cout << "All tests passed." << std::endl;
    return 0;
}
