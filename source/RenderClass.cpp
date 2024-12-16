#include "../header/RenderClass.h"


void RenderClass::addEntity(Entity* entity) {
    entities.push_back(entity);

    std::sort(entities.begin(), entities.end(),
        [](Entity* e1, Entity* e2) {
            return e1->getDrawPriority() < e2->getDrawPriority();
        });
}

void RenderClass::drawAll(sf::RenderTarget &target) {
    for(auto* entity : entities) {
        entity->draw(target);
    }
}
