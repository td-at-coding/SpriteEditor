#include <SFML/Graphics.hpp>
#include <iostream>
#include "sprite/graphics/EditorWindow.h"


#ifndef SOURCE_DIR
#define SOURCE_DIR "unknown"
#endif

int main()
{
    sprite::graphics::EditorWindow window(800,600, "SpriteEditor");
    
    sf::Font font;
    if(!font.openFromFile( SOURCE_DIR"/assets/PurisaBold.ttf"))
    {
        // Handle error
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text text(font);
    text.setString("Hello, World!");
    text.setCharacterSize(24);
    auto bounds = text.getGlobalBounds();
    auto windowSize = window.getSize();
    auto textPos = sf::Vector2f(windowSize.x / 2.0f - bounds.size.x / 2.0f, windowSize.y / 2.0f - bounds.size.y / 2.0f);
    text.setPosition(textPos);

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        window.draw(text);
        window.display();
    }
    return 0;
}