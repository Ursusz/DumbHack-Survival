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
            input >> myWindowConfig.fullscreen;}
    }

    ///NOTE: preventiv, schimb pe viitor // Init returneaza eroare ->
    try {
        m_window.create(sf::VideoMode(myWindowConfig.width, myWindowConfig.height), "DumbHack :: Survival", myWindowConfig.fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    } catch (const std::exception& e) {
        std::cerr << "Error during window creation: " << e.what() << std::endl;
    }
    m_window.setFramerateLimit(myWindowConfig.FPS);

    m_player = Player(myVec(100, 100), myVec(5, 5), "assets/Player.png");
    m_zombie = Zombie(myVec(500, 500), myVec(2, 2), "assets/pixil-frame-0 (2).png");

    rect = sf::RectangleShape(sf::Vector2f(48, 48));
    rect2 = sf::RectangleShape(sf::Vector2f(144, 96));

    for(int i = 0; i < 40; i++) {
        for(int j = 0; j < 23; j++) {
            m_tile[i][j] = Tile(myVec(i*48 + 24, j*48 + 24), "assets/Wooden Plank.png");
        }
    }
}

void GameEngine::run() {
    Init(m_setupPath);

    while(m_window.isOpen()) {
        listenEvents();
        handleEvents();
        m_window.clear(sf::Color::Cyan);

        for(int i = 0; i < 40; i++) {
            for(int j = 0; j < 23; j++) {
                m_tile[i][j].draw(m_window);
            }
        }

        rect.setOrigin(24, 24);
        rect.setOutlineColor(sf::Color::Green);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineThickness(2);
        rect.setPosition(m_player.getMotionComponent()->getPosition().getX(), m_player.getMotionComponent()->getPosition().getY());

        rect2.setOrigin(72, 48);
        rect2.setOutlineColor(sf::Color::Green);
        rect2.setFillColor(sf::Color::Transparent);
        rect2.setOutlineThickness(2);
        rect2.setPosition(m_player.getMotionComponent()->getPosition().getX(), m_player.getMotionComponent()->getPosition().getY());


        m_window.draw(rect2);
        m_window.draw(rect);

        m_zombie.updatePosition(m_player.getMotionComponent()->getPosition());
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
        m_player.getSpriteComponent()->updateSpriteComponent("up", m_animation);
    }
    if(m_player.getKeyboardComponent()->down()) {
        direction += myVec(0, m_player.getMotionComponent()->getVelocity().getY());
        m_player.getSpriteComponent()->updateSpriteComponent("down", m_animation);
    }
    if(m_player.getKeyboardComponent()->left()) {
        direction += myVec(-m_player.getMotionComponent()->getVelocity().getX(), 0);
        m_player.getSpriteComponent()->updateSpriteComponent("left", m_animation);
    }
    if(m_player.getKeyboardComponent()->right()) {
        direction += myVec(m_player.getMotionComponent()->getVelocity().getX(), 0);
        m_player.getSpriteComponent()->updateSpriteComponent("right", m_animation);
    }

    if(direction.getX() != 0.0f && direction.getY() != 0.0f) {
        direction.normalize();
        direction *= 5.0f;
    }

    m_player.getMotionComponent()->updatePosition(direction);
}
