#include "../header/GameEngine.h"

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
        m_music.setVolume(40.0f);
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
}

void GameEngine::run() {
    Init(m_setupPath);
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
                entityManager.togglePlayerKey(keyMap.at(event.key.code), true);
            }
            if(event.key.code == sf::Keyboard::Escape) {
                m_window.close();
            }
            // if(event.key.code == sf::Keyboard::R) {
            //     run(); /// Trebuie sa gasesc o metoda pentru a da restart corect la joc
            // }
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
}
