#ifndef WORLD
#define WORLD

#include <vector>

#include "entity.h"
#include "lighting.h"

class World {
   public:
    std::vector<Entity> entities;
    Light light_source;

    World() {}
    World(std::vector<Entity> entities, Light light_source)
        : entities(entities), light_source(light_source) {}
    void set_entities(std::vector<Entity> entities) {
        this->entities = entities;
    }
    void set_light_source(Light light_source) {
        this->light_source = light_source;
    }
};

#endif  // !WORLD