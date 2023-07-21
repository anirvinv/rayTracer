#ifndef WORLD
#define WORLD

#include <algorithm>
#include <memory>
#include <vector>

#include "entity.h"
#include "lighting.h"

typedef struct IntersectionInfo {
    double t_value;
    Entity* entity_ptr = nullptr;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    bool inside;
} IntersectionInfo;

class World {
   public:
    std::vector<Entity*> entities;
    Light light_source;

    World() {}
    ~World() {}
    World(std::vector<Entity*> entities, Light light_source)
        : entities(entities), light_source(light_source) {}
    void set_entities(std::vector<Entity*> entities) {
        this->entities = entities;
    }
    void set_light_source(Light light_source) {
        this->light_source = light_source;
    }
    std::vector<Intersection> intersections(Ray ray) {
        std::vector<Intersection> res;
        for (Entity* entity_ptr : entities) {
            std::vector<Intersection> entity_xs =
                entity_ptr->intersections(ray);
            for (Intersection i : entity_xs) {
                res.push_back(i);
            }
        }
        sort(res.begin(), res.end());
        return res;
    }
};

IntersectionInfo compute_info(Intersection i, Ray ray) {
    double t_value = i.t_value;
    Entity* entity_ptr = i.entity_ptr;

    Tuple point = ray.get_point(t_value);
    Tuple eyev = normalize(ray.direction * -1);
    Tuple normalv = vector_tuple(0, 0, 0);
    try {
        normalv = entity_ptr->get_unit_normal(point);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    bool inside = false;
    if (normalv.dot(eyev) < 0) {
        normalv = normalv * -1;
        inside = true;
    }

    IntersectionInfo info = {t_value, entity_ptr, point, eyev, normalv, inside};

    return info;
}

Color shade_hit(World world, IntersectionInfo info) {
    return lighting(info.entity_ptr->material, world.light_source, info.point,
                    info.eyev, info.normalv);
}

Color color_at(World world, Ray ray) {
    std::vector<Intersection> xs = world.intersections(ray);
    if (xs.size() == 0) {
        return {0, 0, 0};
    }
    Intersection i = xs[0];
    size_t ptr = 0;
    while (ptr < xs.size()) {
        if (xs[ptr].t_value >= 0) {
            i = xs[ptr];
            break;
        }
        ptr++;
    }
    if (i.t_value < 0) {
        return {0, 0, 0};
    }
    IntersectionInfo info = compute_info(i, ray);
    return shade_hit(world, info);
}
/**
 * Allocates memory on heap, must delete entities after usage
 */
World* default_world() {
    Light light_source = {point_tuple(-10, 10, -10), {1, 1, 1}};
    Sphere* s1 = new Sphere();
    s1->material.color = {0.8, 1.0, 0.6};
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;
    Sphere* s2 = new Sphere();
    s2->set_transform(scaling(0.5, 0.5, 0.5));
    std::vector<Entity*> entities{s1, s2};
    World* world = new World(entities, light_source);
    return world;
}

void delete_default_world(World* ptr) {
    for (Entity* entity_ptr : ptr->entities) {
        delete entity_ptr;
    }
    delete ptr;
}

#endif  // !WORLD