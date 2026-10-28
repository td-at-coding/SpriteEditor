#include "sprite/graphics/EditorWindow.h"
#include <iostream>

namespace sprite::graphics
{

    EditorWindow::EditorWindow(unsigned width, unsigned height, const std::string& title)
        : sf::RenderWindow(sf::VideoMode(sf::Vector2u{width, height}), title.c_str(), sf::Style::Titlebar | sf::Style::Close)
    { 
        setFramerateLimit(60);

        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

        std::cout << "SFML VERSION: "
                << SFML_VERSION_MAJOR << "."
                << SFML_VERSION_MINOR << "."
                << SFML_VERSION_PATCH << std::endl;

        int posX = (desktopMode.size.x - width) / 2;
        int posY = (desktopMode.size.y - height) / 2;

        setPosition(sf::Vector2i(posX, posY));
    }

}
