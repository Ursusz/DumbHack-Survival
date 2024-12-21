#include "../header/CollissionManager.h"

CollissionManager::~CollissionManager() {
    main_entities.clear();
    entities_to_verify_collission.clear();
}

bool CollissionManager::entitiesAreColliding(const Entity &e1, const Entity &e2) {
    if(e1.canCollide() && e2.canCollide()) {
        if(e2.getPositionFromComp().getX() - e2.getHalfWidth() < e1.getPositionFromComp().getX() + e1.getHalfWidth() &&
            e2.getPositionFromComp().getX() + e2.getHalfWidth() > e1.getPositionFromComp().getX() - e1.getHalfWidth() &&
            e2.getPositionFromComp().getY() - e2.getHalfHeight() < e1.getPositionFromComp().getY() + e1.getHalfHeight() &&
            e2.getPositionFromComp().getY() + e2.getHalfHeight() > e1.getPositionFromComp().getY() - e1.getHalfHeight())
            return true;
    }
    return false;
}

void CollissionManager::checkCollisions(Entity &e1, Entity &e2, int frame) {
    if (entitiesAreColliding(e1, e2)) {

        e2.interactWith(e1, frame);
        m_collision.setOverlap(e1, e2);

        if(e1.canMove() && e2.canCollide()) {
            if (m_collision.isHorizontalOverlap()) {
                if (m_collision.isLeftOverlap()) {
                    e1.setPositionInComp(e1.getPositionFromComp() + myVec(m_collision.getOverlapX(), 0.0f));
                } else {
                    e1.setPositionInComp(e1.getPositionFromComp() - myVec(m_collision.getOverlapX(), 0.0f));
                }
            } else {
                if (m_collision.isTopOverlap()) {
                    e1.setPositionInComp(e1.getPositionFromComp() + myVec(0.0f, m_collision.getOverlapY()));
                } else {
                    e1.setPositionInComp(e1.getPositionFromComp() - myVec(0.0f, m_collision.getOverlapY()));
                }
            }
        }
    }
}


void CollissionManager::add_main_entities(Entity *entity) {
    main_entities.push_back(entity);
}

void CollissionManager::add_entities_to_verify_collission(Entity *entity) {
    entities_to_verify_collission.push_back(entity);
}

void CollissionManager::verifyAllCollissions(int frame) {
    for(auto& entity1 : main_entities) {
        for(auto& entity2 : entities_to_verify_collission) {
            checkCollisions(*entity1, *entity2, frame);
        }
    }
}

void CollissionManager::clear_main_entities() {
    main_entities.clear();
}
