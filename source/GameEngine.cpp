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
                        "assets/Player.png",
                        "player");
    m_zombie = Zombie(myVec(myZombieConfig.posX, myZombieConfig.posY),
                        myVec(myZombieConfig.vecX, myZombieConfig.vecY),
                        "assets/Zombie.png",
                        "zombie");

    m_playerHPText = Text("Fonts/ARIAL.TTF",
                "Player HP : " + std::to_string(m_player.getHitPoints()),
                24,
                sf::Color::Cyan,
                myVec(960, 100));

    m_gameLostMsg = Text("Fonts/ARIAL.TTF",
                        "GAME LOST",
                        32,
                        sf::Color::Red,
                        myVec(960, 540));
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

        for(size_t i = 0; i < 23; i++) {
            for(size_t j = 0; j < 40; j++) {
                checkCollisions(m_player, m_tileManager.getTile(i, j));
                checkCollisions(m_zombie, m_tileManager.getTile(i, j));
            }
        }

        m_window.clear(sf::Color::Black);

        m_tileManager.printMap(m_window);

        if(m_player.isAlive()) {
            m_zombie.followPlayer(m_player.getPositionFromComp());
            m_zombie.updateSprite(m_zombie.getDirection());
            m_zombie.draw(m_window);
        }else {
            m_gameLostMsg.drawText(m_window);
        }
        m_playerHPText.drawText(m_window);
        m_player.draw(m_window);

        m_window.display();

        m_player.changeAnimation();
        m_zombie.changeAnimation();
        m_frame++;
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
            if(event.key.code == sf::Keyboard::R) {
                run();
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
        m_player.updateSprite("up");
    }
    if(m_player.isKeyDown()) {
        direction += myVec(0, m_player.getVelocityFromComp().getY());
        m_player.updateSprite("down");

    }
    if(m_player.isKeyLeft()) {
        direction += myVec(-m_player.getVelocityFromComp().getX(), 0);
        m_player.updateSprite("left");

    }
    if(m_player.isKeyRight()) {
        direction += myVec(m_player.getVelocityFromComp().getX(), 0);
        m_player.updateSprite("right");
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

void GameEngine::checkCollisions(Entity& e1, Entity& e2) {
    if (e2.getPositionFromComp().getX() - e2.getHalfWidth() < e1.getPositionFromComp().getX() + e1.getHalfWidth() &&
        e2.getPositionFromComp().getX() + e2.getHalfWidth() > e1.getPositionFromComp().getX() - e1.getHalfWidth() &&
        e2.getPositionFromComp().getY() - e2.getHalfHeight() < e1.getPositionFromComp().getY() + e1.getHalfHeight() &&
        e2.getPositionFromComp().getY() + e2.getHalfHeight() > e1.getPositionFromComp().getY() - e1.getHalfHeight()) {

        if(e1.isType("player") && e2.isType("zombie")) {
            if(e2.getLastHit() == 0 && e1.getHitPoints() > 0) {
                e1.updateHitPoints(10);
                e2.updateHitCooldown(m_frame);
                m_playerHPText.updateTextContent("Player HP : " + std::to_string(e1.getHitPoints()));
            }else if(m_frame - e2.getLastHit() > 180 && e1.getHitPoints() > 0) {   ///180 = 3 seconds, the zombie should have a 3 seconds cooldown between hits
                e1.updateHitPoints(10);
                e2.updateHitCooldown(m_frame);
                m_playerHPText.updateTextContent("Player HP : " + std::to_string(e1.getHitPoints()));
            }
        }

        m_collision.setOverlap(e1, e2);

        if((e1.isType("player") || e1.isType("zombie")) && (e2.isType("zombie") || e2.isType("tile"))) {
            if (m_collision.isHorizontalOverlap()) {
                if (m_collision.isLeftOverlap()) {
                    e1.setPositionInComp(e1.getPositionFromComp() + myVec(m_collision.getOverlapX(), 0.0f));
                } else {
                    e1.setPositionInComp(e1.getPositionFromComp() - myVec(m_collision.getOverlapX(), 0.0f));
                }
            } else {
                if (m_collision.isTopOverlap()) {
                    e1.setPositionInComp(e1.getPositionFromComp() + myVec(0.0f, m_collision.getOverlapY()));
                } else {
                    e1.setPositionInComp(e1.getPositionFromComp() - myVec(0.0f, m_collision.getOverlapY()));
                }
            }
        }
    }
}