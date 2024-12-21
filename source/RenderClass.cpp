#include "../header/RenderClass.h"

RenderClass::~RenderClass() {
    entities.clear();
}

void RenderClass::addEntity(Entity* entity) {
    entities.push_back(entity);

    std::sort(entities.begin(), entities.end(),
        [](const Entity* e1, const Entity* e2) {
            return e1->getDrawPriority() < e2->getDrawPriority();
        });
}

void RenderClass::drawAll(sf::RenderTarget &target, int frame) {
    for(auto* entity : entities) {
        if(auto treasurePtr = dynamic_cast<Treasure*>(entity)) {
            treasurePtr->draw(target, frame);
            continue;
        }
        if(auto trapPtr = dynamic_cast<Trap*>(entity)) {
            trapPtr->draw(target, frame);
            continue;
        }
        entity->draw(target);
    }
}
