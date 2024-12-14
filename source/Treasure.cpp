#include "../header/Treasure.h"

#include "../header/Player.h"


Treasure::Treasure(const myVec &position, const myVec &velocity, const std::string &texture_path,
                   bool hitAble, bool collidable, bool isDynamic, bool isAvailable = true)
    : Entity(position, velocity, texture_path, hitAble, collidable, isDynamic)
    , m_isAvailable(isAvailable)
{}

std::shared_ptr<Treasure> Treasure::instance(const myVec &position, const myVec &velocity, const std::string &texture_path,
                                bool hitAble, bool collidable, bool isDynamic, bool isAvailable) {
    if(uniqueInstance == nullptr) {
        uniqueInstance = std::make_shared<Treasure>(position, velocity, texture_path, hitAble, collidable, isDynamic, isAvailable);
    }
    return uniqueInstance;
}

std::shared_ptr<Treasure> Treasure::uniqueInstance = nullptr;

bool Treasure::is_available() const {
    return m_isAvailable;
}

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
        if (hitPoints - damage <= 100)
            hitPoints -= damage;
    }
    if(hitPoints <= 0) {
        m_isAvailable = false;
    }
}

void Treasure::interactWith(Entity &other, int frame) {
    if(this->is_available() && frame > SPAWN_TIME) {
        if(auto playerptr = dynamic_cast<Player*> (&other)) {
            this->takeDamage(100);
            std::random_device rd;
            std::default_random_engine rng(rd());
            std::uniform_int_distribution<int> uniform_dist(0, 1);
            int bonus = uniform_dist(rng);
            switch (bonus) {
                case 0:
                    playerptr->takeBonus(100, "damage");
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

std::shared_ptr<Entity> Treasure::clone() const {
    throw std::logic_error("Clone not allowed for Singleton");
}