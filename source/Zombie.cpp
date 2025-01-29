#include "../header/Zombie.h"

#include "../header/Player.h"

Zombie::Zombie(const myVec &position, const myVec &velocity, const std::string &texture_path, bool hitAble, bool collidable, bool isDynamic, int drawPriority)
    : Entity(position, velocity, texture_path, hitAble, collidable, isDynamic, drawPriority)
    , heartSprite(std::make_shared<SpriteComponent>("assets/heart.png"))
    , hitBuffer(std::make_shared<sf::SoundBuffer>())
{
    m_generator.setWorldSize({23, 40});
    m_generator.setHeuristic(AStar::Heuristic::euclidean);
    m_generator.setDiagonalMovement(true);

    if(!hitBuffer->loadFromFile("assets/zombiePunch.ogg")) {
        throw std::runtime_error("Error loading zombiePunch.ogg");
    }
    hitSound.setBuffer(*hitBuffer);
    hitSound.setVolume(15.0f);
}

Zombie::Zombie(const Zombie& rhs)
    : Entity(rhs)
    , heartSprite((rhs).heartSprite->clone())
    , m_generator(rhs.m_generator)
    , hitPoints(rhs.hitPoints)
    , isAlive(rhs.isAlive)
    , hitBuffer(rhs.hitBuffer)
{
    hitSound.setBuffer(*hitBuffer);
    hitSound.setVolume(15.0f);
}

std::string &Zombie::getDirection() {
    return m_direction;
}

void Zombie::takeDamage(int damage) {
    if(hitPoints > 0) {
        if (hitPoints - damage <= 100) {
            //this prevents the healing from vending machine to give the zombie more than 100hp which causes the program to crash
            if(hitPoints - damage <= 0) {
                hitPoints = 0;
                isAlive = false;
            }else {
                hitPoints -= damage;
            }
        }else {
            hitPoints = 100;
        }
    }
}

bool Zombie::canHit(int frame) {
    if((lastHit == 0 || frame - lastHit > 180) && isAlive) {
        lastHit = frame;
        hitSound.play();
        return true;
    }
    return false;
}


void Zombie::interactWith(Entity &other, int frame) {
    if(this->canHit(frame) && other.canTakeDamage()) {
        other.takeDamage(10);
    }
}

void Zombie::drawHP(sf::RenderTarget &m_window) {
    for(int i = 0; i < std::ceil((float)hitPoints/20.0f); i++) {
        hearts[i] = heartSprite->getSprite();
        hearts[i].setColor(sf::Color::Green);
        hearts[i].setOrigin(8, 8);
        hearts[i].setScale(1, 1);
        hearts[i].setPosition(Entity::getPositionFromComp().getX() - 26 + i*12, Entity::getPositionFromComp().getY()-48);
        if(hitPoints%20 != 0) {
            hearts[hitPoints/20].setTextureRect(sf::IntRect(17, 0, 16, 16));
        }
        if(i < std::ceil((float)hitPoints/20.0f)) {
            m_window.draw(hearts[i]);
        }
    }
}

void Zombie::followPlayer(const myVec &playerPos) {
    if(isAlive) {
        if(this->getPositionFromComp().distance(playerPos) > 100) {
            auto path = m_generator.findPath({(int)playerPos.getY()/48, (int)playerPos.getX()/48},
                            {(int)this->getPositionFromComp().getY()/48, (int)this->getPositionFromComp().getX()/48});
            if(this->getPositionFromComp()/48 != playerPos/48 && (int)path.size() > next) {
                //since every tile in the game is 48x48, here we are dividing the coordinates by 48 so we can get the location of the 23x40 matrix which is mapping the obstacles
                int currentTileX = (int)this->getPositionFromComp().getX() / 48;
                int currentTileY =(int) this->getPositionFromComp().getY() / 48;
                if(currentTileX != path.at(next).y || currentTileY != path.at(next).x) {
                    direction = myVec(path.at(next).y * 48 + 24 - this->getPositionFromComp().getX(), path.at(next).x * 48 + 24 - this->getPositionFromComp().getY());
                }else {
                    next++;
                }
            }
        }else {
            direction = playerPos - this->getPositionFromComp();
        }
    }
    //49 is the distance between the center of the player and the zombie, +1 pixel so the zombie only pushes the player diagonally, on perpendicullar axes he wont push the player
    if(this->getPositionFromComp().distance(playerPos) > 49) {
        try {
            direction.normalize();
        }catch(const divideByZero& err) {
            std::cerr << "Division error: " << err.what() << std::endl;
        }

        direction *= 1.5f;
        this->updatePositionInComp(direction);
    }

    if(direction.getY() < 0 && std::abs(direction.getY()) > std::abs(direction.getX())) m_direction = "up";
    if(direction.getY() > 0 && std::abs(direction.getY()) > std::abs(direction.getX())) m_direction = "down";
    if(direction.getX() < 0 && std::abs(direction.getX()) > std::abs(direction.getY())) m_direction = "left";
    if(direction.getX() > 0 && std::abs(direction.getX()) > std::abs(direction.getY())) m_direction = "right";
}

bool Zombie::is_alive() const {
    return isAlive;
}

void Zombie::setObstacles(const std::vector<sf::Vector2i> &obs) {
    for(const auto& obstacle : obs) {
        m_generator.addCollision(AStar::Vec2i(obstacle.x, obstacle.y));
    }
}

std::shared_ptr<Entity> Zombie::clone() const {
    return std::make_shared<Zombie>(*this);
}

void Zombie::swap(Zombie &z1, Zombie &z2) noexcept{
    using std::swap;
    swap(z1.heartSprite, z2.heartSprite);
    swap(z1.lastHit, z2.lastHit);
    swap(z1.m_generator, z2.m_generator);
    z1.next = 2;
    swap(z1.hitPoints, z2.hitPoints);
    swap(z1.isAlive, z2.isAlive);
    swap(z1.hitBuffer, z2.hitBuffer);
    z1.hitSound.setBuffer(*z1.hitBuffer);
    z1.hitSound.setVolume(15.0f);
}

Zombie& Zombie::operator=(Zombie rhs) {
    Entity::operator=(rhs);
    swap(*this, rhs);
    return *this;
}

std::ostream& operator<<(std::ostream &os, const Zombie &zombie) {
    os << static_cast<const Entity&>(zombie);
    os << zombie.hitPoints << " " << zombie.lastHit << " " << zombie.direction << " " << zombie.next << " " << zombie.isAlive << " ";
    return os;
}