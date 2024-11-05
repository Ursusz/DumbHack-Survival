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

    m_desktopMode = sf::VideoMode::getDesktopMode();

    scaleX = m_desktopMode.width / myWindowConfig.width;
    scaleY = m_desktopMode.height / myWindowConfig.height;
    scaleFactor = std::min(scaleX, scaleY);

    m_view = sf::View(sf::FloatRect(0, 0, myWindowConfig.width, myWindowConfig.height));
    m_view.setViewport(sf::FloatRect(0, 0, scaleFactor * myWindowConfig.width / m_desktopMode.width, scaleFactor * myWindowConfig.height / m_desktopMode.height));

    m_window.create(m_desktopMode, "DumbHack :: Survival", myWindowConfig.fullscreen ? sf::Style::None : sf::Style::Default);
    m_window.setFramerateLimit(myWindowConfig.FPS);
    m_window.setView(m_view);

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
}

void GameEngine::run() {
    Init(m_setupPath);

    while(m_window.isOpen()) {
        listenEvents();
        handleEvents();
        checkPlayerOutOfBounds();
        m_window.clear(sf::Color::Black);

        m_tileManager.printMap(m_window);

        m_zombie.updatePosition(m_player.getPositionFromComp());
        m_zombie.updateSprite(m_animationZombie);
        m_zombie.draw(m_window);

        m_player.draw(m_window);

        m_window.display();

        m_playerFrameCounter ++;
        m_zombieFrameCounter ++;
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
