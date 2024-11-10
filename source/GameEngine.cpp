#include <utility>

#include "../header/GameEngine.h"

#include "../header/Player.h"
#include "../header/Zombie.h"

GameEngine::GameEngine(std::string  setupPath) : m_setupPath(std::move(setupPath)) {}

void GameEngine::Init(const std::string& setupPath) {
    std::ifstream input(setupPath);
    if (!input.is_open()) {
        std::cerr << "Error: Could not open setup file at " << setupPath << std::endl;
        return;
    }
    std::string commandKey;

    while(input >> commandKey) {
        if(commandKey == "Window") {
            input >> myWindowConfig.width >> myWindowConfig.height >> myWindowConfig.FPS;
            input >> myWindowConfig.fullscreen;
        }
        if(commandKey == "Player") {
            input >> myPlayerConfig.posX >> myPlayerConfig.posY;
            input >> myPlayerConfig.vecX >> myPlayerConfig.vecY;
        }
        if(commandKey == "Zombie") {
            input >> myZombieConfig.posX >> myZombieConfig.posY;
            input >> myZombieConfig.vecX >> myZombieConfig.vecY;
        }
    }


    m_window.create(sf::VideoMode(myWindowConfig.width, myWindowConfig.height), "DumbHack :: Survival", myWindowConfig.fullscreen ? sf::Style::None : sf::Style::Default);
    windowAspectRatio = static_cast<float>(m_window.getSize().x) / static_cast<float>(m_window.getSize().y);
    mapAspectRatio = 1920.f / 1080.f;

    if (windowAspectRatio > mapAspectRatio) {
        newHeight = m_window.getSize().x / mapAspectRatio;
        m_view.setSize(m_window.getSize().x, newHeight);
        m_view.setCenter(m_window.getSize().x / 2.f, newHeight / 2.f);
    } else {
        newWidth = m_window.getSize().y * mapAspectRatio;
        m_view.setSize(newWidth, m_window.getSize().y);
        m_view.setCenter(newWidth / 2.f, m_window.getSize().y / 2.f);
    }

    m_window.setView(m_view);

    m_window.setFramerateLimit(myWindowConfig.FPS);

    m_tileManager.loadMap("Init/world.txt");

    keyMap[sf::Keyboard::W] = 0;    //UP
    keyMap[sf::Keyboard::S] = 1;    //DOWN
    keyMap[sf::Keyboard::A] = 2;    //LEFT
    keyMap[sf::Keyboard::D] = 3;    //RIGHT

    m_player = Player(myVec(myPlayerConfig.posX, myPlayerConfig.posY),
                        myVec(myPlayerConfig.vecX, myPlayerConfig.vecY),
                        "assets/Player.png");
    m_zombie = Zombie(myVec(myZombieConfig.posX, myZombieConfig.posY),
                        myVec(myZombieConfig.vecX, myZombieConfig.vecY),
                        "assets/Zombie.png");

    if(m_font.loadFromFile("Fonts/ARIAL.TTF")) {
        std::cerr<<"Error loading font."<<std::endl;
    }
    m_text.setFont(m_font);
    m_text.setString("Player HP: " + std::to_string(m_player.getHitPoitns()));
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Cyan);
    m_text.setStyle(sf::Text::Bold);
    m_text.setPosition(880, 50);

    gameState.setFont(m_font);
    gameState.setCharacterSize(32);
    gameState.setFillColor(sf::Color::Red);
    gameState.setStyle(sf::Text::Bold);
    gameState.setPosition(880, 540);
}

void GameEngine::run() {
    Init(m_setupPath);

    while(m_window.isOpen()) {
        listenEvents();
        if(m_player.isAlive()) {
            handleEvents();
            checkPlayerOutOfBounds();
        }
        checkCollisions(m_player, m_zombie);

        m_window.clear(sf::Color::Black);

        m_tileManager.printMap(m_window);

        if(m_player.isAlive()) {
            m_zombie.updatePosition(m_player.getPositionFromComp());
            m_zombie.updateSprite(m_animationZombie);
            m_zombie.draw(m_window);
        }else {
            gameState.setString("GAME LOST");
            m_window.draw(gameState);
        }
        m_player.draw(m_window);

        m_window.draw(m_text);
        m_window.display();

        m_playerFrameCounter ++;
        m_zombieFrameCounter ++;
        m_frame++;
        ///NOTE: Using m_frame to update the frame for each animation every 12 frames.
        if(m_playerFrameCounter > 12) {
            if(m_animationPlayer == 0) {
                m_animationPlayer = 16;
            }else if(m_animationPlayer == 16) {
                m_animationPlayer = 0;
            }
            m_playerFrameCounter = 0;
        }
        if(m_zombieFrameCounter > 18) {
            if(m_animationZombie == 0) {
                m_animationZombie = 16;
            }else if(m_animationZombie == 16) {
                m_animationZombie = 0;
            }
            m_zombieFrameCounter = 0;
        }
    }
}

