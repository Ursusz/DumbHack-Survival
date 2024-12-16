#pragma once

#include <vector>

#include "../header/ComputeCollision.h"
#include "../header/Entity.h"

class CollissionManager : ComputeCollision{
    ComputeCollision m_collision;
    std::vector<Entity*> main_entities;
    std::vector<Entity*> entities_to_verify_collission;
    std::vector<Entity*> tiles;
    bool entitiesAreColliding(Entity& e1, Entity& e2);
public:
    void checkCollisions(Entity& e1, Entity& e2, int frame);
    void add_main_entities(Entity* entity);
    void add_entities_to_verify_collission(Entity* entity);
    void add_entities_to_tiles(Entity* entity);
    void clear_main_entities();

    void verifyAllCollissions(int frame);
};