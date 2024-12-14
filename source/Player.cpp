#include "../header/Player.h"


Player::Player(const myVec &position, const myVec &velocity, const std::string& texture_path, bool hitAble, bool collidable, bool isDynamic)
    : Entity(position, velocity, texture_path, hitAble, collidable, isDynamic)
    , m_cKeyboard(std::make_shared<KeyboardComponent>())
    , heartSprite(std::make_shared<SpriteComponent>("assets/heart.png"))
    , m_weapon(std::make_shared<Weapon>("assets/weapon.png"))

{}

Player::Player(const Player &rhs)
    : Entity(rhs)
    , m_cKeyboard(rhs.m_cKeyboard->clone())
    , m_weapon(rhs.m_weapon->clone())
    , semicircle(rhs.semicircle)
{}


bool Player::isKeyUp() const {
    return m_cKeyboard->up();
}

bool Player::isKeyDown() const {
    return m_cKeyboard->down();
}

bool Player::isKeyLeft() const {
    return m_cKeyboard->left();
}

bool Player::isKeyRight() const {
    return m_cKeyboard->right();
}

bool Player::isAlive() const {
    return hitPoints != 0;
}

void Player::takeDamage(int damage) {
    if(hitPoints > 0) {
        if (hitPoints - damage <= 100)
            //this prevents the healing from vending machine to give the player more than 100hp which causes the program to crash
            hitPoints -= damage;
    }
}

bool Player::canHit(int frame) {
    if(lastHit == 0 || frame - lastHit > hitCooldown) {
        lastHit = frame;
        return true;
    }
    return false;
}

void Player::interactWith(Entity &other, int frame) {
    if(this->canHit(frame) && other.canTakeDamage()) {
        other.takeDamage(damage);
    }
}


bool Player::isEnemyInFront(const myVec &enemyPos, const myVec &playerDirection, float range, float angleThreshHold) {
    if(this->getPositionFromComp().distance(enemyPos) > range) return false;
    myVec playerToEnemyVec = (this->getPositionFromComp()-enemyPos);
    try {
        playerToEnemyVec.normalize();
    }catch(const divideByZero& err) {
        std::cerr << "Division error: " << err.what() << std::endl;
    }

    float dotProduct = playerToEnemyVec.getX() * playerDirection.getX() + playerToEnemyVec.getY() * playerDirection.getY();

    float cosAngle = std::cos(angleThreshHold) * (3.14159f / 180.0f);
    return dotProduct <= cosAngle;
}


void Player::setKeyValue(int key, bool toggle) {
    switch(key) {
        case 0:
            m_cKeyboard->setUp(toggle);
            break;
        case 1:
            m_cKeyboard->setDown(toggle);
            break;
        case 2:
            m_cKeyboard->setLeft(toggle);
            lastDirection = 1;
            break;
        case 3:
            m_cKeyboard->setRight(toggle);
            lastDirection = 0;
            break;
        default: break;
    }
}

void Player::drawHP(sf::RenderTarget &m_window) {
    for(int i = 0; i < std::ceil((float)hitPoints/20.0f); i++) {
        hearts[i] = heartSprite->getSprite();
        hearts[i].setOrigin(8, 8);
        hearts[i].setScale(1, 1);
        /// -26 means that the hearts vector is placed 26 px further to the left so the HP is centered to the player
        /// i * 12 is placing every heart at 12 pixels from each other
        /// 48 is placing the hearts vector 48 pixels above the player
        hearts[i].setPosition(Entity::getPositionFromComp().getX() - 26 + i*12, Entity::getPositionFromComp().getY()-48);
        if(hitPoints%20 != 0) {
            hearts[hitPoints/20].setTextureRect(sf::IntRect(17, 0, 16, 16));
        }
        m_window.draw(hearts[i]);
    }
}


void Player::drawWeapon(sf::RenderTarget &m_window) {
    m_weapon->updateAnim();
    m_weapon->draw(m_window, this->getPositionFromComp(), lastDirection);
}

void Player::swingWeapon() {
    m_weapon->swing();
}

void Player::drawRange(sf::RenderTarget &target, float radius, float directionAngle) {
    semicircle.clear();
    semicircle.append(sf::Vertex(sf::Vector2f(getPositionFromComp().getX(), getPositionFromComp().getY()), sf::Color(200, 200, 200, 30)));

    float startAngle = directionAngle - 45.0f;
    float endAngle = directionAngle + 45.0f;

    for (float angle = startAngle; angle <= endAngle; angle += 1.0f) {
        float rad = angle * 3.14159265f / 180.0f;
        sf::Vector2f point(
            getPositionFromComp().getX() + radius * cos(rad),
            getPositionFromComp().getY() + radius * sin(rad)
        );
        semicircle.append(sf::Vertex(point, sf::Color(200, 200, 200, 30)));
    }

    target.draw(semicircle);
}

void Player::swap(Player &p1, Player &p2) {
    using std::swap;
    swap(p1.m_cKeyboard, p2.m_cKeyboard);
    swap(p1.heartSprite, p2.heartSprite);
    swap(p1.hitPoints, p2.hitPoints);
    swap(p1.lastHit, p2.lastHit);
    swap(p1.m_weapon, p2.m_weapon);
    swap(p1.lastDirection, p2.lastDirection);
    swap(p1.semicircle, p2.semicircle);
}

std::shared_ptr<Entity> Player::clone() const {
    return std::make_shared<Player>(*this);
}

Player& Player::operator=(Player rhs) {
    Entity::operator=(rhs);
    swap(*this, rhs);
    return *this;
}

std::ostream& operator<<(std::ostream &os, const Player &player) {
    os << static_cast<const Entity&>(player);
    os << player.hitPoints << " " << player.lastHit << " " << player.lastDirection << " ";
    return os;
}

void Player::takeBonus(int bonus, const std::string &option) {
    if(option == "damage")  damage += bonus;
    if(option == "hit_cooldown_reduction") hitCooldown -= bonus;
}
