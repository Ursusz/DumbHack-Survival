#include "../header/VendingMachine.h"

#include <iomanip>

VendingMachine::VendingMachine(const myVec &position, const myVec &velocity, const std::string &texture_path,
                               bool hitAble, bool collidable, bool isDynamic)
    : Entity(position, velocity, texture_path, hitAble, collidable, isDynamic)
    , dosesLeft("Fonts/ARIAL.TTF",
                "Doses left in Vending Machine: ",
                12, ///FONT SIZE 12 PX
                sf::Color::Cyan,
                position)
    , leftTimeToNextDose("Fonts/ARIAL.TTF",
                "Time left until the next dose: ",
                12, ///FONT SIZE 12 PX
                sf::Color::Cyan,
                position){
    if(!drinkBuffer.loadFromFile("assets/DrinkSoda.ogg")) {
        throw std::runtime_error("Error loading DrinkSoda.ogg");
    }
    drinkSound.setBuffer(drinkBuffer);
    drinkSound.setVolume(25.0f);
}

VendingMachine::VendingMachine(const Entity &rhs)
    : Entity(rhs) {
    if(!drinkBuffer.loadFromFile("assets/DrinkSoda.ogg")) {
        throw std::runtime_error("Error loading DrinkSoda.ogg");
    }
    drinkSound.setBuffer(drinkBuffer);
    drinkSound.setVolume(25.0f);
}

void VendingMachine::drawTexts(sf::RenderTarget& target) {
    dosesLeft.setString("Doses left in Vending Machine: " + std::to_string(numOfDoses));

    float elapsedTimeSinceLastUse = clock.getElapsedTime().asSeconds() - lastUsedTime;
    if (elapsedTimeSinceLastUse > 30.0f) {
        elapsedTimeSinceLastUse = 30.0f;
    }

    float remainingTime = 30.0f - elapsedTimeSinceLastUse;

    if (remainingTime < 0.0f) {
        remainingTime = 0.0f;
    }

    std::ostringstream oss;
    oss << "Time left until the next dose: " << std::fixed << std::setprecision(1) << remainingTime;
    leftTimeToNextDose.setString(oss.str());

    dosesLeft.updateTextPosition(getPositionFromComp() - myVec(0, 40));
    leftTimeToNextDose.updateTextPosition(getPositionFromComp() - myVec(10, 55));

    dosesLeft.drawText(target);
    leftTimeToNextDose.drawText(target);
}



void VendingMachine::takeDamage(int /*damage*/) {}

bool VendingMachine::canHit(int frame) {
    (void)frame;
    if (numOfDoses > 0) {
        float elapsedTime = clock.getElapsedTime().asSeconds();
        if ((elapsedTime - lastUsedTime >= 29.9f && lastUsedTime != 0.0f) || lastUsedTime == 0.0f) {
            lastUsedTime = elapsedTime;
            return true;
        }
    }
    return false;
}


void VendingMachine::interactWith(Entity &other, int frame) {
    if(this->canHit(frame) && other.canTakeDamage()) {
        numOfDoses--;
        drinkSound.play();
        other.takeDamage(-40);
    }
}

std::shared_ptr<Entity> VendingMachine::clone() const {
    return std::make_shared<VendingMachine>(*this);
}

VendingMachine &VendingMachine::operator=(const VendingMachine &rhs){
    Entity::operator=(rhs);
    numOfDoses = rhs.numOfDoses;
    lastUsedTime = 0.0f;
    dosesLeft = rhs.dosesLeft;
    leftTimeToNextDose = rhs.leftTimeToNextDose;
    drinkBuffer = rhs.drinkBuffer;
    drinkSound.setBuffer(drinkBuffer);
    drinkSound.setVolume(25.0f);
    return *this;
}
