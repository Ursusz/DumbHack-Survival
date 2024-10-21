#include "GameEngine.h"

#include "myVec.h"

GameEngine::GameEngine(const std::string& setupPath) {
    m_setupPath = setupPath;
}


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
        m_window.create(sf::VideoMode(myWindowConfig.width, myWindowConfig.height), "DumbHack :: Survival", myWindowConfig.fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
    } catch (const std::exception& e) {
        std::cerr << "Error during window creation: " << e.what() << std::endl;
    }
    m_window.setFramerateLimit(myWindowConfig.FPS);
}

void GameEngine::run() {
    Init(m_setupPath);

    while(m_window.isOpen()) {
        sf::Event event{};
        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                m_window.close();
            }
        }
        m_window.clear();

        m_window.display();
    }
}