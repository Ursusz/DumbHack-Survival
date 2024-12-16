#include "../header/Treasure.h"

#include "../header/Player.h"

Treasure::~Treasure() {
    deleteInstance();
}

Treasure::Treasure(const myVec &position, const myVec &velocity, const std::string &texture_path,
                   bool hitAble, bool collidable, bool isDynamic, bool isAvailable, int drawPriority)
    : Entity(position, velocity, texture_path, hitAble, collidable, isDynamic, drawPriority)
    , m_isAvailable(isAvailable)
{}

Treasure* Treasure::instance(const myVec &position, const myVec &velocity, const std::string &texture_path,
                                bool hitAble, bool collidable, bool isDynamic, bool isAvailable, int drawPriority) {
    if(uniqueInstance == nullptr) {
        uniqueInstance = new Treasure(position, velocity, texture_path, hitAble, collidable, isDynamic, isAvailable, drawPriority);
    }
    return uniqueInstance;
}

Treasure* Treasure::uniqueInstance = nullptr;

void Treasure::draw(sf::RenderTarget &target, int frame) {
    if(is_available() && frame > SPAWN_TIME) {
        Entity::draw(target);
    }
}

bool Treasure::canHit(int) {
    return false;
}

void Treasure::takeDamage(int damage) {
    if(hitPoints > 0) {
        if (hitPoints - damage <= 100) {
            hitPoints -= damage;
        }
    }else{
        Entity::stopCollission();
        m_isAvailable = false;
    }
}

bool Treasure::is_available() const {
    return m_isAvailable;
}

void Treasure::deleteInstance() {
    if(uniqueInstance != nullptr) {
        delete uniqueInstance;
        uniqueInstance = nullptr;
    }
}

void Treasure::interactWith(Entity &other, int frame) {
    if(uniqueInstance && this->is_available() && frame > SPAWN_TIME) {
        if(auto playerptr = dynamic_cast<Player*> (&other)) {
            this->takeDamage(100);
            std::random_device rd;
            std::default_random_engine rng(rd());
            std::uniform_int_distribution<int> uniform_dist(0, 1);
            int bonus = uniform_dist(rng);

            switch (bonus) {
                case 0:
                    playerptr->takeBonus(10, "damage");
                    break;
                case 1:
                    playerptr->takeBonus(5, "hit_cooldown_reduction");
                    break;
                default:
                    break;
            }
        }
    }
}

bool Treasure::hasInstance() {
    return uniqueInstance != nullptr;
}
