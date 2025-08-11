#include "../header/GameEngine.h"

GameEngine::GameEngine() = default;

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
    }
    m_window.create(sf::VideoMode(myWindowConfig.width, myWindowConfig.height), "DumbHack :: Survival", sf::Style::Fullscreen);

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

    keyMap[sf::Keyboard::W] = 0;    //UP
    keyMap[sf::Keyboard::S] = 1;    //DOWN
    keyMap[sf::Keyboard::A] = 2;    //LEFT
    keyMap[sf::Keyboard::D] = 3;    //RIGHT

    try {
        entityManager.initEntities();

        m_gameLostMsg = Text("Fonts/ARIAL.TTF",
                    "GAME LOST",
                    32, ///FONT SIZE 32 PX
                    sf::Color::Red,
                    myVec(960, 540));

        m_gameWonMsg = Text("Fonts/ARIAL.TTF",
                            "GAME WON",
                            32, ///FONT SIZE 32 PX
                            sf::Color::Green,
                            myVec(960, 540));

       if(!m_music.openFromFile("assets/music.ogg")) {
           throw std::runtime_error("Failed to load music");
       }
        m_music.setVolume(0.0f);
        m_music.setLoop(true);
        m_music.play();
    }catch(const textureError& err) {
        std::cerr << "Texture error: " <<  err.what() << std::endl;
        m_window.close();
    }catch(const fontError& err) {
        std::cerr << "Font error: " << err.what() << std::endl;
        m_window.close();
    }catch(const gameException& err) {
        std::cerr << err.what() << std::endl;
        m_window.close();
    }catch(const std::runtime_error& err) {
        std::cerr << "Other runtime error: " << err.what() << std::endl;
        m_window.close();
    }catch(const std::exception& err) {
        std::cerr << "Other exception: " << err.what() << std::endl;
        m_window.close();
    }

    agent.startBotCommunication(*this);
}

void GameEngine::run() {
    while(m_window.isOpen()) {
        listenEvents();
        if(entityManager.isGameStillPlayable()) {
            entityManager.handlePlayerEvents();
            entityManager.checkPlayerOutOfBound(m_window);
            entityManager.computeZombieWaves();
        }

        entityManager.resetMainEntitiesForCollissions(m_frame);

        m_window.clear(sf::Color::Black);

        //################### Printing everything
        entityManager.drawEntities(m_window, m_frame);

        switch (entityManager.verifyPlayerExistance_and_ComputersCompletion(m_window, m_frame)) {
            case 0 : m_gameLostMsg.drawText(m_window);
                break;
            case 1 : m_gameWonMsg.drawText(m_window);
                break;
            case 2: //result could be 2 which means neither the player is dead or the computers have been completed
            default: break;
        }
        m_window.display();

        entityManager.updateAnimations();
        m_frame++;

        agent.updateGameState(*this);
    }
}

void GameEngine::restart() {
    m_frame = 0;
}

void GameEngine::listenEvents() {
    sf::Event event{};
    while(m_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            m_window.close();
        }

        if(event.type == sf::Event::KeyPressed) {
            if (keyMap.contains(event.key.code)) {
                entityManager.togglePlayerKey(keyMap.at(event.key.code), true);
            }
            if(event.key.code == sf::Keyboard::Escape) {
                agent.stopBotCommunication();
                m_window.close();
            }
            if(event.key.code == sf::Keyboard::R) {
                entityManager.resetEntities();
                m_music.stop();
                m_music.play();
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            entityManager.attackZombies(m_frame);
        }
        if(event.type == sf::Event::KeyReleased) {
            if (keyMap.contains(event.key.code)) {
                entityManager.togglePlayerKey(keyMap.at(event.key.code), false);
            }
        }
    }
    int action = agent.getAgentAction();
    if (action != -1) {
        entityManager.togglePlayerKey(0, false);
        entityManager.togglePlayerKey(1, false);
        entityManager.togglePlayerKey(2, false);
        entityManager.togglePlayerKey(3, false);
        switch (action) {
            case 0:
            case 1:
            case 2:
            case 3:
                entityManager.togglePlayerKey(action, true);
                break;
            case 4:
                entityManager.resetEntities();
                m_music.stop();
                m_music.play();
        }
    }
}

const Player& GameEngine::getPlayer() const {
    return entityManager.getPlayer();
}

std::vector<std::pair<float, float>> GameEngine::getZombiesPositions() const {
    auto zombies = entityManager.getZombies();
    std::vector<std::pair<float, float>> zombiesPositions;
    for(const auto& zombie : zombies) {
        zombiesPositions.emplace_back(zombie->getPositionFromComp().getX(), zombie->getPositionFromComp().getY());
    }
    return zombiesPositions;
}

std::vector<std::pair<float, float>> GameEngine::getComputerPositions() const {
    return entityManager.getComputerPositions();
}

std::vector<int> GameEngine::getComputersCompletions() const {
    return entityManager.getComputersCompletions();
}

std::vector<std::pair<float, float>> GameEngine::getTrapsPositions() const {
    return entityManager.getTrapsPositions();
}