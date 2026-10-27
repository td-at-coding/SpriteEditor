#include <SFML/Graphics.hpp>
#include <iostream>

// If you are using C++17 or later, you can also use std::filesystem::path
#ifndef SOURCE_DIR
#define SOURCE_DIR "unknown"
#endif

int main()
{
    sf::Vector2u windowSize(800, 600);
    sf::RenderWindow window(sf::VideoMode(windowSize), "SFML Window");
    window.setFramerateLimit(60);

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    std::cout << "SFM VERSION: "
              << SFML_VERSION_MAJOR << "."
              << SFML_VERSION_MINOR << "."
              << SFML_VERSION_PATCH << std::endl;

    // 3. Calculate the center position
    int posX = (desktopMode.size.x - windowSize.x) / 2;
    int posY = (desktopMode.size.y - windowSize.y) / 2;

    // 4. Set the window position
    //window.setPosition(sf::Vector2i(posX, posY));

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