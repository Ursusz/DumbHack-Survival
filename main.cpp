#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "myVec.h"

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////

int main() {
    // myVec vector(1.0f, 1.0f);
    // std::cout << vector << std::endl;
    // Vec2 vector2 = vector;
    // std::cout << vector2 << std::endl;

    ////////////////////////////////////////////////////////////////////////
    /// NOTE: this function call is needed for environment-specific fixes //
    init_threads();                                                       //
    ////////////////////////////////////////////////////////////////////////

    sf::RenderWindow window;

    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);

    window.setFramerateLimit(60);

    while(window.isOpen()) {
        bool shouldExit = false;
        sf::Event e{};
        while(window.pollEvent(e)) {
            switch(e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                // std::cout << "New width: " << window.getSize().x << '\n'
                          // << "New height: " << window.getSize().y << '\n';
                break;
            case sf::Event::KeyPressed:
                // std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                if(e.key.code == sf::Keyboard::Escape)
                    shouldExit = true;
                break;
            default:
                break;
            }
        }
        if(shouldExit) {
            window.close();
            break;
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);

        window.clear();
        window.display();
    }
    return 0;
}