void GameEngine::listenEvents() {
    sf::Event event{};
    while(m_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            m_window.close();
        }

        if(event.type == sf::Event::KeyPressed) {
            if (keyMap.contains(event.key.code)) {
                m_player.setKeyValue(keyMap.at(event.key.code), true);
            }
            if(event.key.code == sf::Keyboard::Escape) {
                m_window.close();
            }
        }
        if(event.type == sf::Event::KeyReleased) {
            if (keyMap.contains(event.key.code)) {
                m_player.setKeyValue(keyMap.at(event.key.code), false);
            }
        }
    }
}

void GameEngine::handleEvents() const {
    myVec direction(0.0f, 0.0f);
    if(m_player.isKeyUp()) {
        direction += myVec(0, -m_player.getVelocityFromComp().getY());
        // m_player.getSpriteComponent()->updateSpriteComponent("up", m_animation);
        m_player.updateSprite("up", m_animationPlayer);
    }
    if(m_player.isKeyDown()) {
        direction += myVec(0, m_player.getVelocityFromComp().getY());
        m_player.updateSprite("down", m_animationPlayer);

    }
    if(m_player.isKeyLeft()) {
        direction += myVec(-m_player.getVelocityFromComp().getX(), 0);
        m_player.updateSprite("left", m_animationPlayer);

    }
    if(m_player.isKeyRight()) {
        direction += myVec(m_player.getVelocityFromComp().getX(), 0);
        m_player.updateSprite("right", m_animationPlayer);
    }

    if(direction.getX() != 0.0f && direction.getY() != 0.0f) {
        direction.normalize();
        direction *= 5.0f;
    }
    m_player.updatePositionInComp(direction);
}


void GameEngine::checkPlayerOutOfBounds() {
    if(m_player.getPositionFromComp().getX() < 16)                          m_player.setPositionInComp(myVec(16, m_player.getPositionFromComp().getY()));
    if(m_player.getPositionFromComp().getX() > m_window.getSize().x - 16)   m_player.setPositionInComp(myVec(m_window.getSize().x - 16, m_player.getPositionFromComp().getY()));
    if(m_player.getPositionFromComp().getY() < 16)                          m_player.setPositionInComp(myVec(m_player.getPositionFromComp().getX(),16));
    if(m_player.getPositionFromComp().getY() > m_window.getSize().y - 16)   m_player.setPositionInComp(myVec(m_player.getPositionFromComp().getX(), m_window.getSize().y - 16));
}

void GameEngine::checkCollisions(Player& p, Zombie& z) {
    if (z.getPositionFromComp().getX() - z.getHalfWidth() < p.getPositionFromComp().getX() + p.getHalfWidth() &&
        z.getPositionFromComp().getX() + z.getHalfWidth() > p.getPositionFromComp().getX() - p.getHalfWidth() &&
        z.getPositionFromComp().getY() - z.getHalfHeight() < p.getPositionFromComp().getY() + p.getHalfHeight() &&
        z.getPositionFromComp().getY() + z.getHalfHeight() > p.getPositionFromComp().getY() - p.getHalfHeight()) {

        if(z.getLastHit() == 0 && p.getHitPoitns() > 0) {
            p.updateHitPoints(10);
            z.updateHitCooldown(m_frame);
            m_text.setString("Player HP: " + std::to_string(p.getHitPoitns()));
        }else if(m_frame - z.getLastHit() > 180 && p.getHitPoitns() > 0) {   ///180 = 3 seconds, the zombie should have a 3 seconds cooldown between hits
            p.updateHitPoints(10);
            z.updateHitCooldown(m_frame);
            m_text.setString("Player HP: " + std::to_string(p.getHitPoitns()));
        }
        deltaX = p.getPositionFromComp().getX() - z.getPositionFromComp().getX();
        deltaY = p.getPositionFromComp().getY() - z.getPositionFromComp().getY();

        overlapX = (p.getHalfWidth() + z.getHalfWidth()) - std::abs(deltaX);
        overlapY = (p.getHalfHeight() + z.getHalfHeight()) - std::abs(deltaY);

        if (overlapX < overlapY) {
            if (deltaX > 0.0f) {
                p.setPositionInComp(p.getPositionFromComp() + myVec(overlapX, 0.0f));
            } else {
                p.setPositionInComp(p.getPositionFromComp() - myVec(overlapX, 0.0f));
            }
        } else {
            if (deltaY > 0.0f) {
                p.setPositionInComp(p.getPositionFromComp() + myVec(0.0f, overlapY));
            } else {
                p.setPositionInComp(p.getPositionFromComp() - myVec(0.0f, overlapY));
            }
        }
    }
}

