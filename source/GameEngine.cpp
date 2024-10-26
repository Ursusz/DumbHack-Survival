#include "GameEngine.h"

#include "Player.h"

GameEngine::GameEngine(const std::string& setupPath) : m_setupPath(setupPath) {}


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
            input >> myWindowConfig.fullscreen;}
    }

    try {
        m_window.create(sf::VideoMode(myWindowConfig.width, myWindowConfig.height), "DumbHack :: Survival", myWindowConfig.fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    } catch (const std::exception& e) {
        std::cerr << "Error during window creation: " << e.what() << std::endl;
    }
    m_window.setFramerateLimit(myWindowConfig.FPS);

   m_player = Player(myVec(100, 100), myVec(10, 10), 64, 64);
}

void GameEngine::run() {
    Init(m_setupPath);

    while(m_window.isOpen()) {
        listenEvents();
        handleEvents();
        m_window.clear();
        m_player.draw(m_window);
        m_window.display();

    }
}

void GameEngine::listenEvents() {
    sf::Event event{};
    while(m_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            m_window.close();
        }
        if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::W) {
                m_player.getKeyboardComponent()->setUp(true);
            }
            if(event.key.code == sf::Keyboard::S) {
                m_player.getKeyboardComponent()->setDown(true);
            }
            if(event.key.code == sf::Keyboard::A) {
                m_player.getKeyboardComponent()->setLeft(true);
            }
            if(event.key.code == sf::Keyboard::D) {
                m_player.getKeyboardComponent()->setRight(true);
            }
        }
        if(event.type == sf::Event::KeyReleased) {
            if(event.key.code == sf::Keyboard::W) {
                m_player.getKeyboardComponent()->setUp(false);
            }
            if(event.key.code == sf::Keyboard::S) {
                m_player.getKeyboardComponent()->setDown(false);
            }
            if(event.key.code == sf::Keyboard::A) {
                m_player.getKeyboardComponent()->setLeft(false);
            }
            if(event.key.code == sf::Keyboard::D) {
                m_player.getKeyboardComponent()->setRight(false);
            }
        }
    }
}

void GameEngine::handleEvents() {
    myVec direction(0.0f, 0.0f);
    if(m_player.getKeyboardComponent()->up()) {
        direction += myVec(0, -m_player.getMotionComponent()->getVelocity().getY());
    }
    if(m_player.getKeyboardComponent()->down()) {
        direction += myVec(0, m_player.getMotionComponent()->getVelocity().getY());
    }
    if(m_player.getKeyboardComponent()->left()) {
        direction += myVec(-m_player.getMotionComponent()->getVelocity().getX(), 0);
    }
    if(m_player.getKeyboardComponent()->right()) {
        direction += myVec(m_player.getMotionComponent()->getVelocity().getX(), 0);
    }

    if(direction.getX() != 0.0f && direction.getY() != 0.0f) {
        direction.normalize();
        direction *= 10.0f;
    }

    m_player.getMotionComponent()->updatePosition(direction);
}
