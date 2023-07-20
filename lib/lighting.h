#ifndef LIGHTING
#define LIGHTING

#include "entity.h"

struct Light {
    Tuple position = point_tuple(0, 0, 0);
    Color intensity = {1, 1, 1};
};

Color tuple_to_color(Tuple t) { return {t.x, t.y, t.z}; }
Tuple color_to_tuple(Color c) { return {c.r, c.g, c.b, Tuple::VECTOR}; }

Color lighting(Material material, Light light_source, Tuple point,
               Tuple eye_vector, Tuple normal_vector) {
    Tuple effective_color =
        color_to_tuple(material.color * light_source.intensity);
    Tuple light_vector = normalize(light_source.position - point);
    Color ambient = tuple_to_color(effective_color) * material.ambient;
    double light_dot_normal = light_vector.dot(normal_vector);
    Color diffuse = {0, 0, 0};
    Color specular = {0, 0, 0};
    if (light_dot_normal >= 0) {
        diffuse = tuple_to_color(effective_color * material.diffuse *
                                 light_dot_normal);
        Tuple reflect_vector = reflect(light_vector * -1, normal_vector);
        double reflect_dot_eye = reflect_vector.dot(eye_vector);
        if (reflect_dot_eye > 0) {
            double factor = pow(reflect_dot_eye, material.shininess);
            specular = light_source.intensity * material.specular * factor;
        }
    }
    return ambient + diffuse + specular;
}

#endif  // !LIGHTING
