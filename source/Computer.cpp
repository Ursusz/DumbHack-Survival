#include "../header/Computer.h"

Computer::Computer(const myVec &position)
    : position(position)
    , loadBarSprite(std::make_shared<SpriteComponent>("assets/loadBar.png")){
    computersCount++;
}

Computer::Computer(const Computer& rhs)
    : position(rhs.position)
    , loadBarSprite(rhs.loadBarSprite){
    computersCount++;
}

Computer::~Computer() {
    computersCount--;
}


void Computer::drawLoadBars(sf::RenderTarget &target, const myVec& playerPos) {
    if(position.distance(playerPos) < 150) {
        frameCounterInsideComputerRange++;
    }
    for(int i = 0; i < 12; i++) {
        loadBars[i] = loadBarSprite->getSprite();
        loadBars[i].setOrigin(8, 8);
        loadBars[i].setScale(1, 1);
        loadBars[i].setPosition(position.getX() - 34 + i * 6,  position.getY() - 35);
    }
    for(int i = 0; i < 12; i++) {
        if(frameCounterInsideComputerRange/60 > i) {
            target.draw(loadBars[i]);
        }
    }
    if(frameCounterInsideComputerRange/60 > 12 && !hasCompleted) {
        computersCount--;
        hasCompleted = true;
    }
}

bool Computer::allComputersCompleted(){
    return computersCount == 0;
}

int Computer::computersCount = 0;