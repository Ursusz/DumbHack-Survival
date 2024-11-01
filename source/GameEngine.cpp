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

    ///NOTE: preventiv, schimb pe viitor // Init returneaza eroare ->
    try {
        m_window.create(sf::VideoMode(myWindowConfig.width, myWindowConfig.height), "DumbHack :: Survival", myWindowConfig.fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    } catch (const std::exception& e) {
        std::cerr << "Error during window creation: " << e.what() << std::endl;
    }
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
                        "assets/pixil-frame-0 (2).png");
}

void GameEngine::run() {
    Init(m_setupPath);

    while(m_window.isOpen()) {
        listenEvents();
        handleEvents();
        m_window.clear(sf::Color::Cyan);

        m_tileManager.printMap(m_window);

        m_zombie.updatePosition(m_player.getPositionFromComp());
        m_zombie.draw(m_window);

        m_player.draw(m_window);

        m_window.display();

        m_frame ++;
        ///NOTE: Using m_frame to update the frame for each animation every 12 frames.
        if(m_frame > 12) {
            if(m_animation == 0) {
                m_animation = 16;
            }else if(m_animation == 16) {
                m_animation = 0;
            }
            m_frame = 0;
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
        m_player.updateSprite("up", m_animation);
    }
    if(m_player.isKeyDown()) {
        direction += myVec(0, m_player.getVelocityFromComp().getY());
        m_player.updateSprite("down", m_animation);

    }
    if(m_player.isKeyLeft()) {
        direction += myVec(-m_player.getVelocityFromComp().getX(), 0);
        m_player.updateSprite("left", m_animation);

    }
    if(m_player.isKeyRight()) {
        direction += myVec(m_player.getVelocityFromComp().getX(), 0);
        m_player.updateSprite("right", m_animation);
    }

    if(direction.getX() != 0.0f && direction.getY() != 0.0f) {
        direction.normalize();
        direction *= 5.0f;
    }
    m_player.updatePositionInComp(direction);
}
