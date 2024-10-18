#include "Game.h"

void Game::init(const std::string &path) {
    std::ifstream input(path);
    while(input >> m_keyToken) {
        if(m_keyToken == "Window") {
            input >> m_windowConfig.width >> m_windowConfig.height >> m_windowConfig.FPS >> m_windowConfig.fullScreen;
        }
    }
    try {
        m_window.create(sf::VideoMode(m_windowConfig.width, m_windowConfig.height), "Game", m_windowConfig.fullScreen ? sf::Style::Fullscreen : sf::Style::Default);
    }catch(const std::exception &e) {
        std::cerr <<"Error during window init. " << e.what() << std::endl;
    }
    m_window.setFramerateLimit(m_windowConfig.FPS);
}

void Game::run() {
    while(m_window.isOpen()) {
        m_window.clear();
        sf::Event event;
        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                m_window.close();
            }
        }
        m_window.display();
    }
}

